#include "WFS210/wfs210_process.h"

extern volatile BOOL	autotimebase_found;

const DWORD timebase_switch_faster[CH_10MS_DIV] = {
	     0, //   1탎/div
	   400, //   2탎/div : > 100kHz switch to   1탎/div
	   800, //   5탎/div : >  50kHz switch to   2탎/div
	  2000, //  10탎/div : >  20kHz switch to   5탎/div
	  4000, //  20탎/div : >  10kHz switch to  10탎/div
	  8000, //  50탎/div : >   5kHz switch to  20탎/div
	 20000, // 100탎/div : >   2kHz switch to  50탎/div
	 40000, // 200탎/div : >   1kHz switch to 100탎/div
	 80000, // 500탎/div : >  500Hz switch to 200탎/div
	200000, //   1ms/div : >  200Hz switch to 500탎/div
	400000, //   2ms/div : >  100Hz switch to   1ms/div
	800000  //   5ms/div : >   50Hz switch to   2ms/div
};


const DWORD timebase_switch_slower[CH_10MS_DIV] = {
	   500, //   1탎/div : <  80kHz switch to   2탎/div
	  1000, //   2탎/div : <  40kHz switch to   5탎/div
	  2500, //   5탎/div : <  16kHz switch to  10탎/div
	  5000, //  10탎/div : <   8kHz switch to  20탎/div
	 10000, //  20탎/div : <   4kHz switch to  50탎/div
	 25000, //  50탎/div : < 1600Hz switch to 100탎/div
	 50000, // 100탎/div : <  800Hz switch to 200탎/div
	100000, // 200탎/div : <  400Hz switch to 500탎/div
	250000, // 500탎/div : <  160Hz switch to   1ms/div
	500000, //   1ms/div : <   80Hz switch to   2ms/div
   1000000, //   2ms/div : <   40Hz switch to   5ms/div
 100000000, //   5ms/div :
};


BYTE SampleMin(WORD ch)
{
	WORD i;
	BYTE min = 0xFF;

	for (i = 2 * PMP_LATENCY + ch; i < 2 * (PMP_LATENCY + NUMBER_OF_SAMPLES_PER_CHANNEL); i += 2)
	{
		if (sample_buffer[i] < min) min = sample_buffer[i];
	}
	return min;
}


BYTE SampleMax(WORD ch)
{
	WORD i;
	BYTE max = 0;

	for (i = 2 * PMP_LATENCY + ch; i < 2 * (PMP_LATENCY + NUMBER_OF_SAMPLES_PER_CHANNEL); i += 2)
	{
		if (sample_buffer[i] > max) max = sample_buffer[i];
	}
	return max;
}


VOID CheckAutoVolt(VOID)
{
	BYTE min, max;

	if ((scope_settings.status.flags.calibrating) || (!scope_settings.status.flags.autorange))
	{
		sampling_sm = SM_SAMPLING;
		return;
	}

	else
	{
		if (scope_settings.sensitivityCh1 != CH_OFF_V_DIV)
		{
			min = SampleMin(CH1);
			max = SampleMax(CH1);
			if ((scope_settings.sensitivityCh1 != CH_20V_DIV) && ((min < SAMPLE_MIN) || (max > SAMPLE_MAX)))
			{
				scope_settings.sensitivityCh1--;
				SetVoltDivCh1(scope_settings.sensitivityCh1);
				TransmitStatus(&wfs210out);
			}
			else if ((scope_settings.sensitivityCh1 != CH_5MV_DIV) && (min > SAMPLE_MIN_AUTORANGE) && (max < SAMPLE_MAX_AUTORANGE))
			{
				scope_settings.sensitivityCh1++;
				SetVoltDivCh1(scope_settings.sensitivityCh1);
				TransmitStatus(&wfs210out);
			}
		}

		if (scope_settings.sensitivityCh2 != CH_OFF_V_DIV)
		{
			min = SampleMin(CH2);
			max = SampleMax(CH2);
			if ((scope_settings.sensitivityCh2 != CH_20V_DIV) && ((min < SAMPLE_MIN) || (max > SAMPLE_MAX)))
			{
				scope_settings.sensitivityCh2--;
				SetVoltDivCh2(scope_settings.sensitivityCh2);
				TransmitStatus(&wfs210out);
			}
			else if ((scope_settings.sensitivityCh2 != CH_5MV_DIV) && (min > SAMPLE_MIN_AUTORANGE) && (max < SAMPLE_MAX_AUTORANGE))
			{
				scope_settings.sensitivityCh2++;
				SetVoltDivCh2(scope_settings.sensitivityCh2);
				TransmitStatus(&wfs210out);
			}
		}

		sampling_sm++;
	}
}



