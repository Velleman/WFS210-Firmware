#include "WFS210/wfs210_process.h"

// program application space:		0x000000 ... 0x025FFE
// program flash calibration data:	0x026000 ... 0x0267FE
// program flash reserved data:		0x026800 ... 0x028FF8
// program flash checksum data:		0x028FFA


int __attribute__((space(prog),address(0x026000), aligned(_FLASH_PAGE * 2))) CalibrationData[_FLASH_PAGE];

int __attribute__((space(prog),address(0x026800), aligned(_FLASH_PAGE * 2))) ReservedFlash[5 * _FLASH_PAGE - 3];




VOID LoadCalibrationData(VOID)
{
	_prog_addressT p;
	unsigned int len;

	len = sizeof(calibration.ch1_offset) + sizeof(calibration.ch2_offset)
		  + sizeof(calibration.ch1_lower_center) + sizeof(calibration.ch1_upper_center)
		  + sizeof(calibration.ch2_lower_center) + sizeof(calibration.ch2_upper_center)
		  + sizeof(calibration.trigger_lower_center) + sizeof(calibration.trigger_upper_center);

	_init_prog_address(p, CalibrationData);
	_memcpy_p2d16(&calibration, p, len);
}


VOID StoreCalibrationData(VOID)
{
	_prog_addressT p;
	unsigned int len;
	static int buffer[_FLASH_ROW];

	memset(buffer, 0xFF, sizeof(buffer));
	len = sizeof(calibration.ch1_offset) + sizeof(calibration.ch2_offset)
		  + sizeof(calibration.ch1_lower_center) + sizeof(calibration.ch1_upper_center)
		  + sizeof(calibration.ch2_lower_center) + sizeof(calibration.ch2_upper_center)
		  + sizeof(calibration.trigger_lower_center) + sizeof(calibration.trigger_upper_center);
	memcpy(buffer, &calibration, len);

	_init_prog_address(p, CalibrationData);
	_erase_flash(p);
	_write_flash16(p, buffer);
}



VOID InitCalibration(VOID)
{

	memset(&calibration, 0, sizeof(calibration));

	SetInputCouplingCh1(REFGND);
	SetVoltDivCh1(CH_5MV_DIV);
	SetYposCh1(YPOS_CENTER);
	SetInputCouplingCh2(REFGND);
	SetVoltDivCh2(CH_5MV_DIV);
	SetYposCh2(YPOS_CENTER);
	SetTimebase(CH_0P5MS_DIV);
	SetTrigLevel(TRIG_LVL_BOTTOM);
	SetTriggering(0);
	scope_settings.status.flags.trigger_mode = AUTO;

	TransmitStatus(&wfs210out);

	calibration.sm = SM_Y_CENTER_5MV_DIV;
	calibration.ch1_done = FALSE;
	calibration.ch2_done = FALSE;
	calibration.pwm_min_Ch1 = calibration.pwm_min_Ch2 = 0;
	calibration.pwm_max_Ch1 = calibration.pwm_max_Ch2 = PWM_PERIOD;
}


DWORD SumSamples(WORD ch)
{
	WORD i;
	DWORD sum = 0;

	for (i = 2 * PMP_LATENCY + ch; i < 2 * (PMP_LATENCY + NUMBER_OF_SAMPLES_PER_CHANNEL); i += 2)
		sum += sample_buffer[i];

	return sum;
}



