/* 
 * File:   wfs210_hal.h
 * Author: edc
 *
 * Created on 28 juni 2013, 14:13
 */

#ifndef WFS210_HAL_H
#define	WFS210_HAL_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "common.h"
#include <outcompare.h>
#include <pmp.h>
#include <timer.h>


/** TRIS factory defaults button io status ********************************/
#define mTRIS_Factory_Defaults	TRISDbits.TRISD9

/** factory defaults button pin status ************************************/
#define mPORT_Factory_Defaults	PORTDbits.RD9

/** Weak Pull-up factory defaults button io status ***************************************/
#define mCNPU_Factory_Defaults	CNPUDbits.CNPUD9

/** Weak Pull-down factory defaults button io status ***************************************/
#define mCNPD_Factory_Defaults	CNPDDbits.CNPDD9


/** TRIS analog power supply io status ************************************/
#define mTRIS_Analog_Power		TRISDbits.TRISD8

/** Output analog power supply ********************************************/
#define mLAT_Analog_Power		LATDbits.LATD8


/** ANSEL battery io status ***********************************************/
#define mANSEL_Charger_PG		ANSELBbits.ANSB12
#define mANSEL_Charger_Stat1	ANSELBbits.ANSB13
#define mANSEL_Charger_Stat2	ANSELBbits.ANSB14

/** TRIS battery io status ************************************************/
#define mTRIS_Charger_PG		TRISBbits.TRISB12
#define mTRIS_Charger_Stat1		TRISBbits.TRISB13
#define mTRIS_Charger_Stat2		TRISBbits.TRISB14

/** battery status pins ********************************************/
#define mPORT_Charger_PG		PORTBbits.RB12
#define mPORT_Charger_Stat1		PORTBbits.RB13
#define mPORT_Charger_Stat2		PORTBbits.RB14
#define mGetChargerPower()		U1OTGSTATbits.VBUSVD


/** Weak Pull-ups battery io status ***************************************/
#define mCNPU_Charger_PG		CNPUBbits.CNPUB12
#define mCNPU_Charger_Stat1		CNPUBbits.CNPUB13
#define mCNPU_Charger_Stat2		CNPUBbits.CNPUB14


/** ANSEL channels 1 ***************************************************/
#define mANSEL_DivBy1_Ch1		ANSELCbits.ANSC13
#define mANSEL_Gain_x2p5_x5_Ch1	ANSELCbits.ANSC14

/** ANSEL channels 2 ***************************************************/
#define mANSEL_ACDC_Ch2			ANSELBbits.ANSB10
#define mANSEL_InputCap_Ch2		ANSELBbits.ANSB11
#define mANSEL_RefGnd_Ch2		ANSELBbits.ANSB9
#define mANSEL_DivBy1_Ch2		ANSELBbits.ANSB8
#define mANSEL_DivBy20_Ch2		ANSELBbits.ANSB2
#define mANSEL_DivBy400_Ch2		ANSELBbits.ANSB4
#define mANSEL_Gain_x1_x5_Ch2	ANSELBbits.ANSB3
#define mANSEL_Gain_x2p5_x5_Ch2	ANSELDbits.ANSD6

/** TRIS Channel 1 ************************************************************/
#define mTRIS_ACDC_Ch1			TRISDbits.TRISD0
#define mTRIS_InputCap_Ch1		TRISDbits.TRISD11
#define mTRIS_RefGnd_Ch1		TRISDbits.TRISD3
#define mTRIS_DivBy1_Ch1		TRISCbits.TRISC13
#define mTRIS_DivBy20_Ch1		TRISDbits.TRISD1
#define mTRIS_DivBy400_Ch1		TRISDbits.TRISD2
#define mTRIS_Gain_x1_x5_Ch1	TRISDbits.TRISD10
#define mTRIS_Gain_x2p5_x5_Ch1	TRISCbits.TRISC14

/** Outputs Channel 1 ************************************************************/
#define mLAT_ACDC_Ch1			LATDbits.LATD0
#define mLAT_InputCap_Ch1		LATDbits.LATD11
#define mLAT_RefGnd_Ch1			LATDbits.LATD3
#define mLAT_DivBy1_Ch1			LATCbits.LATC13
#define mLAT_DivBy20_Ch1		LATDbits.LATD1
#define mLAT_DivBy400_Ch1		LATDbits.LATD2
#define mLAT_Gain_x1_x5_Ch1		LATDbits.LATD10
#define mLAT_Gain_x2p5_x5_Ch1	LATCbits.LATC14

/** TRIS Channel 2 ************************************************************/
#define mTRIS_ACDC_Ch2			TRISBbits.TRISB10
#define mTRIS_InputCap_Ch2		TRISBbits.TRISB11
#define mTRIS_RefGnd_Ch2		TRISBbits.TRISB9
#define mTRIS_DivBy1_Ch2		TRISBbits.TRISB8
#define mTRIS_DivBy20_Ch2		TRISBbits.TRISB2
#define mTRIS_DivBy400_Ch2		TRISBbits.TRISB4
#define mTRIS_Gain_x1_x5_Ch2	TRISBbits.TRISB3
#define mTRIS_Gain_x2p5_x5_Ch2	TRISDbits.TRISD6

