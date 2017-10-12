#ifndef HARDWARE_PROFILE_H
#define HARDWARE_PROFILE_H

	#include <xc.h>

    /*******************************************************************/
    /******** USB stack hardware selection options *********************/
    /*******************************************************************/
    //This section is the set of definitions required by the MCHPFSUSB
    //  framework.  These definitions tell the firmware what mode it is
    //  running in, and where it can find the results to some information
    //  that the stack needs.
    //These definitions are required by every application developed with
    //  this revision of the MCHPFSUSB framework.  Please review each
    //  option carefully and determine which options are desired/required
    //  for your application.


    /*******************************************************************/
    /*******************************************************************/
    /*******************************************************************/
    /******** Application specific definitions *************************/
    /*******************************************************************/
    /*******************************************************************/
    /*******************************************************************/

    /** Board definition ***********************************************/
    //  These defintions will tell the main() function which board is
    //  currently selected.  This will allow the application to add
    //  the correct configuration bits as wells use the correct
    //  initialization functions for the board.  These defitions are only
    //  required in the stack provided demos.  They are not required in
    //  final application design.

	/** Clock **************************************************************/
	#define GetSystemClock()        40000000UL
	#define GetPeripheralClock()    40000000UL
	#define FCY						40000000UL

	//#define USE_SELF_POWER_SENSE_IO
	#define tris_self_power     TRISAbits.TRISA2    // Input
	#define self_power          1

	#define USE_USB_BUS_SENSE_IO
	//#define tris_usb_bus_sense  TRISDbits.TRISD8    // Input
	#define USB_BUS_SENSE       U1OTGSTATbits.VBUSVD


#endif  //HARDWARE_PROFILE_H
