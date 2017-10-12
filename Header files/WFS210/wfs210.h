/* 
 * File:   scope.h
 * Author: edc
 *
 * Created on 27 juni 2013, 16:36
 */

#ifndef WFS210_H
#define	WFS210_H


#include "common.h"
#include "wfs210/wfs210_protocol.h"
#include "wfs210/wfs210_usb.h"
#include "wfs210/wifi.h"


#define BUILD	"1423"

#define SLEEP_TIME_OUT	 9000	// 15 minutes (9000 * 0.1s)

#define PMP_LATENCY						1
#define NUMBER_OF_SAMPLES_PER_CHANNEL	4096

// channels
#define	CH1				0
#define	CH2				1

// input coupling
#define	AC				0
#define	DC				1
#define	REFGND			2

// sensitivity
#define NUMBER_OF_VOLT_DIV	13

#define	CH_OFF_V_DIV	0
#define	CH_20V_DIV		1
#define	CH_10V_DIV		2
#define	CH_4V_DIV		3
#define	CH_2V_DIV		4
#define	CH_1V_DIV		5
#define	CH_0P5V_DIV		6
#define	CH_0P2V_DIV		7
#define	CH_0P1V_DIV		8
#define	CH_50MV_DIV		9
#define	CH_25MV_DIV		10
#define	CH_10MV_DIV		11
#define	CH_5MV_DIV		12

// timebase
#define	CH_1US_DIV		0
#define	CH_2US_DIV		1
#define	CH_5US_DIV		2
#define	CH_10US_DIV		3
#define	CH_20US_DIV		4
#define	CH_50US_DIV		5
#define	CH_0P1MS_DIV	6
#define	CH_0P2MS_DIV	7
#define	CH_0P5MS_DIV	8
#define	CH_1MS_DIV		9
#define	CH_2MS_DIV		10
#define	CH_5MS_DIV		11
#define	CH_10MS_DIV		12
#define	CH_20MS_DIV		13
#define	CH_50MS_DIV		14
#define	CH_0P1S_DIV		15
#define	CH_0P2S_DIV		16
#define	CH_0P5S_DIV		17
#define	CH_1S_DIV		18




// timebase prescaler & period

#define	CH_1US_DIV_PERIOD	(DWORD)(1 * (GetPeripheralClock() / 10000000UL) - 1)
#define	CH_2US_DIV_PERIOD	(DWORD)(2 * (GetPeripheralClock() / 10000000UL) - 1)
#define	CH_5US_DIV_PERIOD	(DWORD)(5 * (GetPeripheralClock() / 10000000UL) - 1)
#define	CH_10US_DIV_PERIOD	(DWORD)(1 * (GetPeripheralClock() / 1000000UL) - 1)
#define	CH_20US_DIV_PERIOD	(DWORD)(2 * (GetPeripheralClock() / 1000000UL) - 1)
#define	CH_50US_DIV_PERIOD	(DWORD)(5 * (GetPeripheralClock() / 1000000UL) - 1)
#define	CH_0P1MS_DIV_PERIOD	(DWORD)(2 * (GetPeripheralClock() / 1000000UL) - 1)
#define	CH_0P2MS_DIV_PERIOD	(DWORD)(4 * (GetPeripheralClock() / 1000000UL) - 1)
#define	CH_0P5MS_DIV_PERIOD	(DWORD)(10 * (GetPeripheralClock() / 1000000UL) - 1)
#define	CH_1MS_DIV_PERIOD	(DWORD)(20 * (GetPeripheralClock() / 1000000UL) - 1)
#define	CH_2MS_DIV_PERIOD	(DWORD)(40 * (GetPeripheralClock() / 1000000UL) - 1)
#define	CH_5MS_DIV_PERIOD	(DWORD)(100 * (GetPeripheralClock() / 1000000UL) - 1)
#define	CH_10MS_DIV_PERIOD	(DWORD)(200 * (GetPeripheralClock() / 1000000UL) - 1)
#define	CH_20MS_DIV_PERIOD	(DWORD)(400 * (GetPeripheralClock() / 1000000UL) - 1)
#define	CH_50MS_DIV_PERIOD	(DWORD)(1000 * (GetPeripheralClock() / 1000000UL) - 1)
#define	CH_0P1S_DIV_PERIOD	(DWORD)(2000UL * (GetPeripheralClock() / 1000000UL) - 1)
#define	CH_0P2S_DIV_PERIOD	(DWORD)(4000UL * (GetPeripheralClock() / 1000000UL) - 1)
#define	CH_0P5S_DIV_PERIOD	(DWORD)(10000UL * (GetPeripheralClock() / 1000000UL) - 1)
#define	CH_1S_DIV_PERIOD	(DWORD)(20000UL * (GetPeripheralClock() / 1000000UL) - 1)