/** Outputs Channel 2 ************************************************************/
#define mLAT_ACDC_Ch2			LATBbits.LATB10
#define mLAT_InputCap_Ch2		LATBbits.LATB11
#define mLAT_RefGnd_Ch2			LATBbits.LATB9
#define mLAT_DivBy1_Ch2			LATBbits.LATB8
#define mLAT_DivBy20_Ch2		LATBbits.LATB2
#define mLAT_DivBy400_Ch2		LATBbits.LATB4
#define mLAT_Gain_x1_x5_Ch2		LATBbits.LATB3
#define mLAT_Gain_x2p5_x5_Ch2	LATDbits.LATD6

/** ANSEL Trigger channels *******************************************************/
#define mANSEL_Trig1			ANSELBbits.ANSB5
#define mANSEL_Trig2			ANSELGbits.ANSG9

/* TRIS Trigger channels *********************************************************/
#define mTRIS_Trig1				TRISBbits.TRISB5
#define mTRIS_Trig2				TRISGbits.TRISG9

/** Trigger input pins ***********************************************************/
#define mPORT_Trig1				PORTBbits.RB5
#define mPORT_Trig2				PORTGbits.RG9

/* RPINR Peripheral Pin select Trigger channels **********************************/
#define mRPINR_Trig1			RPINR0bits.INT1R
#define mRPINR_Trig2			RPINR1bits.INT2R

/* INTCONx Trigger settings *******************************************************/
#define mTrig1_Edge				INTCON2bits.INT1EP
#define mTrig2_Edge				INTCON2bits.INT2EP
#define mTrig1_Int_Ena			IEC1bits.INT1IE
#define mTrig2_Int_Ena			IEC1bits.INT2IE
#define mTrig1_Int_Pri			IPC5bits.INT1IP
#define mTrig2_Int_Pri			IPC7bits.INT2IP
#define mTrig1_Int_Flag			IFS1bits.INT1IF
#define mTrig2_Int_Flag			IFS1bits.INT2IF

/* RPINR Peripheral Pin select input capture channels *****************************/
#define mRPINR_IC1				RPINR7bits.IC1R
#define mRPINR_IC2				RPINR8bits.IC3R

/* ICxCONx input capture settings *************************************************/
#define mIC1L_Edge				IC1CON1bits.ICM
#define mIC1H_Edge				IC2CON1bits.ICM
#define mIC2L_Edge				IC3CON1bits.ICM
#define mIC2H_Edge				IC4CON1bits.ICM
#define mIC1_Int_Ena			IEC0bits.IC1IE
#define mIC2_Int_Ena			IEC2bits.IC3IE
#define mIC1_Int_Pri			IPC0bits.IC1IP
#define mIC2_Int_Pri			IPC9bits.IC3IP
#define mIC1_Int_Flag			IFS0bits.IC1IF
#define mIC2_Int_Flag			IFS2bits.IC3IF


/** ANSEL Y-position pwm output **************************************************/
#define mANSEL_Ypos_Ch1			ANSELDbits.ANSD7

/** RPOR Peripheral Pin select for PWM modules ***********************************/
#define mRPOR_Ypos_Ch1			RPOR3bits.RP71R
#define mRPOR_Ypos_Ch2			RPOR7bits.RP97R
#define mRPOR_Trig_Level		RPOR7bits.RP96R

/** PWM Period registers *********************************************************/
#define PWM_PERIOD				0x8000
#define mPeriod_Ypos_Ch1		OC1RS
#define mPeriod_Ypos_Ch2		OC2RS
#define mPeriod_Trig_Level		OC3RS

/** PWM Duty Cycle registers *****************************************************/
#define PWM_CENTER				(PWM_PERIOD / 2)
#define mDuty_Cycle_Ypos_Ch1	OC1R
#define mDuty_Cycle_Ypos_Ch2	OC2R
#define mDuty_Cycle_Trig_Level	OC3R

/** ANSEL UART Rx input **********************************************************/
#define mANSEL_Rx_UART			ANSELBbits.ANSB6
#define mANSEL_CTS_UART			ANSELBbits.ANSB7
#define mANSEL_Wifi_Tcp_Con		ANSELBbits.ANSB15

/** TRIS WiFi module status ******************************************************/
#define mTRIS_Wifi_Rst			TRISDbits.TRISD5
#define mTRIS_Wifi_Tcp_Con		TRISBbits.TRISB15
#define mTRIS_UART_Rx			TRISBbits.TRISB6
#define mTRIS_UART_CTS			TRISBbits.TRISB7

/** Inputs WiFi module ***********************************************************/
#define mPORT_UART_CTS			PORTBbits.RB7
#define mPORT_Wifi_Tcp_Con		PORTBbits.RB15

/** Outputs WiFi module **********************************************************/
#define mLAT_Wifi_Rst			LATDbits.LATD5
#define mLAT_Wifi_Tcp_Con		LATBbits.LATB15

/** RPOR Peripheral Pin select for UART module************************************/
#define mRPOR_Tx_UART			RPOR9bits.RP101R
#define mRPOR_RTS_UART			RPOR9bits.RP100R

/** RPINR Peripheral Pin select for UART module***********************************/
#define mRPINR_Rx_UART			RPINR18bits.U1RXR
#define mRPINR_CTS_UART			RPINR18bits.U1CTSR

/** ANSEL ADC module io status **************************************************/
#define mANSEL_ADC_PD0			ANSELGbits.ANSG8
#define mANSEL_ADC_PD1			ANSELGbits.ANSG7
#define mANSEL_ADC_D0			ANSELEbits.ANSE0
#define mANSEL_ADC_D1			ANSELEbits.ANSE1
#define mANSEL_ADC_D2			ANSELEbits.ANSE2
#define mANSEL_ADC_D3			ANSELEbits.ANSE3
#define mANSEL_ADC_D4			ANSELEbits.ANSE4
#define mANSEL_ADC_D5			ANSELEbits.ANSE5
#define mANSEL_ADC_D6			ANSELEbits.ANSE6
#define mANSEL_ADC_D7			ANSELEbits.ANSE7
#define mANSEL_ADC_AB			ANSELGbits.ANSG6