VOID StartAutoTimebase(VOID)
{
	autotimebase_found = FALSE;

	mInitICInputs();
	//mSetIC1RisingEdge();
	if (scope_settings.status.flags.trigger_channel == CH1)
	{
		mSetIC1RisingEdge();
		mSelectIC1();
	}
	else
	{
		mSetIC2RisingEdge();
		mSelectIC2();
	}
	mStartAutoTimebaseTimer();
	sampling_sm++;
}



VOID SetFasterTimebase(BYTE i)
{
	DWORD period;

	period = capture2.Val - capture1.Val;

	while (period < timebase_switch_faster[i]) i--;
	SetTimebase(i);
	TransmitStatus(&wfs210out);
}


VOID SetSlowerTimebase(BYTE i)
{
	DWORD period;

	period = capture2.Val - capture1.Val;

	while (period > timebase_switch_slower[i]) i++;
	SetTimebase(i);
	TransmitStatus(&wfs210out);
}



VOID SetAutoTimeBase(VOID)
{
	DWORD period;

	period = capture2.Val - capture1.Val;

	// check timebase at 1탎/div
	if (scope_settings.timebase == CH_1US_DIV)
	{
		if (period > timebase_switch_slower[CH_1US_DIV]) SetSlowerTimebase(CH_1US_DIV);
	}

	//check timebase at 5ms/div
	else if (scope_settings.timebase == CH_5MS_DIV)
	{
		if (period < timebase_switch_faster[CH_5MS_DIV]) SetFasterTimebase(CH_5MS_DIV);
	}

	// check timebase between 2탎/div and 2ms/div
	else if ((scope_settings.timebase > CH_1US_DIV) && (scope_settings.timebase < CH_5MS_DIV))
	{
		if (period < timebase_switch_faster[scope_settings.timebase]) SetFasterTimebase(scope_settings.timebase);
		else if (period > timebase_switch_slower[scope_settings.timebase]) SetSlowerTimebase(CH_1US_DIV);
	}

	else SetFasterTimebase(CH_5MS_DIV);

	sampling_sm++;
}






//------------------------------------------------------------------------------
// Method		: _IC1Interrupt
// Description	: Interrupt service routine (ISR) for the Input Capture Interrupt
//				: This interrupt occurs when an input capture happens on channel 1
//				: The ISR name is chosen from the device linker script.
// Parameters	: none
// Return		: void
//------------------------------------------------------------------------------

void __attribute__((interrupt, shadow, no_auto_psv)) mIC1Interrupt(VOID)
{
	// disable auto timebase timeout timer
	mStopAutoTimebaseTimer();
	mDisAutoTimebaseTimerInt();

	autotimebase_found = TRUE;

	capture1.word.LW = IC1BUF;
	capture1.word.HW = IC2BUF;
	capture2.word.LW = IC1BUF;
	capture2.word.HW = IC2BUF;

	// disable input capture channel 1 interrupt
	mDisIC1Interrupts();
}


//------------------------------------------------------------------------------
// Method		: _IC2Interrupt
// Description	: Interrupt service routine (ISR) for the Input Capture Interrupt
//				: This interrupt occurs when an input capture happens on channel 2
//				: The ISR name is chosen from the device linker script.
// Parameters	: none
// Return		: void
//------------------------------------------------------------------------------

void __attribute__((interrupt, shadow, no_auto_psv)) mIC2Interrupt(VOID)
{
	// disable auto timebase timeout timer
	mStopAutoTimebaseTimer();
	mDisAutoTimebaseTimerInt();

	autotimebase_found = TRUE;

	capture1.word.LW = IC3BUF;
	capture1.word.HW = IC4BUF;
	capture2.word.LW = IC3BUF;
	capture2.word.HW = IC4BUF;

	// disable input capture channel 2 interrupt
	mDisIC2Interrupts();
}


//------------------------------------------------------------------------------
// Method		: _IC1Interrupt
// Description	: Interrupt service routine (ISR) for the Input Capture Interrupt
//				: This interrupt occurs when an input capture happens on channel 1
//				: The ISR name is chosen from the device linker script.
// Parameters	: none
// Return		: void
//------------------------------------------------------------------------------

void __attribute__((interrupt, shadow, no_auto_psv)) mAutoTimebaseInterrupt(VOID)
{
	// disable auto timebase timeout timer
	mStopAutoTimebaseTimer();
	mDisAutoTimebaseTimerInt();

	// disable input capture interrupts
	mDisIC1Interrupts();
	mDisIC2Interrupts();

	autotimebase_found = TRUE;

	capture1.Val = 0;
	capture2.Val = 2000000;
}

