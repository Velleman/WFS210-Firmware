#include "config.h"
#include "common.h"
#include "wfs210/wfs210.h"

static void InitializeSystem(void);

int main(void)
{   
	InitializeSystem();

	WFS210Init();
	while(TRUE)
    {
		WFS210Tasks();
	}
}

static void InitializeSystem(void)
{
	// Configure the device PLL to obtain 40 MIPS operation. The crystal
	// frequency is 12MHz. Divide 12MHz by 3, multiply by 40 and divide by 2.
	// This results in Fosc of 80MHz. The CPU clock frequency is
	// Fcy = Fosc/2 = 40MHz. Wait for the Primary PLL to lock and then
	// configure the auxilliary PLL to provide 48MHz needed for USB Operation.

 	PLLFBD = 38;				// M  = 40
	CLKDIVbits.PLLPOST = 0;		// N2 = 2
	CLKDIVbits.PLLPRE = 1;		// N1 = 3
	CLKDIVbits.DOZE = 0;		// N1 = 3
	CLKDIVbits.DOZEN = 0;		// processor clock = peripheral clock

	// Initiate Clock Switch to Primary Oscillator with PLL (NOSC= 0x3)
	
	__builtin_write_OSCCONH(0x03);
	__builtin_write_OSCCONL(0x01);
	
	// Wait for the Primary PLL to lock
	while (OSCCONbits.COSC != 0x3);

	// Wait for PLL lock
	while (OSCCONbits.LOCK != 1);

	// Configuring the auxiliary PLL, since the primary
	// oscillator provides the source clock to the auxiliary
	// PLL, the auxiliary oscillator is disabled. Note that
	// the AUX PLL is enabled. The input 12MHz clock is divided
	// by 3, multiplied by 24 and then divided by 2.
	// Wait till the AUX PLL locks.

	ACLKCON3bits.AOSCMD = 0;			// Auxillary oscillator is disabled
	ACLKCON3bits.FRCSEL = 0;			// FRC is not APLL clock source
	ACLKCON3bits.ASRCSEL = 1;			// Primary oscillator is APLL clock source
	ACLKCON3bits.APLLPRE = 2;			// APLL input divider = 3
	ACLKCON3bits.APLLPOST = 6;			// APLL output divider = 2
	ACLKCON3bits.SELACLK = 1;			// Primary PLL not as source for auxillary clock divider
	ACLKDIV3 = 0x7;						// APLL multiplier = 24
	ACLKCON3bits.ENAPLL = 1;			// Enable APLL

	while(ACLKCON3bits.APLLCK != 1);	// Wait till the AUX PLL locks.

	// REFCLKO output as AD clock
	REFOCONbits.ROON = 0;
	REFOCONbits.RODIV = 3;
	REFOCONbits.ROON = 1;
	RPOR2bits.RP68R = 0x31;
}