#include "nekocl.h"

str_t str_new(byte_t buf,byte_t rstr,len_t len) {
	if ( buf == NULL ) return SIG_BUF_NIL;
	if ( rstr == NULL ) return SIG_ADDR_NIL;

	str_t s = (str_t) buf;

	s->len = len;
	buf_copy(s->str,rstr,len);

	return s;
}