// trigger mode
#define	NORMAL			0
#define	AUTO			1
#define	ONCE			2

// trigger slope INT
#define	RISING_EDGE		1
#define	FALLING_EDGE	0

// trigger slope input capture
#define	INPUT_CAPTURE_RISING_EDGE	2
#define INPUT_CAPTURE_FALLING_EDGE	3

// trigger run/hold
#define	RUN				0
#define	HOLD			1

// Sample limits
#define SAMPLE_MIN				3
#define SAMPLE_MAX				252

// Sample switchover values for autorange
#define SAMPLE_MIN_AUTORANGE 	90
#define SAMPLE_MAX_AUTORANGE 	170

// Y-position
#define	YPOS_TOP			3
#define	YPOS_UPPER_CENTER	64
#define	YPOS_CENTER			128
#define	YPOS_LOWER_CENTER	YPOS_UPPER_CENTER + 128
#define	YPOS_BOTTOM			252

// Trigger level
#define	TRIG_LVL_TOP	3
#define	TRIG_LVL_CENTER	128
#define	TRIG_LVL_BOTTOM	252

// Sampling state machine
#define SM_IDLE					0
#define SM_SAMPLING_START		1
#define SM_AUTO_TIMEBASE		2
#define SM_AUTO_TIMEBASE_BUSY	3
#define SM_AUTO_TIMEBASE_DONE	4
#define SM_SAMPLING				5
#define SM_SAMPLING_BUSY		6
#define SM_SAMPLING_DONE		7
#define SM_SEND_SAMPLES			8
#define SM_SEND_BUSY			9
#define SM_SEND_DONE			10

// Calibration state machine
#define SM_IDLE					0
#define SM_INIT					1
#define SM_Y_CENTER_5MV_DIV		2
#define SM_Y_CENTER_10MV_DIV	3
#define SM_Y_CENTER_20MV_DIV	4
#define SM_Y_CENTER_50MV_DIV	5
#define SM_Y_UPPER_CENTER		6
#define SM_Y_LOWER_CENTER		7
#define SM_TRIG_LOWER_CENTER	8
#define SM_TRIG_UPPER_CENTER	9
#define SM_DONE					10


typedef union
{
	WORD	val;
	struct
	{
		BYTE	LB;
		BYTE	HB;
	} byte;
	struct
	{
		unsigned	trigger_mode	: 2;
		unsigned	trigger_slope	: 1;
		unsigned	trigger_channel	: 1;
		unsigned	trigger_hold	: 1;
		unsigned	trigger_restart	: 1;
		unsigned	trigger_manual	: 1;
		unsigned	autorange		: 1;
		unsigned	charger_PG		: 1;
		unsigned	charger_stat1	: 1;
		unsigned	charger_stat2	: 1;
		unsigned	debug			: 1;
		unsigned	calibrating		: 1;
		unsigned	low_voltage		: 1;
		unsigned	reserved		: 3;
	} flags;
} WFS210_STATUS;

typedef struct
{
	BYTE			couplingCh1;
	BYTE			sensitivityCh1;
	BYTE			ypositionCh1;
	BYTE			couplingCh2;
	BYTE			sensitivityCh2;
	BYTE			ypositionCh2;
	BYTE			timebase;
	BYTE			triglevel;
	WFS210_STATUS	status;
} WFS210_SETTINGS;


typedef struct
{
	int		ch1_offset[NUMBER_OF_VOLT_DIV];
	int		ch2_offset[NUMBER_OF_VOLT_DIV];
	int		ch1_lower_center;
	int		ch1_upper_center;
	int		ch2_lower_center;
	int		ch2_upper_center;
	int		trigger_lower_center;
	int		trigger_upper_center;
	BOOL	ch1_done;
	BOOL	ch2_done;
	WORD	pwm_min_Ch1, pwm_max_Ch1;
	WORD	pwm_min_Ch2, pwm_max_Ch2;
	WORD	sm;
} WFS210_CALIBRATION;


extern WORD					sampling_sm;
extern WFS210_SETTINGS		scope_settings;
extern WFS210_CALIBRATION	calibration;
extern WFS210_OUT_PACKET	wfs210out;


/**
 *
 */
VOID WFS210Init(VOID);

/**
 * 
 * @param 
 * @return 
 */
VOID WFS210Sleep(VOID);

/**
 * 
 */
VOID WFS210Tasks(VOID);



#endif	/* SCOPE_H */