/** TRIS ADC module *********************************************************/
#define mTRIS_ADC_PD0			TRISGbits.TRISG8
#define mTRIS_ADC_PD1			TRISGbits.TRISG7
#define mTRIS_ADC_Clk			TRISDbits.TRISD4
#define mTRIS_ADC_D0			TRISEbits.TRISE0
#define mTRIS_ADC_D1			TRISEbits.TRISE1
#define mTRIS_ADC_D2			TRISEbits.TRISE2
#define mTRIS_ADC_D3			TRISEbits.TRISE3
#define mTRIS_ADC_D4			TRISEbits.TRISE4
#define mTRIS_ADC_D5			TRISEbits.TRISE5
#define mTRIS_ADC_D6			TRISEbits.TRISE6
#define mTRIS_ADC_D7			TRISEbits.TRISE7
#define mTRIS_ADC_AB			TRISGbits.TRISG6

/** outputs ADC module ******************************************************/
#define mLAT_ADC_PD0			LATGbits.LATG8
#define mLAT_ADC_PD1			LATGbits.LATG7
#define mLAT_ADC_Clk			LATDbits.LATD4

/* analog power supply macro's **********00000************************************/
#define mInitAnalogPower()		{ mTRIS_Analog_Power = OUTPUT_PIN; mLAT_Analog_Power = 1; }
#define mDisAnalogPower()		mLAT_Analog_Power = 0


/** Outputs macro's Channel 1 ****************************************************/
#define mInitAcDcCh1()			mTRIS_ACDC_Ch1 = INPUT_PIN;
#define mInitInputCapCh1()		mTRIS_InputCap_Ch1 = INPUT_PIN;
#define mInitRefGndCh1()		mTRIS_RefGnd_Ch1 = OUTPUT_PIN;
#define mInitDivBy1Ch1()		{ mTRIS_DivBy1_Ch1 = INPUT_PIN; mANSEL_DivBy1_Ch1 = DIGITAL_PIN; }
#define mInitDivBy20Ch1()		mTRIS_DivBy20_Ch1 = OUTPUT_PIN;
#define mInitDivBy400Ch1()		mTRIS_DivBy400_Ch1 = OUTPUT_PIN;
#define mInitGainx1x5Ch1()		mTRIS_Gain_x1_x5_Ch1 = OUTPUT_PIN;
#define mInitGainx2p5x5Ch1()	{ mTRIS_Gain_x2p5_x5_Ch1 = OUTPUT_PIN; mANSEL_Gain_x2p5_x5_Ch1 = DIGITAL_PIN; }
#define mInitTrisCh1()			{ mInitAcDcCh1(); \
								  mInitInputCapCh1(); \
								  mInitRefGndCh1(); \
								  mInitDivBy1Ch1(); \
								  mInitDivBy20Ch1(); \
								  mInitDivBy400Ch1(); \
								  mInitGainx1x5Ch1(); \
								  mInitGainx2p5x5Ch1(); \
								}

#define mInitYposCh1()			{ mRPOR_Ypos_Ch1 = 0x10; \
								  ConfigIntOC1(OC_INT_OFF); \
								  OC1CON1 = 0x3C00; \
								  OC1CON2 = 0; \
								  OC1CON1bits.OCTSEL = 0x07; \
								  mDuty_Cycle_Ypos_Ch1 = PWM_CENTER; \
								  mPeriod_Ypos_Ch1 = PWM_PERIOD; \
								  OC1CON1bits.OCM = 6; \
								  OC1CON2bits.SYNCSEL = 0x1F; \
								}

