#include "wfs210/wfs210_process.h"
#include <Generic.h>

WORD				low_voltage_sm;
WORD				sleep_timer;
volatile DWORD_VAL	capture1, capture2;
WORD				sampling_sm;
WFS210_SETTINGS		scope_settings;
WFS210_CALIBRATION	calibration;
WFS210_OUT_PACKET	wfs210out;


VOID WFS210Init(VOID)
{
	// Initialize all io's and settings
	InitSettings();

	// Initialize wifi module
	WifiInit();

	// Initialize usb module
	WFS210USBInit();

	// start sleep timer
	sleep_timer = SLEEP_TIME_OUT;
	mStartSleepTimer();
}


VOID WFS210Sleep(VOID)
{
	mSwitchOffCh1();
	mSwitchOffCh2();
	mShutdownADC();
	mDisAnalogPower();
	CM1CONbits.CON = 0;		// comparator is disabled
	CVRCONbits.CVREN = 0;	// comparator voltage reference circuit powered down

	// led on indication
	mTRIS_Wifi_Tcp_Con = OUTPUT_PIN;
	mLAT_Wifi_Tcp_Con = 1;

	Sleep();
}

VOID SleepTask(VOID)
{

	if (mGetChargerPower() || WifiConnected()) sleep_timer = SLEEP_TIME_OUT;
	else if (mGetSleepTimerIntFlag())
	{
		mGetSleepTimerIntFlag()	= FALSE;
		if (sleep_timer != 0)
		{
			sleep_timer--;
			if (sleep_timer == 0) wifi.cmd_out.sm = SM_START_SLEEP;
		}
	}
}


VOID WFS210Tasks(VOID)
{
	SleepTask();
	LowVoltageTask();
	ScopeTasks();
	TransmitTask();
	WFS210USBTasks();
	WifiTasks();
}





