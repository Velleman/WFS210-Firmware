/* 
 * File:   buffer.h
 * Author: edc
 *
 * Created on 17 september 2013, 11:07
 */

#ifndef BUFFER_H
#define	BUFFER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "common.h"
#include <string.h>

#define MAX_BUFFER_SIZE	1024 //256

typedef struct
{
	BYTE	*pfeedpos;					// position into buffer for adding new data
	BYTE	*pdatapos;					// start position into buffer to parse
	WORD	freespace;
	BYTE	data[MAX_BUFFER_SIZE];
} WFS210_BUFFER;
	

/**
 * Initialize the parser packet
 * @param	none
 * @return	none
 */
VOID BufferInit(WFS210_BUFFER *buffer);


/**
 * Feed the packet parser with bytes received from th usb host
 * @param data
 * @return
 */
VOID BufferFeed(WFS210_BUFFER *buffer, BYTE *data, WORD size);


/**
 * 
 * @param buffer
 * @return 
 */
WORD BufferGetSize(WFS210_BUFFER *buffer);


/**
 * 
 * @param buffer
 * @param size
 * @return 
 */
VOID BufferRemoveData(WFS210_BUFFER *buffer, WORD size);


/**
 * 
 * @param buffer
 * @return 
 */
inline BYTE BufferPeek(WFS210_BUFFER *buffer, WORD pos);

/**
 *
 * @param buffer
 * @return
 */
inline BYTE* BufferGetData(WFS210_BUFFER *buffer);

#ifdef	__cplusplus
}
#endif

#endif	/* BUFFER_H */

