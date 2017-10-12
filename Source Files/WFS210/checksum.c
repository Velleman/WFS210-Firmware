#include "WFS210/checksum.h"


BYTE CalcChecksum(BYTE * pdata, WORD size)
{
	BYTE checksum = 0;
	WORD i;

	for (i=0; i < size; i++) checksum += *pdata++;
	return -checksum;
}



