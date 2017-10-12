#include "wfs210/wifi_cmd_reply_parser.h"


VOID InitWifiCmdReplyParser(WIFI_CMD_REPLY_PARSER *parser)
{
	BufferInit(&parser->buffer);
}


BOOL WifiCmdParserEmty(WIFI_CMD_REPLY_PARSER *parser)
{
	return (BufferGetSize(&parser->buffer) == 0);
}


VOID FeedWifiCmdReplyParser(WIFI_CMD_REPLY_PARSER *parser, BYTE* data, BYTE size)
{
	BufferFeed(&parser->buffer, data, size);
}


BOOL ParseWifiCmdReply(WIFI_CMD_REPLY_PARSER *parser, char *cmd)
{
	WORD size;
	BYTE *start, *end;

	if ( BufferGetSize(&parser->buffer) > 0)
	{
		// search linefeed as end of cmd reply
		end = memchr(BufferGetData(&parser->buffer), '\n', BufferGetSize(&parser->buffer));
//		if (end == NULL) end = memchr(BufferGetData(&parser->buffer), '\0', BufferGetSize(&parser->buffer));

		// if end of cmd found
		if (end != NULL)
		{
			// Create a helper variable that points to the start of the parsable data
			start = BufferGetData(&parser->buffer);

			// load valid cmd
			size = end - start + 1;
			memcpy((void*)cmd, (const void*)start, size);
			cmd[size] = '\0';

			// remove cmd from parser buffer
			BufferRemoveData(&parser->buffer, size);

			// check parser buffer is empty
			if (BufferGetSize(&parser->buffer) == 0) BufferInit(&parser->buffer);

			return TRUE;
		}
	}

	return FALSE;
}

