/* 
 * File:   parser.h
 * Author: edc
 *
 * Created on 28 juni 2013, 14:28
 */

#ifndef PARSER_H
#define	PARSER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "wfs210/buffer.h"

#include "wfs210/wfs210_protocol.h"
#include "wfs210/checksum.h"
#include <string.h>

typedef struct
{
	WFS210_BUFFER	buffer;
} PACKET_PARSER;

/**
 * Initialize the parser packet
 * @param	none
 * @return	none
 */
VOID InitParser(PACKET_PARSER *parser);

/**
 *
 * @param parser
 * @param data
 * @param size
 * @return
 */
VOID FeedParser(PACKET_PARSER *parser, BYTE* data, BYTE size);

/**
 *
 * @param parser
 * @param packet
 * @return
 */
BOOL ParsePacket(PACKET_PARSER *parser, WFS210_IN_PACKET* packet);



#ifdef	__cplusplus
}
#endif

#endif	/* PARSER_H */

