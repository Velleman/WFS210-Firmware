/* 
 * File:   wfs210_process.h
 * Author: edc
 *
 * Created on 2 juli 2013, 11:38
 */

#ifndef WFS210_PROCESS_H
#define	WFS210_PROCESS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "common.h"
#include "wfs210/wfs210.h"



// Global vars
// -----------
extern volatile DWORD_VAL	capture1, capture2;
extern volatile WORD		timebase_index;
extern BYTE					sample_buffer[2 * (PMP_LATENCY + NUMBER_OF_SAMPLES_PER_CHANNEL + 1)];


typedef struct
{
	WORD	samples;
	BOOL	status;
	BOOL	wifistatus;
} TX_QUEUE;




/**
 *
 * @param	none
 * @return	none
 */
VOID InitSettings(VOID);


/**
 * 
 * @param 
 * @return 
 */
VOID LoadCalibrationData(VOID);

/**
 * 
 * @param 
 * @return 
 */
VOID StartCalibration(VOID);


/**
 *
 * @param
 * @return
 */
VOID CalibrationTask(VOID);


/**
 *
 * @param
 * @return
 */
VOID InitLowVoltage(VOID);


/**
 *
 * @param
 * @return
 */
VOID DisLowVoltage(VOID);


/**
 *
 * @param
 * @return
 */
VOID LowVoltageTask(VOID);


/**
 *
 * @param	none
 * @return	none
 */
VOID InitSampleBuffer(VOID);


/**
 * 
 * @param 
 * @return 
 */
VOID CheckAutoVolt(VOID);


/**
 * 
 * @param 
 * @return 
 */
VOID StartAutoTimebase(VOID);


/**
 *
 * @param
 * @return
 */
VOID SetAutoTimeBase(VOID);


/**
 *
 * @param
 * @return
 */
VOID StopSampling(VOID);


/**
 *
 * @param
 * @return
 */
VOID ScopeTasks(VOID);



/**
 *
 * @param packet
 * @return none
 */
VOID WFS210Receive(WFS210_IN_PACKET* packet);


/**
 * 
 * @param 
 * @return 
 */
VOID TransmitTask(VOID);


/**
 *
 * @param
 * @return
 */
BOOL TxReady(VOID);


/**
 *
 * @param packet
 * @param cmd
 * @param nrsamples
 * @return none
 */
VOID TransmitSamples(WFS210_OUT_PACKET* packet, WORD nrsamples);


/**
 * 
 * @param packet
 * @return 
 */
VOID TransmitStatus(WFS210_OUT_PACKET* packet);


/**
 *
 * @param packet
 * @return
 */
VOID TransmitWifiStatus(WFS210_OUT_PACKET* packet);


/**
 * Read the status of the battery charger
 * @param none
 * @return none
 */
VOID ReadChargerStatus(VOID);


/**
 *
 * @param debug
 * @return
 */
VOID SetScopeDebugMode(BOOL debug);

/**
 * Set the input coupling (ac/dc gnd) of channel 1
 * @param index
 * @return none
 */
VOID SetInputCouplingCh1(BYTE index);


/**
 * Set the input coupling (ac/dc gnd) of channel 2
 * @param index
 * @return none
 */
VOID SetInputCouplingCh2(BYTE index);


/**
 * set the input sensitivity of channel 1
 * @param index
 * @return none
 */
VOID SetVoltDivCh1(BYTE index);


/**
 * set the input sensitivity of channel 2
 * @param index
 * @return none
 */
VOID SetVoltDivCh2(BYTE index);

/**
 * Set y-position pwm of channel 1
 * @param index (0..255)
 * @return 
 */
VOID SetYposCh1(BYTE index);

/**
 * Set y-position pwm of channel 2
 * @param index (0..255)
 * @return
 */
VOID SetYposCh2(BYTE index);

/**
 * Set trigger level pwm
 * @param index (0..255)
 * @return
 */
VOID SetTrigLevel(BYTE index);

/**
 * set Timebase
 * @param index
 * @return
 */
VOID SetTimebase(BYTE index);

/**
 * 
 * @param index
 * @return 
 */
VOID SetTriggering(BYTE setting);





#ifdef	__cplusplus
}
#endif

#endif	/* WFS210_PROCESS_H */

