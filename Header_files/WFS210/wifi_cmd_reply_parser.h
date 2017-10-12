/* 
 * File:   wifi_cmdreply_parser.h
 * Author: edc
 *
 * Created on 18 september 2013, 14:44
 */

#ifndef WIFI_CMD_REPLY_PARSER_H
#define	WIFI_CMD_REPLY_PARSER_H

#ifdef	__cplusplus
extern "C" {
#endif



#include "wfs210/buffer.h"
#include <string.h>

typedef struct
{
	WFS210_BUFFER	buffer;
} WIFI_CMD_REPLY_PARSER;


/**
 * Initialize the parser packet
 * @param	none
 * @return	none
 */
VOID InitWifiCmdReplyParser(WIFI_CMD_REPLY_PARSER *parser);


/**
 *
 * @param parser
 * @return
 */
BOOL WifiCmdParserEmty(WIFI_CMD_REPLY_PARSER *parser);


/**
 *
 * @param parser
 * @param data
 * @param size
 * @return
 */
VOID FeedWifiCmdReplyParser(WIFI_CMD_REPLY_PARSER *parser, BYTE* data, BYTE size);

/**
 *
 * @param parser
 * @param packet
 * @return
 */
BOOL ParseWifiCmdReply(WIFI_CMD_REPLY_PARSER *parser, char *cmd);



#ifdef	__cplusplus
}
#endif

#endif	/* WIFI_CMD_REPLY_PARSER_H */

