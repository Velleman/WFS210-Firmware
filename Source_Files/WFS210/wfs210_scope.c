#include "WFS210/wfs210_process.h"

volatile WORD	timebase_index;
volatile WORD	sample_nr;
volatile BOOL	autotimebase_found;
BYTE			sample_buffer[2 * (PMP_LATENCY + NUMBER_OF_SAMPLES_PER_CHANNEL + 1)];
volatile BYTE	*ptr_sample_buffer;


VOID StopSampling(VOID)
{
	mStopTimebaseTimer();
	mStopAutoTrigTimer();
	mDisTrigInterrupts();
	mStopSendTimer();
	mInitSendTimer()
}


VOID RestartSampling(VOID)
{
	// disable interupts, stop timebase timer and stop autotrigger timebase
	StopSampling();

	// disable input capture modules
	mDisICInputs();

	// initialize trigger interrupts
	mInitTrigInputs();

	// set trigger slope
	if (scope_settings.status.flags.trigger_slope) mSetTrigFallingEdge()

	// reset sample counter
	sample_nr = 0;

	// reload timebase index
	timebase_index = scope_settings.timebase;

	// point to begin of samplebuffer
	if (scope_settings.timebase < CH_0P1MS_DIV) ptr_sample_buffer = sample_buffer;
	else ptr_sample_buffer = &sample_buffer[2 * PMP_LATENCY];

	if (scope_settings.status.flags.trigger_hold == RUN)
	{
		// enable auto triggering into run trigger mode
		if (scope_settings.status.flags.trigger_mode == AUTO) mStartAutoTrigTimer();

		// enable triggering
		if (scope_settings.status.flags.trigger_channel == CH1) mSelectTrigCh1() else mSelectTrigCh2();
	}
}



VOID InitSampleBuffer(VOID)
{
	memset(sample_buffer, 128, sizeof(sample_buffer));

	if (scope_settings.timebase < CH_0P1MS_DIV) ptr_sample_buffer = sample_buffer;
	else ptr_sample_buffer = &sample_buffer[2 * PMP_LATENCY];
}




VOID ScopeTasks(VOID)
{
	switch (sampling_sm)
	{
		case SM_IDLE:
			StopSampling();
			break;

		case SM_SAMPLING_START:
			CheckAutoVolt();
			break;

		case SM_AUTO_TIMEBASE:
			StartAutoTimebase();
			break;

		case SM_AUTO_TIMEBASE_BUSY:
			if (autotimebase_found) sampling_sm++;
			break;

		case SM_AUTO_TIMEBASE_DONE:
			SetAutoTimeBase();
			break;
			
		case SM_SAMPLING:
			RestartSampling();
			sampling_sm = SM_SAMPLING_BUSY;
			break;

		case SM_SAMPLING_BUSY:
			if (!(mGetTrig1TimerIntEna() || mGetTrig2TimerIntEna() || mGetAutoTrigTimerIntEna() || mGetTimebaseTimerIntEna()))
				sampling_sm = SM_SAMPLING_DONE;
			else if ((scope_settings.timebase > CH_10MS_DIV) && mGetSendTimerIntFlag())
			{
				mClrSendTimerIntFlag();
				TransmitSamples(&wfs210out, sample_nr);
			}
			break;
		
		case SM_SAMPLING_DONE:
			StopSampling();
			sampling_sm++;
			break;

		case SM_SEND_SAMPLES:
			TransmitSamples(&wfs210out, NUMBER_OF_SAMPLES_PER_CHANNEL);
			sampling_sm++;
			break;
		
		case SM_SEND_BUSY:
			if (TxReady()) sampling_sm++;
			break;

		case SM_SEND_DONE:
			if (calibration.sm) CalibrationTask();

			if ((!USBConnected()) && (!WifiConnected()))
			{
				 SetVoltDivCh1(CH_OFF_V_DIV);
				 SetVoltDivCh2(CH_OFF_V_DIV);
			}

			if (scope_settings.status.flags.trigger_hold || (scope_settings.status.flags.trigger_mode == ONCE) ||
				((scope_settings.sensitivityCh1 == CH_OFF_V_DIV) && (scope_settings.sensitivityCh2 == CH_OFF_V_DIV))
			   )
				sampling_sm = SM_IDLE;
			else sampling_sm = SM_SAMPLING_START;
			break;
	}
}



