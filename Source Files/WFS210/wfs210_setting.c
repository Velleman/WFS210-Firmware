#include "WFS210/wfs210_process.h"
#include "wfs210/wfs210_hal.h"


VOID InitSettings(VOID)
{
	// initialize comparator module
	InitLowVoltage();

	// Initialize all pins
	mInitAnalogPower();
	mInitFactoryDefaultsPB();
	mInitChargerPins();
	mInitTrisCh1();
	mSwitchOffCh1();
	mInitTrisCh2();
	mSwitchOffCh2();
	mInitADCPins();
	mIdleADC();

	// Initialize PWM modules
	mInitYposCh1();
	mInitYposCh2();
	mInitTrigLevel();

	// Initialize PMP modules
	mInitPMP();

	TRISBbits.TRISB15 = INPUT_PIN;

	// Initialize Trigger inputs
	mDisICInputs();
	mInitTrigInputs();

	// set AD converter into run mode
	mRunADC();

	// load calibration data for Yposition and trigger level
	LoadCalibrationData();

	// initialize scope settings
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

	InitSampleBuffer();

	sampling_sm = SM_IDLE;
	
	#ifdef DEBUGGING
		SetWifiDebugMode(TRUE);
		WFS210SetUSBDebugMode(TRUE);
	#else
		SetWifiDebugMode(FALSE);
		WFS210SetUSBDebugMode(FALSE);
	#endif

}

VOID SetScopeDebugMode(BOOL debug)
{
	scope_settings.status.flags.debug = debug;
}


VOID ReadChargerStatus(VOID)
{
	scope_settings.status.flags.charger_PG =	mGetChargerPG();
	scope_settings.status.flags.charger_stat1 =	mGetChargerStat1();
	scope_settings.status.flags.charger_stat2 =	mGetChargerStat2();
}


VOID SetInputCouplingCh1(BYTE index)
{
	scope_settings.couplingCh1 = index;
	switch (index)
	{
		case AC:		mSetAcCh1(); SetVoltDivCh1(scope_settings.sensitivityCh1); break;
		case DC:		mSetDcCh1(); SetVoltDivCh1(scope_settings.sensitivityCh1); break;
		case REFGND:	mSetGndCh1(); break;
	}
}


VOID SetInputCouplingCh2(BYTE index)
{
	scope_settings.couplingCh2 = index;
	switch (index)
	{
		case AC:		mSetAcCh2(); SetVoltDivCh2(scope_settings.sensitivityCh2); break;
		case DC:		mSetDcCh2(); SetVoltDivCh2(scope_settings.sensitivityCh2); break;
		case REFGND:	mSetGndCh2(); break;
	}
}


VOID SetVoltDivCh1(BYTE index)
{
	scope_settings.sensitivityCh1 = index;
	switch (index)
	{
		case CH_OFF_V_DIV:	mSwitchOffCh1(); break;
		case CH_20V_DIV:	mSet20VdivCh1(); break;
		case CH_10V_DIV:	mSet10VdivCh1(); break;
		case CH_4V_DIV:		mSet4VdivCh1(); break;
		case CH_2V_DIV:		mSet2VdivCh1(); break;
		case CH_1V_DIV:		mSet1VdivCh1(); break;
		case CH_0P5V_DIV:	mSet0p5VdivCh1(); break;
		case CH_0P2V_DIV:	mSet0p2VdivCh1(); break;
		case CH_0P1V_DIV:	mSet0p1VdivCh1(); break;
		case CH_50MV_DIV:	mSet50mVdivCh1(); break;
		case CH_25MV_DIV:	mSet25mVdivCh1(); break;
		case CH_10MV_DIV:	mSet10mVdivCh1(); break;
		case CH_5MV_DIV:	mSet5mVdivCh1(); break;
	}
	SetYposCh1(scope_settings.ypositionCh1);
	
	if (scope_settings.couplingCh1 == REFGND) mSetGndCh1();
}


VOID SetVoltDivCh2(BYTE index)
{
	scope_settings.sensitivityCh2 = index;
	switch (index)
	{
		case CH_OFF_V_DIV:	mSwitchOffCh2(); break;
		case CH_20V_DIV:	mSet20VdivCh2(); break;
		case CH_10V_DIV:	mSet10VdivCh2(); break;
		case CH_4V_DIV:		mSet4VdivCh2(); break;
		case CH_2V_DIV:		mSet2VdivCh2(); break;
		case CH_1V_DIV:		mSet1VdivCh2(); break;
		case CH_0P5V_DIV:	mSet0p5VdivCh2(); break;
		case CH_0P2V_DIV:	mSet0p2VdivCh2(); break;
		case CH_0P1V_DIV:	mSet0p1VdivCh2(); break;
		case CH_50MV_DIV:	mSet50mVdivCh2(); break;
		case CH_25MV_DIV:	mSet25mVdivCh2(); break;
		case CH_10MV_DIV:	mSet10mVdivCh2(); break;
		case CH_5MV_DIV:	mSet5mVdivCh2(); break;
	}
	SetYposCh2(scope_settings.ypositionCh2);

	if (scope_settings.couplingCh2 == REFGND) mSetGndCh2();}