#define mSetAcCh1()				mTRIS_ACDC_Ch1 = INPUT_PIN
#define mSetDcCh1()				{ mTRIS_ACDC_Ch1 = OUTPUT_PIN; mLAT_ACDC_Ch1 = 0; }
#define mSetGndCh1()			{ mTRIS_DivBy1_Ch1 = INPUT_PIN; mLAT_DivBy20_Ch1 = 0; mLAT_DivBy400_Ch1 = 0; mLAT_RefGnd_Ch1 = 1; mTRIS_InputCap_Ch1 = INPUT_PIN; }
#define mSetAtt1Ch1()			{ mLAT_RefGnd_Ch1 = 0; mTRIS_DivBy1_Ch1 = OUTPUT_PIN; mLAT_DivBy1_Ch1 = 0; mLAT_DivBy20_Ch1 = 0; mLAT_DivBy400_Ch1 = 0; mTRIS_InputCap_Ch1 = INPUT_PIN; }
#define mSetAtt20Ch1()			{ mLAT_RefGnd_Ch1 = 0; mTRIS_DivBy1_Ch1 = INPUT_PIN; mLAT_DivBy20_Ch1 = 1; mLAT_DivBy400_Ch1 = 0; mTRIS_InputCap_Ch1 = OUTPUT_PIN; mLAT_InputCap_Ch1 = 0; }
#define mSetAtt400Ch1()			{ mLAT_RefGnd_Ch1 = 0; mTRIS_DivBy1_Ch1 = INPUT_PIN; mLAT_DivBy20_Ch1 = 0; mLAT_DivBy400_Ch1 = 1; mTRIS_InputCap_Ch1 = OUTPUT_PIN; mLAT_InputCap_Ch1 = 0; }
#define mSetGain2p5Ch1()		{ mLAT_Gain_x1_x5_Ch1 = 0; mLAT_Gain_x2p5_x5_Ch1 = 0; }
#define mSetGain5Ch1()			{ mLAT_Gain_x1_x5_Ch1 = 0; mLAT_Gain_x2p5_x5_Ch1 = 1; }
#define mSetGain12p5Ch1()		{ mLAT_Gain_x1_x5_Ch1 = 1; mLAT_Gain_x2p5_x5_Ch1 = 0; }
#define mSetGain25Ch1()			{ mLAT_Gain_x1_x5_Ch1 = 1; mLAT_Gain_x2p5_x5_Ch1 = 1; }
#define mSwitchOffCh1()			{ mSetGndCh1(); mSetAcCh1(); mSetGain2p5Ch1(); mDuty_Cycle_Ypos_Ch1 = PWM_CENTER;}
#define mSet20VdivCh1()			{ mSetAtt400Ch1(); mSetGain2p5Ch1(); }
#define mSet10VdivCh1()			{ mSetAtt400Ch1(); mSetGain5Ch1(); }
#define mSet4VdivCh1()			{ mSetAtt400Ch1(); mSetGain12p5Ch1(); }
#define mSet2VdivCh1()			{ mSetAtt400Ch1(); mSetGain25Ch1(); }
#define mSet1VdivCh1()			{ mSetAtt20Ch1(); mSetGain2p5Ch1(); }
#define mSet0p5VdivCh1()		{ mSetAtt20Ch1(); mSetGain5Ch1(); }
#define mSet0p2VdivCh1()		{ mSetAtt20Ch1(); mSetGain12p5Ch1(); }
#define mSet0p1VdivCh1()		{ mSetAtt20Ch1(); mSetGain25Ch1(); }
#define mSet50mVdivCh1()		{ mSetAtt1Ch1(); mSetGain2p5Ch1(); }
#define mSet25mVdivCh1()		{ mSetAtt1Ch1(); mSetGain5Ch1(); }
#define mSet10mVdivCh1()		{ mSetAtt1Ch1(); mSetGain12p5Ch1(); }
#define mSet5mVdivCh1()			{ mSetAtt1Ch1(); mSetGain25Ch1(); }


/** Outputs macro's Channel 2 ****************************************************/
#define mInitAcDcCh2()			{ mTRIS_ACDC_Ch2 = INPUT_PIN; mANSEL_ACDC_Ch2 = DIGITAL_PIN; }
#define mInitInputCapCh2()		{ mTRIS_InputCap_Ch2 = INPUT_PIN; mANSEL_InputCap_Ch2 = DIGITAL_PIN; }
#define mInitRefGndCh2()		{ mTRIS_RefGnd_Ch2 = OUTPUT_PIN; mANSEL_RefGnd_Ch2 = DIGITAL_PIN; }
#define mInitDivBy1Ch2()		{ mTRIS_DivBy1_Ch2 = INPUT_PIN; mANSEL_DivBy1_Ch2 = DIGITAL_PIN; }
#define mInitDivBy20Ch2()		{ mTRIS_DivBy20_Ch2 = OUTPUT_PIN; mANSEL_DivBy20_Ch2 = DIGITAL_PIN; }
#define mInitDivBy400Ch2()		{ mTRIS_DivBy400_Ch2 = OUTPUT_PIN; mANSEL_DivBy400_Ch2 = DIGITAL_PIN; }
#define mInitGainx1x5Ch2()		{ mTRIS_Gain_x1_x5_Ch2 = OUTPUT_PIN; mANSEL_Gain_x1_x5_Ch2 = DIGITAL_PIN; }
#define mInitGainx2p5x5Ch2()	{ mTRIS_Gain_x2p5_x5_Ch2 = OUTPUT_PIN; mANSEL_Gain_x2p5_x5_Ch2 = DIGITAL_PIN; }
#define mInitTrisCh2()			{ mInitAcDcCh2(); \
								  mInitInputCapCh2(); \
								  mInitRefGndCh2(); \
								  mInitDivBy1Ch2(); \
								  mInitDivBy20Ch2(); \
								  mInitDivBy400Ch2(); \
								  mInitGainx1x5Ch2(); \
								  mInitGainx2p5x5Ch2(); \
								}
/*#define mInitYposCh2()			{ mRPOR_Ypos_Ch2 = 0x11; \
								  ConfigIntOC2(OC_INT_OFF); \
								  OpenOC2(OC_IDLE_CON & OC_SYSCLK_SRC & OC_FAULTC_IN_DISABLE & OC_FAULTB_IN_DISABLE & OC_FAULTA_IN_DISABLE & OC_PWM_FAULT_CLEAR & OC_TRIG_CLEAR_SW & OC_PWM_EDGE_ALIGN, \
										  OC_FAULT_MODE_PWM_CYCLE & OC_PWM_FAULT_OUT_LOW &  OC_OUT_NOT_INVERT & OC_CASCADE_DISABLE & OC_SYNC_ENABLE & OC_UNTRIGGER_TIMER & OC_DIRN_OUTPUT & OC_SYNC_TRIG_IN_DISABLE, \
										  PWM_PERIOD, PWM_CENTER) ; \
								}
*/
#define mInitYposCh2()			{ mRPOR_Ypos_Ch2 = 0x11; \
								  ConfigIntOC2(OC_INT_OFF); \
								  OC2CON1 = 0x3C00; \
								  OC2CON2 = 0; \
								  OC2CON1bits.OCTSEL = 0x07; \
								  mDuty_Cycle_Ypos_Ch2 = PWM_CENTER; \
								  mPeriod_Ypos_Ch2 = PWM_PERIOD; \
								  OC2CON1bits.OCM = 6; \
								  OC2CON2bits.SYNCSEL = 0x1F; \
								}