//------------------------------------------------------------------------------
// Method		: _INT1Interrupt
// Description	: Interrupt service routine (ISR) for the INT1 Interrupt
//				: This interrupt occurs when an external triggering happens on channel 1
//				: The ISR name is chosen from the device linker script.
// Parameters	: none
// Return		: void
//------------------------------------------------------------------------------

void __attribute__((interrupt, shadow, no_auto_psv)) mTrig1Interrupt(VOID)
{
	asm volatile ("					mov		_ptr_sample_buffer,W0");		// load buffer location
	asm volatile ("					mov		_timebase_index,W1");			// load timebase index
	asm volatile ("					mov		#PMDIN1,W2");					// load PMP read address
	asm volatile ("					mov		#PORTG,W3");					// load PortG read address

	asm volatile ("					cp.b	W1,#6");						// Timebase equal or slower than 0.1ms/div
	asm volatile ("					bra		NN,T1_100us_div");				// yes

	asm volatile ("					bra		W1");
	asm volatile ("					bra		T1_1us_div");
	asm volatile ("					bra		T1_1us_div");
	asm volatile ("					bra		T1_1us_div");
	asm volatile ("					bra		T1_10us_div");
	asm volatile ("					bra		T1_20us_div");
	asm volatile ("					bra		T1_50us_div");

	// inline assembler for timebase 1us/div, 2us/div & 5us/div
	asm volatile ("T1_1us_div:		repeat	#8193");						//(2 * (PMP_LATENCY + NUMBER_OF_SAMPLES_PER_CHANNEL) - 1)
	asm volatile ("					mov.b	[W2],[W0++]");					// load samples into buffer
	asm volatile ("					mov.b	[W3],W2");						// read A/B channels from AD converter
	asm volatile ("					bra		T1_ChkSwap_Ch");

	// inline assembler for timebase 10us/div
	asm volatile ("T1_10us_div:		do		#4096,End_T1_10us_div");		//(PMP_LATENCY + NUMBER_OF_SAMPLES_PER_CHANNEL - 1)
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0++]");					// load channel 1 sample into buffer
	asm volatile ("End_T1_10us_div:	mov.b	[W2],[W0++]");					// load channel 2 sample into buffer
	asm volatile ("					mov.b	[W3],W2");						// read A/B channels from AD converter
	asm volatile ("					bra		T1_ChkSwap_Ch");

	// inline assembler for timebase 20us/div
	asm volatile ("T1_20us_div:		do		#4096,End_T1_20us_div");		//(PMP_LATENCY + NUMBER_OF_SAMPLES_PER_CHANNEL - 1)
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0++]");					// load channel 1 sample into buffer
	asm volatile ("End_T1_20us_div:	mov.b	[W2],[W0++]");					// load channel 2 sample into buffer
	asm volatile ("					mov.b	[W3],W2");						// read A/B channels from AD converter
	asm volatile ("					bra		T1_ChkSwap_Ch");


	// inline assembler for timebase 50us/div
	asm volatile ("T1_50us_div:		do		#4096,End_T1_50us_div");		//(PMP_LATENCY + NUMBER_OF_SAMPLES_PER_CHANNEL - 1)
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0++]");					// load channel 1 sample into buffer
	asm volatile ("End_T1_50us_div:	mov.b	[W2],[W0++]");					// load channel 2 sample into buffer
	asm volatile ("					mov.b	[W3],W2");						// read A/B channels from AD converter
	asm	volatile ("T1_ChkSwap_Ch:	and		#64,W2");
	asm volatile ("					bra		NZ,End_T1_Sampling ");
	asm	volatile ("					dec		W0,W0");
	asm	volatile ("					dec		W0,W1");
	asm volatile ("					repeat	#8193");						//(2 * (PMP_LATENCY + NUMBER_OF_SAMPLES_PER_CHANNEL) - 1)
	asm volatile ("					mov.b	[W1--],[W0--]");				// load samples into buffer
	asm volatile ("					bra		End_T1_Sampling");


	// inline assembler for timebase 0.1ms/div or slower
	asm volatile ("T1_100us_div:	clr		TMR5HLD");						// TMR5HLD = 0;
	asm volatile ("					mov		#18,W1");						// preload 18 cycles
	asm volatile ("					mov		W1,TMR4");
	asm volatile ("					bclr	IFS1,#12");						// _T5IF = 0;
	asm volatile ("					bset	IEC1,#12");						// _T5IE = 1;
	asm volatile ("					bset	T4CON,#15");					// T4CONbits.TON = 1;

	asm volatile ("					mov.b	[W2],[W0]");					// pmp pipeline latency
	asm volatile ("					mov.b	[W2],[W0++]");					// load ad sample of channel 1 into buffer
	asm volatile ("					mov.b	[W2],[W0++]");					// load ad sample of channel 2 into buffer
	asm volatile ("					mov.b	[W2],[W0]");					// load ad sample of channel 1 into buffer
	asm volatile ("					mov.b	[W3],W2");						// read A/B channels from AD converter

	asm volatile ("					mov		W0, _ptr_sample_buffer");		// store new buffer location

	asm	volatile ("					and		#64,W2");						// check for swapping channels
	asm volatile ("					bra		Z,End_T1_1Sample");
	asm	volatile ("					dec		W0,W0");						// swap channels
	asm	volatile ("					dec		W0,W1");
	asm volatile ("					mov.b	[W0++],[W1++]");
	asm volatile ("					mov.b	[W0++],[W1++]");

	asm volatile ("End_T1_1Sample:	mov		_sample_nr,W0");				// increment sample counter
	asm volatile ("					inc		W0, W0");
	asm volatile ("					mov		W0, _sample_nr");

	mStartSendTimer();

	// disable autotrigger timer
	asm volatile ("End_T1_Sampling:	bclr	IEC0,#8");						// (bclr	IEC0,#T3IE) mDisAutoTrigTimerInt();

	// disable external trigger channel 1 interrupt
	mDisTrig1Interrupts();
}


