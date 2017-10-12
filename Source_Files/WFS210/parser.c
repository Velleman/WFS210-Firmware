#include "wfs210/parser.h"


VOID InitParser(PACKET_PARSER *parser)
{
	BufferInit(&parser->buffer);
}

VOID FeedParser(PACKET_PARSER *parser, BYTE* data, BYTE size)
{
	BufferFeed(&parser->buffer, data, size);
}

BOOL ParsePacket(PACKET_PARSER *parser, WFS210_IN_PACKET *packet)
{
	WORD_VAL	packet_size;
	BYTE		*pdata;

	while (BufferGetSize(&parser->buffer) > 0)
	{
		// get number of bytes into parser buffer
		//fill =  WFS210BufferGetSize(parser->buffer);		//wfs210parser.pfeedpos - wfs210parser.pstartpos;

		// find STX position;
		while ((BufferGetSize(&parser->buffer) > 0)  && (BufferPeek(&parser->buffer, 0) != WFS210_STX))
		{
			BufferRemoveData(&parser->buffer, 1);
		}

		// skip if smallest packet not yet into parse buffer
		if (BufferGetSize(&parser->buffer) < WFS210_IN_PACKET_MIN_SIZE) return FALSE;

		// Create a helper variable that points to the start of the parsable data (STX)
		pdata = BufferGetData(&parser->buffer);
		
		// calculate packet size
		packet_size.byte.LB = pdata[WFS210_PACKET_SIZE_INDEX];
		packet_size.byte.HB = pdata[WFS210_PACKET_SIZE_INDEX + 1];

		// validate packet size
		if ((packet_size.Val < WFS210_IN_PACKET_MIN_SIZE) || (packet_size.Val > WFS210_IN_PACKET_MAX_SIZE))
		{ // invalid
			BufferRemoveData(&parser->buffer, 1);
			continue;
		}

		// skip if complete packet not yet into parse buffer
		if (BufferGetSize(&parser->buffer) < packet_size.Val) return FALSE;

		// skip if no valid ETX
		if (pdata[packet_size.Val - 1] != WFS210_ETX)
		{ // invalid
			BufferRemoveData(&parser->buffer, 1);
			continue;
		}

		// skip if no valid checksum
		if (pdata[packet_size.Val - 2] != CalcChecksum(BufferGetData(&parser->buffer), packet_size.Val - 2))
		{ // invalid
			BufferRemoveData(&parser->buffer, 1);
			continue;
		}

		// load valid packet
		memcpy((void*)packet, (const void*)pdata, packet_size.Val);

		// remove packet from parser buffer
		BufferRemoveData(&parser->buffer, packet_size.Val);	//wfs210parser.pstartpos += packetsize.Val;

		// check parser buffer is empty
		if (BufferGetSize(&parser->buffer) == 0) BufferInit(&parser->buffer);

		return TRUE;
	}

	return FALSE;
}