BOOL CalibrateY(BYTE Target)
{
	DWORD sum;

	if (!calibration.ch1_done)
	{
		sum = SumSamples(CH1);
		if (sum < (((DWORD)Target * NUMBER_OF_SAMPLES_PER_CHANNEL) - (NUMBER_OF_SAMPLES_PER_CHANNEL / 8)))
		{
			calibration.pwm_min_Ch1 = mDuty_Cycle_Ypos_Ch1;
			mDuty_Cycle_Ypos_Ch1 = (mDuty_Cycle_Ypos_Ch1 + calibration.pwm_max_Ch1) / 2;
		}
		else if (sum > ((DWORD)Target * NUMBER_OF_SAMPLES_PER_CHANNEL) + (NUMBER_OF_SAMPLES_PER_CHANNEL / 8))
		{
			calibration.pwm_max_Ch1 = mDuty_Cycle_Ypos_Ch1;
			mDuty_Cycle_Ypos_Ch1 = (mDuty_Cycle_Ypos_Ch1 + calibration.pwm_min_Ch1) / 2;
		}
		else calibration.ch1_done = TRUE;
	}

	if (!calibration.ch2_done)
	{
		sum = SumSamples(CH2);
		if (sum < (((DWORD)Target * NUMBER_OF_SAMPLES_PER_CHANNEL) - (NUMBER_OF_SAMPLES_PER_CHANNEL / 8)))
		{
			calibration.pwm_min_Ch2 = mDuty_Cycle_Ypos_Ch2;
			mDuty_Cycle_Ypos_Ch2 = (mDuty_Cycle_Ypos_Ch2 + calibration.pwm_max_Ch2) / 2;
		}
		else if (sum > ((DWORD)Target * NUMBER_OF_SAMPLES_PER_CHANNEL) + (NUMBER_OF_SAMPLES_PER_CHANNEL / 8))
		{
			calibration.pwm_max_Ch2 = mDuty_Cycle_Ypos_Ch2;
			mDuty_Cycle_Ypos_Ch2 = (mDuty_Cycle_Ypos_Ch2 + calibration.pwm_min_Ch2) / 2;
		}
		else calibration.ch2_done = TRUE;
	}

	if (calibration.ch1_done && calibration.ch2_done) return TRUE; else return FALSE;
}


VOID CalibrateYupperCenter(VOID)
{
	if (CalibrateY(YPOS_UPPER_CENTER))
	{
		// load y-offset calibration factor
		calibration.ch1_upper_center =  mDuty_Cycle_Ypos_Ch1 - calibration.ch1_offset[CH_50MV_DIV];
		calibration.ch2_upper_center =  mDuty_Cycle_Ypos_Ch2 - calibration.ch2_offset[CH_50MV_DIV];

		calibration.ch1_done = FALSE;
		calibration.ch2_done = FALSE;
		calibration.pwm_min_Ch1 = calibration.pwm_min_Ch2 = 0;
		calibration.pwm_max_Ch1 = calibration.pwm_max_Ch2 = PWM_PERIOD;

		calibration.sm++;
	}
}


VOID CalibrateYcenter(VOID)
{
	BYTE i;

	if (CalibrateY(YPOS_CENTER))
	{
		// load y-offset calibration factor
		i = scope_settings.sensitivityCh1;
		calibration.ch1_offset[i] = calibration.ch1_offset[i - 4] = calibration.ch1_offset[i - 8] =  mDuty_Cycle_Ypos_Ch1 - (YPOS_CENTER << 7);
		calibration.ch2_offset[i] = calibration.ch2_offset[i - 4] = calibration.ch2_offset[i - 8] =  mDuty_Cycle_Ypos_Ch2 - (YPOS_CENTER << 7);
		if (i == CH_50MV_DIV)
		{
			calibration.ch1_offset[CH_OFF_V_DIV] = calibration.ch1_offset[CH_20V_DIV];
			calibration.ch2_offset[CH_OFF_V_DIV] = calibration.ch2_offset[CH_20V_DIV];
		}

		calibration.ch1_done = FALSE;
		calibration.ch2_done = FALSE;
		calibration.pwm_min_Ch1 = calibration.pwm_min_Ch2 = 0;
		calibration.pwm_max_Ch1 = calibration.pwm_max_Ch2 = PWM_PERIOD;


		if (i > CH_50MV_DIV)
		{
			// update V/div setting
			i--;
			SetVoltDivCh1(i);
			SetVoltDivCh2(i);
			TransmitStatus(&wfs210out);
			calibration.sm++;
		}
		else
			calibration.sm++;
	}
}