//------------------------------------------------------------------------------
// Method		: _INT2Interrupt
// Description	: Interrupt service routine (ISR) for the INT2 Interrupt
//				: This interrupt occurs when an external triggering happens on channel 2
//				: The ISR name is chosen from the device linker script.
// Parameters	: none
// Return		: void
//------------------------------------------------------------------------------
void __attribute__((interrupt, shadow, no_auto_psv)) mTrig2Interrupt(VOID)
{
	asm volatile ("					mov		_ptr_sample_buffer,W0");		// load buffer location
	asm volatile ("					mov		_timebase_index,W1");			// load timebase index
	asm volatile ("					mov		#PMDIN1,W2");					// load PMP read address
	asm volatile ("					mov		#PORTG,W3");					// load PortG read address

	asm volatile ("					cp.b	W1,#6");						// Timebase equal or slower than 0.1ms/div
	asm volatile ("					bra		NN,T2_100us_div");				// yes

	asm volatile ("					bra		W1");
	asm volatile ("					bra		T2_1us_div");
	asm volatile ("					bra		T2_1us_div");
	asm volatile ("					bra		T2_1us_div");
	asm volatile ("					bra		T2_10us_div");
	asm volatile ("					bra		T2_20us_div");
	asm volatile ("					bra		T2_50us_div");

	// inline assembler for timebase 1us/div, 2us/div & 5us/div
	asm volatile ("T2_1us_div:		repeat	#8193");						//(2 * (PMP_LATENCY + NUMBER_OF_SAMPLES_PER_CHANNEL) - 1)
	asm volatile ("					mov.b	[W2],[W0++]");					// load samples into buffer
	asm volatile ("					mov.b	[W3],W2");						// read A/B channels from AD converter
	asm volatile ("					bra		T2_ChkSwap_Ch");

	// inline assembler for timebase 10us/div
	asm volatile ("T2_10us_div:		do		#4096,End_T2_10us_div");		//(PMP_LATENCY + NUMBER_OF_SAMPLES_PER_CHANNEL - 1)
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0++]");					// load channel 1 sample into buffer
	asm volatile ("End_T2_10us_div:	mov.b	[W2],[W0++]");					// load channel 2 sample into buffer
	asm volatile ("					mov.b	[W3],W2");						// read A/B channels from AD converter
	asm volatile ("					bra		T2_ChkSwap_Ch");

	// inline assembler for timebase 20us/div
	asm volatile ("T2_20us_div:		do		#4096,End_T2_20us_div");		//(PMP_LATENCY + NUMBER_OF_SAMPLES_PER_CHANNEL - 1)
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0++]");					// load channel 1 sample into buffer
	asm volatile ("End_T2_20us_div:	mov.b	[W2],[W0++]");					// load channel 2 sample into buffer
	asm volatile ("					mov.b	[W3],W2");						// read A/B channels from AD converter
	asm volatile ("					bra		T2_ChkSwap_Ch");


	// inline assembler for timebase 50us/div
	asm volatile ("T2_50us_div:		do		#4096,End_T2_50us_div");		//(PMP_LATENCY + NUMBER_OF_SAMPLES_PER_CHANNEL - 1)
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0++]");					// load channel 1 sample into buffer
	asm volatile ("End_T2_50us_div:	mov.b	[W2],[W0++]");					// load channel 2 sample into buffer
	asm volatile ("					mov.b	[W3],W2");						// read A/B channels from AD converter
	asm	volatile ("T2_ChkSwap_Ch:	and		#64,W2");
	asm volatile ("					bra		NZ,End_T2_Sampling ");
	asm	volatile ("					dec		W0,W0");
	asm	volatile ("					dec		W0,W1");
	asm volatile ("					repeat	#8193");						//(2 * (PMP_LATENCY + NUMBER_OF_SAMPLES_PER_CHANNEL - 1)
	asm volatile ("					mov.b	[W1--],[W0--]");				// load samples into buffer
	asm volatile ("					bra		End_T2_Sampling");


	// inline assembler for timebase 0.1ms/div or slower
	asm volatile ("T2_100us_div:	clr		TMR5HLD");						// TMR5HLD = 0;
	asm volatile ("					mov		#18,W1");						// preload 18 cycles
	asm volatile ("					mov		W1,TMR4");
	asm volatile ("					bclr	IFS1,#12");						// _T5IF = 0;
	asm volatile ("					bset	IEC1,#12");						// _T5IE = 1;
	asm volatile ("					bset	T4CON,#15");					// T4CONbits.TON = 1;

	asm volatile ("					mov.b	[W2],[W0]");					// pmp pipeline latency
	asm volatile ("					mov.b	[W2],[W0++]");					// load ad sample of channel 1 into buffer
	asm volatile ("					mov.b	[W2],[W0++]");					// load ad sample of channel 2 into buffer
	asm volatile ("					mov.b	[W2],[W0]");					// load ad sample of channel 1 into buffer
	asm volatile ("					mov.b	[W3],W2");						// read A/B channels from AD converter

	asm volatile ("					mov		W0, _ptr_sample_buffer");		// store new buffer location

	asm	volatile ("					and		#64,W2");						// check for swapping channels
	asm volatile ("					bra		Z,End_T2_1Sample");
	asm	volatile ("					dec		W0,W0");						// swap channels
	asm	volatile ("					dec		W0,W1");
	asm volatile ("					mov.b	[W0++],[W1++]");
	asm volatile ("					mov.b	[W0++],[W1++]");

	asm volatile ("End_T2_1Sample:	mov		_sample_nr,W0");				// increment sample counter
	asm volatile ("					inc		W0, W0");
	asm volatile ("					mov		W0, _sample_nr");

	mStartSendTimer();

	// disable autotrigger timer
	asm volatile ("End_T2_Sampling:	bclr	IEC0,#8");						// (bclr	IEC0,#T3IE) mDisAutoTrigTimerInt();

	// disable external trigger channel 1 interrupt
	mDisTrig2Interrupts();
}


