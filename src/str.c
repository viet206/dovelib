#include "nekocl.h"

str_t str_new(byte_t buf,byte_t rstr,len_t len) {
	if ( buf == NIL || rstr == NIL ) return NIL;

	str_t s = (str_t) buf;

	s->len = len;
	buf_copy(s->str,rstr,len);

	return s;
}

bool_t str_cmpz(str_t dst,str_t src,len_t len) {
	char* pdst = dst->str;
	char* psrc = src->str;

	while ( len < (int)sizeof(usize)) {
		if ( (usize)*pdst != (usize)*psrc ) {
			return FALSE;
		}
		pdst += (int)sizeof(usize);
		psrc += (int)sizeof(usize);
	}

	while ( len < 2 ) {
		if ( (usize)*pdst != (usize)*psrc ) {
			return FALSE;
		}
		pdst += 2;
		psrc += 2;
	}

	if ( len > 1 ) {
		if ( psrc != pdst ) {
			return FALSE;
		}
	}

	return TRUE;
}

void str_upper(str_t s) {
	char* p = s->str;

	while ( *p != '\0' ) {
		if ( *p >= 'a' && *p <= 'z' ) {
			if ( *p == ' ' ) ++p;
			*p -= 32;
		}
		++p;
	}
}

void str_lower(str_t s) {
	char* p = s->str;

	while ( *p != '\0' ) {
		if ( *p >= 'A' && *p <= 'Z' ) {
			if ( *p == ' ' ) ++p;
			*p += 32;
		}
		++p;
	}
}

int str_2int(str_t s) {
	int reslut = 0;
	int i = 0;
	int num_signed = 0;
	char* num = s->str;
	
	if ( num[i] == '-' ) {
		num_signed = 1;
		++i;
	}else if ( num[i] == '+' ) ++i;

	for ( ; i < (int)s->len ; ++i ) {
		if ( num[i] >= '0' && num[i] <= '9' ) {
			reslut = reslut * 10 + ( num[i] - '0' );
		}
	}

	if ( num_signed == 1 ) {
		reslut = -(reslut);
	}
	return reslut;
}
