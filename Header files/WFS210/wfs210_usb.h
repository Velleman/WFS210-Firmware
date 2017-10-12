/** 
 * File:   wfs210_usb.h
 * Author: edc
 *
 * Created on 28 juni 2013, 13:52
 */

#ifndef WFS210_USB_H
#define	WFS210_USB_H

#ifdef	__cplusplus
extern "C" {
#endif

//#include "common.h"

//#include "usb_config.h"

#include "usb/usb_function_cdc.h"
#include "usb/usb_device.h"
#include "usb/usb.h"

#include "wfs210/wfs210_protocol.h"
#include "wfs210/parser.h"
#include "wfs210/checksum.h"

#define	WFS210_USB_PACKET_MAX_SIZE			254


extern CONTROL_SIGNAL_BITMAP control_signal_bitmap;


typedef struct
{
	BYTE	*pfrag;
	WORD	sm;
	WORD	bytes_to_send;
	BYTE	stx;
	BYTE	cmd;
	WORD	size;
	WORD	offset;
	BYTE	data[WFS210_USB_PACKET_MAX_SIZE - WFS210_PACKET_HEADER_SIZE];
} WFS210_USB_OUT;


typedef struct
{
	BOOL	mode;
	WORD	size;
	WORD	bytes_to_send;
	BYTE	data[256];
} WFS210_USB_DEBUG_OUT;


typedef struct
{
	char					buffer_in[64];
	char					buffer_out[64];
	BYTE					number_tx_bytes;
	WFS210_USB_OUT			out;
	WFS210_USB_DEBUG_OUT	debug_out;
	PACKET_PARSER			parser;
} WFS210_USB;




#if defined(__C30__) || defined __XC16__
    #if defined(PROGRAMMABLE_WITH_USB_HID_BOOTLOADER)
        /*
         *	ISR JUMP TABLE
         *
         *	It is necessary to define jump table as a function because C30 will
         *	not store 24-bit wide values in program memory as variables.
         *
         *	This function should be stored at an address where the goto instructions
         *	line up with the remapped vectors from the bootloader's linker script.
         *
         *  For more information about how to remap the interrupt vectors,
         *  please refer to AN1157.  An example is provided below for the T2
         *  interrupt with a bootloader ending at address 0x1400
         */
//        void __attribute__ ((address(0x1404))) ISRTable(){
//
//        	asm("reset"); //reset instruction to prevent runaway code
//        	asm("goto %0"::"i"(&_T2Interrupt));  //T2Interrupt's address
//        }
    #endif
#endif


/**
 *
 */
VOID WFS210USBInit(VOID);


/**
 * Copy data from the packet buffer to USB_out buffer and set USB_send flag
 * @param packet pointer to data to send 
 * @return none
 */
VOID WFS210USBTransmit(WFS210_OUT_PACKET *packet);


/**
 *
 * @param debug
 * @return
 */
VOID WFS210SetUSBDebugMode(BOOL debug);


/**
 *
 * @param
 * @return
 */
BOOL WFS210GetUSBDebugMode(VOID);


/**
 *
 * @param
 * @return
 */
BOOL USBConnected(VOID);


/**
 *
 * @param
 * @return
 */
BOOL WFS210USBTxReady(VOID);


/**
 * 
 * @param data
 * @param size
 * @return 
 */
VOID WFS210FeedUSBDebugOut(BYTE *data, WORD size);


/**
 * 
 * @param txmode
 * @return 
 */
VOID WFS210USBTasks(VOID);

/**
 *
 */
VOID CALLBACK WFS210USBReceive(WFS210_IN_PACKET* packet);


/**
 * 
 * @param data
 * @param size
 */
VOID CALLBACK WFS210USBReceiveRaw(BYTE *data, WORD size);


#ifdef	__cplusplus
}
#endif

#endif	/* WFS210_USB_H */

