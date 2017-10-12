/* 
 * File:   common.h
 * Author: edc
 *
 * Created on 28 juni 2013, 13:54
 */

#ifndef COMMON_H
#define	COMMON_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "GenericTypeDefs.h"
#include "HardwareProfile.h"
#include <xc.h>


//#define DEBUGGING	// TODO: comment for real device


#define ANALOG_PIN	 1
#define DIGITAL_PIN	 0

#define INPUT_PIN	1
#define OUTPUT_PIN	0

#define CALLBACK
#define INTERRUPT

#ifdef	__cplusplus
}
#endif

#endif	/* COMMON_H */