#define mSetAcCh2()				mTRIS_ACDC_Ch2 = INPUT_PIN;
#define mSetDcCh2()				{ mTRIS_ACDC_Ch2 = OUTPUT_PIN; mLAT_ACDC_Ch2 = 0; }
#define mSetGndCh2()			{ mTRIS_DivBy1_Ch2 = INPUT_PIN; mLAT_DivBy20_Ch2 = 0; mLAT_DivBy400_Ch2 = 0; mLAT_RefGnd_Ch2 = 1; mTRIS_InputCap_Ch2 = INPUT_PIN; }
#define mSetAtt1Ch2()			{ mLAT_RefGnd_Ch2 = 0; mTRIS_DivBy1_Ch2 = OUTPUT_PIN; mLAT_DivBy1_Ch2 = 0; mLAT_DivBy20_Ch2 = 0; mLAT_DivBy400_Ch2 = 0; mTRIS_InputCap_Ch2 = INPUT_PIN; }
#define mSetAtt20Ch2()			{ mLAT_RefGnd_Ch2 = 0; mTRIS_DivBy1_Ch2 = INPUT_PIN; mLAT_DivBy20_Ch2 = 1; mLAT_DivBy400_Ch2 = 0; mTRIS_InputCap_Ch2 = OUTPUT_PIN; mLAT_InputCap_Ch2 = 0; }
#define mSetAtt400Ch2()			{ mLAT_RefGnd_Ch2 = 0; mTRIS_DivBy1_Ch2 = INPUT_PIN; mLAT_DivBy20_Ch2 = 0; mLAT_DivBy400_Ch2 = 1; mTRIS_InputCap_Ch2 = OUTPUT_PIN; mLAT_InputCap_Ch2 = 0; }
#define mSetGain2p5Ch2()		{ mLAT_Gain_x1_x5_Ch2 = 0; mLAT_Gain_x2p5_x5_Ch2 = 0; }
#define mSetGain5Ch2()			{ mLAT_Gain_x1_x5_Ch2 = 0; mLAT_Gain_x2p5_x5_Ch2 = 1; }
#define mSetGain12p5Ch2()		{ mLAT_Gain_x1_x5_Ch2 = 1; mLAT_Gain_x2p5_x5_Ch2 = 0; }
#define mSetGain25Ch2()			{ mLAT_Gain_x1_x5_Ch2 = 1; mLAT_Gain_x2p5_x5_Ch2 = 1; }
#define mSwitchOffCh2()			{ mSetGndCh2(); mSetAcCh2(); mSetGain2p5Ch2(); mDuty_Cycle_Ypos_Ch2 = PWM_CENTER; }
#define mSet20VdivCh2()			{ mSetAtt400Ch2(); mSetGain2p5Ch2(); }
#define mSet10VdivCh2()			{ mSetAtt400Ch2(); mSetGain5Ch2(); }
#define mSet4VdivCh2()			{ mSetAtt400Ch2(); mSetGain12p5Ch2(); }
#define mSet2VdivCh2()			{ mSetAtt400Ch2(); mSetGain25Ch2(); }
#define mSet1VdivCh2()			{ mSetAtt20Ch2(); mSetGain2p5Ch2(); }
#define mSet0p5VdivCh2()		{ mSetAtt20Ch2(); mSetGain5Ch2(); }
#define mSet0p2VdivCh2()		{ mSetAtt20Ch2(); mSetGain12p5Ch2(); }
#define mSet0p1VdivCh2()		{ mSetAtt20Ch2(); mSetGain25Ch2(); }
#define mSet50mVdivCh2()		{ mSetAtt1Ch2(); mSetGain2p5Ch2(); }
#define mSet25mVdivCh2()		{ mSetAtt1Ch2(); mSetGain5Ch2(); }
#define mSet10mVdivCh2()		{ mSetAtt1Ch2(); mSetGain12p5Ch2(); }
#define mSet5mVdivCh2()			{ mSetAtt1Ch2(); mSetGain25Ch2(); }




/** macro's Trigger channels ******************************************************/
#define mTrig1Interrupt			_INT1Interrupt
#define mTrig2Interrupt			_INT2Interrupt
#define mSetTrigRisingEdge()	{ mTrig1_Edge = RISING_EDGE; mTrig2_Edge = RISING_EDGE; }
#define mSetTrigFallingEdge()	{ mTrig1_Edge = FALLING_EDGE; mTrig2_Edge = FALLING_EDGE; }
#define mDisTrig1Interrupts()	{ mTrig1_Int_Ena = FALSE; }
#define mDisTrig2Interrupts()	{ mTrig2_Int_Ena = FALSE; }
#define mDisTrigInterrupts()	{ mTrig1_Int_Ena = FALSE; mTrig2_Int_Ena = FALSE; }
#define mSelectTrigCh1()		{ mTrig2_Int_Ena = FALSE; mTrig1_Int_Flag = FALSE; mTrig1_Int_Ena = TRUE; }
#define mSelectTrigCh2()		{ mTrig1_Int_Ena = FALSE; mTrig2_Int_Flag = FALSE; mTrig2_Int_Ena = TRUE; }
#define mInitTrigInputs()		{ mTRIS_Trig1 = INPUT_PIN; mANSEL_Trig1 = DIGITAL_PIN; \
								  mTRIS_Trig2 = INPUT_PIN; mANSEL_Trig2 = DIGITAL_PIN; \
								  mRPINR_IC1 = 0; mRPINR_IC2 = 0; \
								  mRPINR_Trig1 = 0x25; mRPINR_Trig2	= 0x79; \
								  mDisTrigInterrupts(); \
								  mTrig1_Int_Pri = 5; mTrig2_Int_Pri = 5; \
								  mSetTrigRisingEdge(); \
								}
