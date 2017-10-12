/* 
 * File:   checksum.h
 * Author: edc
 *
 * Created on 1 juli 2013, 16:04
 */

#ifndef CHECKSUM_H
#define	CHECKSUM_H

#ifdef	__cplusplus
extern "C" {
#endif


#include "common.h"


/**
 * calculate the checsum (two's complement of sum of all bytes) 
 * @param pdata		point to begin of array
 * @param size		number of bytes for calculating the checksum
 * @return			checksum
 */
BYTE CalcChecksum(BYTE * pdata, WORD size);


#ifdef	__cplusplus
}
#endif

#endif	/* CHECKSUM_H */

