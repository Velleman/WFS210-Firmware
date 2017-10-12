#include "wfs210/buffer.h"

VOID BufferInit(WFS210_BUFFER *buffer)
{
	buffer->pfeedpos = buffer->data;
	buffer->pdatapos = buffer->data;
	buffer->freespace = MAX_BUFFER_SIZE;
}


VOID BufferFeed(WFS210_BUFFER *buffer, BYTE* data, WORD size)
{
	WORD fill;

	// check enough free space into parser buffer
	if (size > buffer->freespace)
	{ // free-up space
		if (buffer->pdatapos > buffer->data)
		{
			fill = buffer->pfeedpos - buffer->pdatapos;
			memcpy((void *)buffer->data, (const void *)buffer->pdatapos, fill);
			buffer->pdatapos = buffer->data;
			buffer->pfeedpos = buffer->pdatapos + fill;
			buffer->freespace = MAX_BUFFER_SIZE - fill;
		}
		// limit size to freespace into buffer
		if (size > buffer->freespace) size = buffer->freespace;
	}

	// add data to buffer
	memcpy((void *)buffer->pfeedpos, (const void *)data, size);

	// update feed position and free space
	buffer->pfeedpos += size;
	buffer->freespace -= size;
}


WORD BufferGetSize(WFS210_BUFFER *buffer)
{
	return (buffer->pfeedpos - buffer->pdatapos);
}

VOID BufferRemoveData(WFS210_BUFFER *buffer, WORD size)
{
	buffer->pdatapos += size;
}

inline BYTE BufferPeek(WFS210_BUFFER *buffer, WORD pos)
{
	return *(buffer->pdatapos + pos);
};

inline BYTE* BufferGetData(WFS210_BUFFER *buffer)
{
	return buffer->pdatapos;
}


