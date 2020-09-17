#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include "rc_funcs.h"


void main () {

	 unsigned char data[] = {0x04, 0x0A, 0xE6, 0xF0, 0x05, 0xA3, 0x00, 0x12,
		                     0x34, 0x56, 0x78, 0x90, 0x08, 0x00, 0x45, 0x00,
		                     0x00, 0x30, 0xB3, 0xFE, 0x00, 0x00, 0x80, 0x11,
		                     0x72, 0xBA, 0x0A, 0x00, 0x00, 0x03, 0x0A, 0x00,
		                     0x00, 0x02, 0x04, 0x00, 0x04, 0x00, 0x00, 0x1C,
		                     0x89, 0x4D, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
		                     0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D,
		                     0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 
		                     0x00, 0x00, 0x00, 0x00};

	uint32_t crc = crc32(sizeof(data)-4, data);
	fprintf(stderr, "L(data): %u -- CRC: %"PRIx32"\n",sizeof(data),crc);

	//crc = htonl(crc);
	memcpy(&(data[62]), &crc, sizeof(crc));

	fprintf(stderr, "CRC in pack: %"PRIx32"\n",*(uint32_t *)&(data[62]));

	data[13] = 0xff;

	fprintf(stderr, "CRC: %"PRIx32"\n",crc32(sizeof(data), data));
}