#define mGetTrig1TimerIntEna()	mTrig1_Int_Ena
#define mGetTrig2TimerIntEna()	mTrig2_Int_Ena



/** macro's Input capture *********************************************************/
#define mIC1Interrupt			_IC1Interrupt
#define mIC2Interrupt			_IC3Interrupt
#define mSetIC1RisingEdge()		{ IC1CON1bits.ICM = 0; IC2CON1bits.ICM = 0; mIC1H_Edge = INPUT_CAPTURE_RISING_EDGE; mIC1L_Edge = INPUT_CAPTURE_RISING_EDGE; }
#define mSetIC1FallingEdge()	{ IC3CON1bits.ICM = 0; IC4CON1bits.ICM = 0; mIC1H_Edge = INPUT_CAPTURE_FALLING_EDGE; mIC1L_Edge = INPUT_CAPTURE_FALLING_EDGE; }
#define mSetIC2RisingEdge()		{ IC1CON1bits.ICM = 0; IC2CON1bits.ICM = 0; mIC2H_Edge = INPUT_CAPTURE_RISING_EDGE; mIC2L_Edge = INPUT_CAPTURE_RISING_EDGE; }
#define mSetIC2FallingEdge()	{ IC3CON1bits.ICM = 0; IC4CON1bits.ICM = 0; mIC2H_Edge = INPUT_CAPTURE_FALLING_EDGE; mIC2L_Edge = INPUT_CAPTURE_FALLING_EDGE;}
#define mDisIC1Interrupts()		{ mIC1_Int_Ena = FALSE; }
#define mDisIC2Interrupts()		{ mIC2_Int_Ena = FALSE; }
#define mDisICInterrupts()		{ mIC1_Int_Ena = FALSE; mIC2_Int_Ena = FALSE; }
#define mSelectIC1()			{ mIC2_Int_Ena = FALSE; mIC1_Int_Flag = FALSE; mIC1_Int_Ena = TRUE; }
#define mSelectIC2()			{ mIC1_Int_Ena = FALSE; mIC2_Int_Flag = FALSE; mIC2_Int_Ena = TRUE; }
#define mInitICInputs()			{ mTRIS_Trig1 = INPUT_PIN; mANSEL_Trig1 = DIGITAL_PIN; \
								  mTRIS_Trig2 = INPUT_PIN; mANSEL_Trig2 = DIGITAL_PIN; \
								  mRPINR_Trig1 = 0; mRPINR_Trig2 = 0; \
								  mRPINR_IC1 = 0x25; mRPINR_IC2	= 0x79; \
								  mDisICInterrupts(); \
								  mIC1_Int_Pri = 5; mIC2_Int_Pri = 5; \
								  IC1CON1bits.ICTSEL = 7; IC1CON1bits.ICI = 1; IC1CON1bits.ICBNE = 0; IC1CON1bits.ICM = 0; \
								  IC1CON2bits.IC32 = 1; IC1CON2bits.ICTRIG = 0; IC1CON2bits.TRIGSTAT = 0; IC1CON2bits.SYNCSEL = 0; \
								  IC2CON1bits.ICTSEL = 7; IC2CON1bits.ICI = 1; IC2CON1bits.ICBNE = 0; IC2CON1bits.ICM = 0; \
								  IC2CON2bits.IC32 = 1; IC2CON2bits.ICTRIG = 0; IC2CON2bits.TRIGSTAT = 0; IC2CON2bits.SYNCSEL = 0b10000; \
								  IC3CON1bits.ICTSEL = 7; IC3CON1bits.ICI = 1; IC3CON1bits.ICBNE = 0; IC3CON1bits.ICM = 0; \
								  IC3CON2bits.IC32 = 1; IC3CON2bits.ICTRIG = 0; IC3CON2bits.TRIGSTAT = 0; IC3CON2bits.SYNCSEL = 0; \
								  IC4CON1bits.ICTSEL = 7; IC4CON1bits.ICI = 1; IC4CON1bits.ICBNE = 0; IC4CON1bits.ICM = 0; \
								  IC4CON2bits.IC32 = 1; IC4CON2bits.ICTRIG = 0; IC4CON2bits.TRIGSTAT = 0; IC4CON2bits.SYNCSEL = 0b10000; \
								}
#define mGetIC1TimerIntEna()	mIC1_Int_Ena
#define mGetIC2TimerIntEna()	mIC2_Int_Ena
#define mDisICInputs()			{ mDisICInterrupts(); IC1CON1bits.ICM = 0; IC2CON1bits.ICM = 0; IC3CON1bits.ICM = 0; IC4CON1bits.ICM = 0; }