VOID CalibrateYlowerCenter(VOID)
{
	if (CalibrateY(YPOS_LOWER_CENTER))
	{
		// load y-offset calibration factor
		calibration.ch1_lower_center =  mDuty_Cycle_Ypos_Ch1 - calibration.ch1_offset[CH_50MV_DIV];
		calibration.ch2_lower_center =  mDuty_Cycle_Ypos_Ch2 - calibration.ch2_offset[CH_50MV_DIV];

		calibration.ch1_done = FALSE;
		calibration.ch2_done = FALSE;
		calibration.pwm_min_Ch1 = calibration.pwm_min_Ch2 = 0;
		calibration.pwm_max_Ch1 = calibration.pwm_max_Ch2 = PWM_PERIOD;

		calibration.sm++;
	}
}



BOOL CalibrateTrigger(VOID)
{
	if ((calibration.pwm_max_Ch1 - calibration.pwm_min_Ch1) > 2)
	{
		if (mPORT_Trig1)
		{
			calibration.pwm_max_Ch1 = mDuty_Cycle_Trig_Level;
			mDuty_Cycle_Trig_Level = (calibration.pwm_min_Ch1 + calibration.pwm_max_Ch1) / 2;
		}
		else
		{
			calibration.pwm_min_Ch1 = mDuty_Cycle_Trig_Level;
			mDuty_Cycle_Trig_Level = (calibration.pwm_min_Ch1 + calibration.pwm_max_Ch1) / 2;
		}
		return FALSE;
	}
	else return TRUE;
}

VOID CalibrateTrigLowerCenter(VOID)
{
	SetYposCh1(YPOS_LOWER_CENTER);
	if (CalibrateTrigger())
	{
		calibration.trigger_lower_center = mDuty_Cycle_Trig_Level;

		SetYposCh1(YPOS_UPPER_CENTER);

		calibration.pwm_min_Ch1 = calibration.pwm_min_Ch2 = 0;
		calibration.pwm_max_Ch1 = calibration.pwm_max_Ch2 = PWM_PERIOD;
		mDuty_Cycle_Trig_Level = 0;

		calibration.sm++;
	}
}


VOID CalibrateTrigUpperCenter(VOID)
{
	SetYposCh1(YPOS_UPPER_CENTER);
	if (CalibrateTrigger())
	{
		calibration.trigger_upper_center = mDuty_Cycle_Trig_Level;

		calibration.sm++;
	}
}






VOID StartCalibration(VOID)
{
	calibration.sm = SM_INIT;
	scope_settings.status.flags.calibrating = TRUE;
	scope_settings.status.flags.trigger_mode = AUTO;
	if (sampling_sm == SM_IDLE) sampling_sm = SM_SAMPLING_START;
}


VOID ExitCalibration(VOID)
{
	StoreCalibrationData();
	calibration.sm = SM_IDLE;
	scope_settings.status.flags.calibrating = FALSE;
	SetInputCouplingCh1(AC);
	SetVoltDivCh1(CH_OFF_V_DIV);
	SetYposCh1(YPOS_CENTER);
	SetInputCouplingCh2(AC);
	SetVoltDivCh2(CH_OFF_V_DIV);
	SetYposCh2(YPOS_CENTER);
	SetTimebase(CH_5US_DIV);
	SetTrigLevel(TRIG_LVL_CENTER);
	SetTriggering(0);
	scope_settings.status.flags.trigger_mode = AUTO;
	TransmitStatus(&wfs210out);
}


VOID CalibrationTask(VOID)
{
	switch (calibration.sm)
	{
		case SM_INIT: InitCalibration(); break;
		case SM_Y_CENTER_5MV_DIV: 
		case SM_Y_CENTER_10MV_DIV:
		case SM_Y_CENTER_20MV_DIV:
		case SM_Y_CENTER_50MV_DIV: CalibrateYcenter(); break;
		case SM_Y_UPPER_CENTER: CalibrateYupperCenter(); break;
		case SM_Y_LOWER_CENTER: CalibrateYlowerCenter(); break;
		case SM_TRIG_LOWER_CENTER: CalibrateTrigLowerCenter(); break;
		case SM_TRIG_UPPER_CENTER: CalibrateTrigUpperCenter(); break;
		case SM_DONE: ExitCalibration();
	}
}