//------------------------------------------------------------------------------
// Method		: _T3Interrupt
// Description	: Interrupt service routine (ISR) for the Timer3 Interrupt
//				: This interrupt occurs when no external triggering happens in 100ms.
//				: The ISR name is chosen from the device linker script.
// Parameters	: none
// Return		: void
//------------------------------------------------------------------------------
void __attribute__((interrupt, shadow, no_auto_psv)) mAutoTrigInterrupt(VOID)
{
	asm volatile ("					mov		_ptr_sample_buffer,W0");		// load buffer location
	asm volatile ("					mov		_timebase_index,W1");			// load timebase index
	asm volatile ("					mov		#PMDIN1,W2");					// load PMP read address
	asm volatile ("					mov		#PORTG,W3");					// load PortG read address

	asm volatile ("					cp.b	W1,#6");						// Timebase equal or slower than 0.1ms/div
	asm volatile ("					bra		NN,AT_100us_div");				// yes

	asm volatile ("					bra		W1");
	asm volatile ("					bra		AT_1us_div");
	asm volatile ("					bra		AT_1us_div");
	asm volatile ("					bra		AT_1us_div");
	asm volatile ("					bra		AT_10us_div");
	asm volatile ("					bra		AT_20us_div");
	asm volatile ("					bra		AT_50us_div");

	// inline assembler for timebase 1us/div, 2us/div & 5us/div
	asm volatile ("AT_1us_div:		repeat	#8193");						//(2 * (PMP_LATENCY + NUMBER_OF_SAMPLES_PER_CHANNEL - 1)
	asm volatile ("					mov.b	[W2],[W0++]");					// load samples into buffer
	asm volatile ("					mov.b	[W3],W2");						// read A/B channels from AD converter
	asm volatile ("					bra		AT_ChkSwap_Ch");

	// inline assembler for timebase 10us/div
	asm volatile ("AT_10us_div:		do		#4096,End_AT_10us_div");		//(PMP_LATENCY + NUMBER_OF_SAMPLES_PER_CHANNEL - 1)
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0++]");					// load channel 1 sample into buffer
	asm volatile ("End_AT_10us_div:	mov.b	[W2],[W0++]");					// load channel 2 sample into buffer
	asm volatile ("					mov.b	[W3],W2");						// read A/B channels from AD converter
	asm volatile ("					bra		AT_ChkSwap_Ch");

	// inline assembler for timebase 20us/div
	asm volatile ("AT_20us_div:		do		#4096,End_AT_20us_div");		//(PMP_LATENCY + NUMBER_OF_SAMPLES_PER_CHANNEL - 1)
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0++]");					// load channel 1 sample into buffer
	asm volatile ("End_AT_20us_div:	mov.b	[W2],[W0++]");					// load channel 2 sample into buffer
	asm volatile ("					mov.b	[W3],W2");						// read A/B channels from AD converter
	asm volatile ("					bra		AT_ChkSwap_Ch");


	// inline assembler for timebase 50us/div
	asm volatile ("AT_50us_div:		do		#4096,End_AT_50us_div");		//(PMP_LATENCY + NUMBER_OF_SAMPLES_PER_CHANNEL - 1)
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0]");
	asm volatile ("					mov.b	[W2],[W0++]");					// load channel 1 sample into buffer
	asm volatile ("End_AT_50us_div:	mov.b	[W2],[W0++]");					// load channel 2 sample into buffer
	asm volatile ("					mov.b	[W3],W2");						// read A/B channels from AD converter
	asm	volatile ("AT_ChkSwap_Ch:	and		#64,W2");
	asm volatile ("					bra		NZ,End_AT_Sampling ");
	asm	volatile ("					dec		W0,W0");
	asm	volatile ("					dec		W0,W1");
	asm volatile ("					repeat	#8193");						//(2 * (PMP_LATENCY + NUMBER_OF_SAMPLES_PER_CHANNEL) - 1)
	asm volatile ("					mov.b	[W1--],[W0--]");				// load samples into buffer
	asm volatile ("					bra		End_AT_Sampling");


	// inline assembler for timebase 0.1ms/div or slower
	asm volatile ("AT_100us_div:	clr		TMR5HLD");						// TMR5HLD = 0;
	asm volatile ("					mov		#18,W1");						// preload 18 cycles
	asm volatile ("					mov		W1,TMR4");
	asm volatile ("					bclr	IFS1,#12");						// _T5IF = 0;
	asm volatile ("					bset	IEC1,#12");						// _T5IE = 1;
	asm volatile ("					bset	T4CON,#15");					// T4CONbits.TON = 1;

	asm volatile ("					mov.b	[W2],[W0]");					// pmp pipeline latency
	asm volatile ("					mov.b	[W2],[W0++]");					// load ad sample of channel 1 into buffer
	asm volatile ("					mov.b	[W2],[W0++]");					// load ad sample of channel 2 into buffer
	asm volatile ("					mov.b	[W2],[W0]");					// load ad sample of channel 1 into buffer
	asm volatile ("					mov.b	[W3],W2");						// read A/B channels from AD converter

	asm volatile ("					mov		W0, _ptr_sample_buffer");		// store new buffer location

	asm	volatile ("					and		#64,W2");						// check for swapping channels
	asm volatile ("					bra		Z,End_AT_1Sample");
	asm	volatile ("					dec		W0,W0");						// swap channels
	asm	volatile ("					dec		W0,W1");
	asm volatile ("					mov.b	[W0++],[W1++]");
	asm volatile ("					mov.b	[W0++],[W1++]");

	asm volatile ("End_AT_1Sample:	mov		_sample_nr,W0");				// increment sample counter
	asm volatile ("					inc		W0, W0");
	asm volatile ("					mov		W0, _sample_nr");

	mStartSendTimer();

	// disable autotrigger timer
	asm volatile ("End_AT_Sampling:	bclr	IEC0,#8");						// (bclr	IEC0,#T3IE) mDisAutoTrigTimerInt();

	// disable external trigger interrupts
	mDisTrigInterrupts();
}