/** Outputs macro's Trigger level*******************************************/
#define mInitTrigLevel()		{ mRPOR_Trig_Level = 0x12; \
								  ConfigIntOC3(OC_INT_OFF); \
								  OC3CON1 = 0x3C00; \
								  OC3CON2 = 0; \
								  OC3CON1bits.OCTSEL = 0x07; \
								  mDuty_Cycle_Trig_Level = PWM_CENTER; \
								  mPeriod_Trig_Level = PWM_PERIOD; \
								  OC3CON1bits.OCM = 6; \
								  OC3CON2bits.SYNCSEL = 0x1F; \
								}


/** Input macro's factory defaults button *********************************/
#define mInitFactoryDefaultsPB()	{ mTRIS_Factory_Defaults = INPUT_PIN; mCNPU_Factory_Defaults = TRUE; mCNPD_Factory_Defaults = FALSE; }

/** factory defaults button pin status ************************************/
#define mGetFactoryDefaultsPB()		mPORT_Factory_Defaults


/** Inputs macro's Battery Charger *****************************************/
#define	mInitChargerPG()		{ mANSEL_Charger_PG = DIGITAL_PIN; mTRIS_Charger_PG = INPUT_PIN; mCNPU_Charger_PG = TRUE; }
#define mInitChargerStat1()		{ mANSEL_Charger_Stat1 = DIGITAL_PIN; mTRIS_Charger_Stat1 = INPUT_PIN; mCNPU_Charger_Stat1 = TRUE; }
#define mInitChargerStat2()		{ mANSEL_Charger_Stat2 = DIGITAL_PIN; mTRIS_Charger_Stat2 = INPUT_PIN; mCNPU_Charger_Stat2 = TRUE; }
#define	mInitChargerPins()		{ mInitChargerPG(); mInitChargerStat1(); mInitChargerStat2(); }
#define	mGetChargerPG()			mPORT_Charger_PG
#define	mGetChargerStat1()		mPORT_Charger_Stat1
#define	mGetChargerStat2()		mPORT_Charger_Stat2


/** Init macro Wifi pins ***************************************************/
#define mInitWifiPins()			{ mANSEL_Rx_UART = DIGITAL_PIN; \
								  mANSEL_CTS_UART = DIGITAL_PIN; \
								  mANSEL_Wifi_Tcp_Con = DIGITAL_PIN; \
								  mTRIS_Wifi_Rst = OUTPUT_PIN; \
								  mTRIS_Wifi_Tcp_Con = INPUT_PIN; \
								  mTRIS_UART_Rx  = INPUT_PIN; \
								  mTRIS_UART_CTS = INPUT_PIN; \
								  mLAT_Wifi_Rst = 0; \
								  mRPOR_Tx_UART = 1; \
								  mRPOR_RTS_UART = 2; \
								  mRPINR_Rx_UART = 0x26; \
								  mRPINR_CTS_UART = 0x27; \
								}
#define mWifiReset()			mLAT_Wifi_Rst = 0
#define mReleaseWifiReset()		mLAT_Wifi_Rst = 1
#define mUART1OERR()			U1STAbits.OERR
#define	mClrUART1OERR()			{U1STAbits.OERR = 0; }
#define mWifiTcpOpen()			mPORT_Wifi_Tcp_Con


/** ADC macro's ************************************************************/
#define mInitADCPins()			{ mANSEL_ADC_PD0 = DIGITAL_PIN; \
								  mANSEL_ADC_PD1 = DIGITAL_PIN; \
								  mANSEL_ADC_D0 = DIGITAL_PIN; \
								  mANSEL_ADC_D1 = DIGITAL_PIN; \
								  mANSEL_ADC_D2 = DIGITAL_PIN; \
								  mANSEL_ADC_D3 = DIGITAL_PIN; \
								  mANSEL_ADC_D4 = DIGITAL_PIN; \
								  mANSEL_ADC_D5 = DIGITAL_PIN; \
								  mANSEL_ADC_D6 = DIGITAL_PIN; \
								  mANSEL_ADC_D7 = DIGITAL_PIN; \
								  mANSEL_ADC_AB = DIGITAL_PIN; \
								  mTRIS_ADC_PD0 = OUTPUT_PIN; \
								  mTRIS_ADC_PD1 = OUTPUT_PIN; \
								  mTRIS_ADC_Clk = OUTPUT_PIN; \
								  mTRIS_ADC_D0 = INPUT_PIN; \
								  mTRIS_ADC_D1 = INPUT_PIN; \
								  mTRIS_ADC_D2 = INPUT_PIN; \
								  mTRIS_ADC_D3 = INPUT_PIN; \
								  mTRIS_ADC_D4 = INPUT_PIN; \
								  mTRIS_ADC_D5 = INPUT_PIN; \
								  mTRIS_ADC_D6 = INPUT_PIN; \
								  mTRIS_ADC_D7 = INPUT_PIN; \
								  mTRIS_ADC_AB = INPUT_PIN; \
								  mLAT_ADC_PD0 = 0; \
								  mLAT_ADC_PD1 = 0; \
								  mLAT_ADC_Clk = 0; \
								}
#define mShutdownADC()			{ mLAT_ADC_PD0 = 0; mLAT_ADC_PD1 = 0; }
#define mStandbyADC()			{ mLAT_ADC_PD0 = 0; mLAT_ADC_PD1 = 1; }
#define mIdleADC()				{ mLAT_ADC_PD0 = 1; mLAT_ADC_PD1 = 0; }
#define mRunADC()				{ mLAT_ADC_PD0 = 1; mLAT_ADC_PD1 = 1; }

