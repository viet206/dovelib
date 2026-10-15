#include "nekocl.h"

void buf_copy(byte_t dst,byte_t src,len_t size) {
        while (size >= (int)sizeof(usize)) {
                *((usize*)dst) = *((usize*)src);
                dst += sizeof(usize);
                src += sizeof(usize);
                size -= sizeof(usize);
        }

        while (size >= 2) {
                *((uint2*)dst) = *((uint2*)src);
                dst += 2;
                src += 2;
                size -= 2;
        }

        if (size > 0) *dst++ = *src++;
}

void buf_zero(byte_t src,len_t size) {
	while ( size >= (int)sizeof(usize)) {
		*((usize*)src) = 0;
		src += sizeof(usize);
		size -= sizeof(usize);
	}

	while ( size >= 2 ) {
		*((uint2*)src) = 0;
		src += sizeof(uint2);
		size -= 2;
	}

	if ( size > 0 ) *src = 0;
}