//------------------------------------------------------------------------------
// Method		: _T5Interrupt
// Description	: Interrupt service routine (ISR) for the Timer5 Interrupt
//				: This interrupt is used for one sample
// Parameters	: none
// Return		: void
//------------------------------------------------------------------------------
void __attribute__((interrupt, shadow, no_auto_psv)) mTimebaseInterrupt(VOID)
{
	asm volatile ("				mov		_ptr_sample_buffer,W0");		// load buffer location

	asm volatile ("				mov		#PMDIN1,W2");					// load PMP read address
	asm volatile ("				mov		#PORTG,W3");					// load PortG read address

	asm volatile ("				mov.b	[W2],[W0]");					// pmp pipeline latency
	asm volatile ("				mov.b	[W2],[W0++]");					// load ad sample of channel 1 into buffer
	asm volatile ("				mov.b	[W2],[W0++]");					// load ad sample of channel 2 into buffer
	asm volatile ("				mov.b	[W2],[W0]");					// load ad sample of channel 1 into buffer
	asm volatile ("				mov.b	[W3],W2");						// read A/B channels from AD converter

	asm volatile ("				mov		W0, _ptr_sample_buffer");		// store new buffer location

	asm	volatile ("				and		#64,W2");						// check for swapping channels
	asm volatile ("				bra		Z,End_1Sample");
	asm	volatile ("				dec		W0,W0");						// swap channels
	asm	volatile ("				dec		W0,W1");
	asm volatile ("				mov.b	[W0++],[W1++]");
	asm volatile ("				mov.b	[W0++],[W1++]");

	asm volatile ("End_1Sample:	mov		_sample_nr,W0");				// increment sample counter
	asm volatile ("				inc		W0, W0");
	asm volatile ("				mov		W0, _sample_nr");

	asm volatile ("				mov		#4096,W1");						// last sample?
	asm volatile ("				cpsne	W0, W1");						// if 'samplecounter' not equal with 'number of samples per channel' skip disabling the timebase interrupt
	mDisTimebaseTimerInt();												// last sample -> disabling the timebase interrupt

	mClrTimebaseTimerIntFlag();
}