/** PMP macro's ************************************************************/
#define mInitPMP()				{ PMCONbits.PMPEN = 0; PMCONbits.PSIDL = 1; PMCONbits.ADRMUX = 0; PMCONbits.PTBEEN = 0; PMCONbits.PTWREN = 0; \
								  PMCONbits.PTRDEN = 0; PMCONbits.CSF = 0; \
								  PMMODEbits.IRQM = 0; PMMODEbits.INCM = 1; PMMODEbits.MODE16 = 0; PMMODEbits.MODE = 2; PMMODEbits.WAITM = 0; \
								  PMAEN = 0x0; \
								  PMADDR = 0; \
								  IPC11bits.PMPIP = 0; \
								  IEC2bits.PMPIE = 0; \
								  PMCONbits.PMPEN = 1; \
								}

/** Timebase ************************************************************/
#define mTimebaseInterrupt			_T5Interrupt
#define mOpenTimebaseTimer(a)		{ OpenTimer45(T4_OFF & T4_IDLE_STOP & T4_GATE_OFF & T4_PS_1_1 & T4_SOURCE_INT & T4_32BIT_MODE_ON, a); \
									  ConfigIntTimer45(T5_INT_PRIOR_6 & T5_INT_OFF); \
									}
#define mStartTimebaseTimer()		{ TMR5HLD = 0; TMR4 = 0; _T5IF = 0;	_T5IE = 1; T4CONbits.TON = 1; }
#define mStopTimebaseTimer()		{ CloseTimer45(); }
#define mClrTimebaseTimerIntFlag()	_T5IF = 0
#define mDisTimebaseTimerInt()		_T5IE = 0
#define mGetTimebaseTimerIntEna()	_T5IE


/** Auto Timebase Timer ************************************************************/
#define mAutoTimebaseInterrupt			_T6Interrupt
#define mStartAutoTimebaseTimer()		{ OpenTimer6(T6_ON & T6_IDLE_STOP & T6_GATE_OFF & T6_PS_1_64 & T6_SOURCE_INT &  T6_32BIT_MODE_OFF, 0xFFFF); \
										  ConfigIntTimer6(T6_INT_PRIOR_5 & T6_INT_ON); \
										}
#define mStopAutoTimebaseTimer()		{ CloseTimer6(); }
#define mClrAutoTimebaseTimerIntFlag()	_T6IF = 0
#define mGetAutoTimebaseTimerIntFlag()	_T6IF
#define mDisAutoTimebaseTimerInt()		_T6IE = 0
#define mGetAutoTimebaseTimerIntEna()	_T6IE



/** Auto Trigger Timer ************************************************************/
#define mAutoTrigInterrupt			_T3Interrupt
#define mStartAutoTrigTimer()		{ OpenTimer3(T3_ON & T3_IDLE_STOP & T3_GATE_OFF & T3_PS_1_64 & T3_SOURCE_INT, 0xFFFF); \
									  ConfigIntTimer3(T3_INT_PRIOR_5 & T3_INT_ON); \
									}
#define mStopAutoTrigTimer()		{ CloseTimer3(); }
#define m25msAutoTrigTimer()		{ WriteTimer3(0xC000); }
#define mClrAutoTrigTimerIntFlag()	_T3IF = 0
#define mDisAutoTrigTimerInt()		_T3IE = 0
#define mGetAutoTrigTimerIntEna()	_T3IE

/** Send Timer *********************************************************************/
#define mInitSendTimer()			{ OpenTimer2(T2_OFF & T2_IDLE_STOP & T2_GATE_OFF & T2_PS_1_256 & T2_32BIT_MODE_OFF & T2_SOURCE_INT, 0x8000); \
									  ConfigIntTimer2(T2_INT_PRIOR_4 & T2_INT_OFF); \
									}
#define mStopSendTimer()			{ CloseTimer2(); }
#define mStartSendTimer()			{ T2CONbits.TON = 1; }
#define mClrSendTimerIntFlag()		_T2IF = 0
#define mGetSendTimerIntFlag()		_T2IF


/** Wifi Cmd Reply Timer ************************************************************/
#define mRestartWifiCmdReplyTimer()		{ OpenTimer7(T7_ON & T7_IDLE_STOP & T7_GATE_OFF & T7_PS_1_256 & T7_SOURCE_INT, 0xFFFF); \
										  ConfigIntTimer7(T7_INT_PRIOR_4 & T7_INT_OFF); \
										}
#define mStopWifiCmdReplyTimer()		{ CloseTimer7(); }
#define mGetWifiCmdReplyTimerIntFlag()	_T7IF


/** Wifi Flush Timer (6.5ms) ********************************************************/
#define mRestartWifiFlushTimer()	{ OpenTimer8(T8_ON & T8_IDLE_STOP & T8_GATE_OFF & T8_PS_1_8  & T8_32BIT_MODE_OFF & T8_SOURCE_INT, 0x8000); \
									  ConfigIntTimer8(T8_INT_PRIOR_4 & T8_INT_OFF); \
									}
#define mStopWifiFlushTimer()		{ CloseTimer8(); }
#define mGetWifiFlushTimerIntFlag()	_T8IF


/** Sleep Timer (6.5ms) *************************************************************/
#define mStartSleepTimer()			{ OpenTimer9(T9_ON & T9_IDLE_STOP & T9_GATE_OFF & T8_PS_1_64 & T9_SOURCE_INT, 62500); \
									  ConfigIntTimer9(T9_INT_PRIOR_4 & T8_INT_OFF); \
									}
#define mStopSleepTimer()			{ CloseTimer9(); }
#define mGetSleepTimerIntFlag()		_T9IF

	

#ifdef	__cplusplus
}
#endif

#endif	/* WFS210_HAL_H */