VOID SetYposCh1(BYTE index)
{
	int duty_cycle;

	scope_settings.ypositionCh1 = index;
	duty_cycle = calibration.ch1_upper_center - ((calibration.ch1_lower_center - calibration.ch1_upper_center) / 2);
	duty_cycle += (((calibration.ch1_lower_center - calibration.ch1_upper_center) * (long)index) / (YPOS_LOWER_CENTER - YPOS_UPPER_CENTER));
	duty_cycle += calibration.ch1_offset[scope_settings.sensitivityCh1];
	mDuty_Cycle_Ypos_Ch1 = duty_cycle;
}

VOID SetYposCh2(BYTE index)
{
	int duty_cycle;

	scope_settings.ypositionCh2 = index;
	duty_cycle = calibration.ch2_upper_center - ((calibration.ch2_lower_center - calibration.ch2_upper_center) / 2);
	duty_cycle += (((calibration.ch2_lower_center - calibration.ch2_upper_center) * (long)index) / (YPOS_LOWER_CENTER - YPOS_UPPER_CENTER));
	duty_cycle += calibration.ch2_offset[scope_settings.sensitivityCh2];
	mDuty_Cycle_Ypos_Ch2 = duty_cycle;
}

VOID SetTrigLevel(BYTE index)
{
	int duty_cycle;

	scope_settings.triglevel = index;
	duty_cycle = calibration.trigger_upper_center + ((calibration.trigger_upper_center - calibration.trigger_lower_center) / 2);
	duty_cycle -= (((calibration.trigger_upper_center - calibration.trigger_lower_center) * (long)index) / (YPOS_LOWER_CENTER - YPOS_UPPER_CENTER));
	mDuty_Cycle_Trig_Level = duty_cycle;
}

VOID SetTimebase(BYTE index)
{
	scope_settings.timebase = index;
	mStopTimebaseTimer();
	switch (index)
	{
		case CH_1US_DIV: mOpenTimebaseTimer(CH_1US_DIV_PERIOD);  break;
		case CH_2US_DIV: mOpenTimebaseTimer(CH_2US_DIV_PERIOD);  break;
		case CH_5US_DIV: mOpenTimebaseTimer(CH_5US_DIV_PERIOD);  break;
		case CH_10US_DIV: mOpenTimebaseTimer(CH_10US_DIV_PERIOD);  break;
		case CH_20US_DIV: mOpenTimebaseTimer(CH_20US_DIV_PERIOD);  break;
		case CH_50US_DIV: mOpenTimebaseTimer(CH_50US_DIV_PERIOD);  break;
		case CH_0P1MS_DIV: mOpenTimebaseTimer(CH_0P1MS_DIV_PERIOD);  break;
		case CH_0P2MS_DIV: mOpenTimebaseTimer(CH_0P2MS_DIV_PERIOD);  break;
		case CH_0P5MS_DIV: mOpenTimebaseTimer(CH_0P5MS_DIV_PERIOD);  break;
		case CH_1MS_DIV: mOpenTimebaseTimer(CH_1MS_DIV_PERIOD);  break;
		case CH_2MS_DIV: mOpenTimebaseTimer(CH_2MS_DIV_PERIOD);  break;
		case CH_5MS_DIV: mOpenTimebaseTimer(CH_5MS_DIV_PERIOD);  break;
		case CH_10MS_DIV: mOpenTimebaseTimer(CH_10MS_DIV_PERIOD);  break;
		case CH_20MS_DIV: mOpenTimebaseTimer(CH_20MS_DIV_PERIOD);  break;
		case CH_50MS_DIV: mOpenTimebaseTimer(CH_50MS_DIV_PERIOD);  break;
		case CH_0P1S_DIV: mOpenTimebaseTimer(CH_0P1S_DIV_PERIOD);  break;
		case CH_0P2S_DIV: mOpenTimebaseTimer(CH_0P2S_DIV_PERIOD);  break;
		case CH_0P5S_DIV: mOpenTimebaseTimer(CH_0P5S_DIV_PERIOD);  break;
		case CH_1S_DIV: mOpenTimebaseTimer(CH_1S_DIV_PERIOD);  break;
	}
}

VOID SetTriggering(BYTE setting)
{
	scope_settings.status.byte.LB = setting;

	// set trigger slope
	if (scope_settings.status.flags.trigger_slope)
		mSetTrigFallingEdge()
	else
		mSetTrigRisingEdge()
}




