/* 
 * File:   interrupt.h
 * Author: edc
 *
 * Created on 28 juni 2013, 14:17
 */

#ifndef INTERRUPT_H
#define	INTERRUPT_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "common.h"

VOID YourHighPriorityISRCode(VOID);
VOID YourLowPriorityISRCode(VOID);

#ifdef	__cplusplus
}
#endif

#endif	/* INTERRUPT_H */

