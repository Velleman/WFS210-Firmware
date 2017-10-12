/********************************************************************
 FileName:      Config.h
 Dependencies:  See INCLUDES section
 Processor:     PIC18, PIC24, dsPIC33, or PIC32 USB Microcontrollers
 Hardware:      This demo is natively intended to be used on Microchip USB demo
                boards supported by the MCHPFSUSB stack.  See release notes for
                support matrix.  The firmware may be modified for use on
                other USB platforms by editing this file (HardwareProfile.h)
                and adding a new hardware specific 
                HardwareProfile - [platform name].h file.
 Compiler:      Microchip C18 (for PIC18), C30 (for PIC24/dsPIC33), or C32 (for PIC32)
 Company:       Microchip Technology, Inc.

 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the "Company") for its PIC® Microcontroller is intended and
 supplied to you, the Company's customer, for use solely and
 exclusively on Microchip PIC Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

********************************************************************/

#ifndef CONFIG_H
#define CONFIG_H

#include "common.h"


/** CONFIGURATION **************************************************/

	// General Segment Write-Protect bit: General Segment may be written
	// General Segment Code-Protect bit: General Segment Code protect is disabled
	// General Segment Key bits: General Segment Write Protection and Code Protection is Disabled
	_FGS(GWRP_OFF & GSS_ON & GSSK_ON);

	// Initial Oscillator Source Selection bits: Primary Oscillator (XT, HS, EC) with PLL
	// Two-speed Oscillator Start-up Enable bit: Start up with user-selected oscillator source
	_FOSCSEL(FNOSC_PRIPLL & IESO_OFF);

	// Primary Oscillator Mode: HS Crystal Oscillator Mode
	// OSC2 Pin Function bit: OSC2 is clock output
	// Peripheral pin select configuration: Allow multiple reconfigurations
	// Clock Switching Mode bits: Clock switching is enabled,Fail-safe Clock Monitor is disabled
	_FOSC(FCKSM_CSECMD & IOL1WAY_OFF & OSCIOFNC_OFF & POSCMD_HS);

	// Watchdog Timer Postscaler bits: 1:32,768
	// Watchdog Timer Prescaler bit: 1:128
	// PLL Lock Wait Enable bit: Clock switch to PLL source will wait until the PLL lock signal is valid
	// Watchdog Timer Window Enable bit: Watchdog Timer in Non-Window mode
	// Watchdog Timer Enable bit: Watchdog timer enabled/disabled by user software
	_FWDT(WDTPOST_PS32768 & WDTPRE_PR128 & PLLKEN_ON & WINDIS_OFF & FWDTEN_OFF);

	// Power-on Reset Timer Value Select bits: 128ms
	// Brown-out Reset (BOR) Detection Enable bit: BOR is enabled
	// Alternate I2C pins for I2C1: SDA1/SCK1 pins are selected as the I/O pins for I2C1
	_FPOR(FPWRT_PWR128 & BOREN_ON & ALTI2C1_OFF);

	// ICD Communication Channel Select bits: Communicate on PGEC3 and PGED3
	// Reset Target Vector Select bit: Device will obtain reset instruction from Auxilary instead of Primary flash
	// JTAG Enable bit: JTAG is disabled
// TODO
	_FICD(ICS_PGD3 & RSTPRI_PF & JTAGEN_OFF);
//	_FICD(ICS_PGD3 & RSTPRI_AF & JTAGEN_OFF);

	// Auxiliary Segment Write-protect bit: Aux Flash may be written
	// Auxiliary Segment Code-protect bit: Aux Flash Code protect is disabled
	// Auxiliary Segment Key bits: Aux Flash Write Protection and Code Protection is Disabled
	_FAS(AWRP_ON & APL_ON & APLK_ON);

#endif  //CONFIG_H
