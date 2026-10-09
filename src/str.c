#include "nekocl.h"

str_t str_new(byte_t buf,byte_t rstr,len_t len) {
	if ( buf == SIG_NULL ) return (void*)SIG_NULL;
	if ( rstr == SIG_NULL ) return (void*)SIG_NULL;

	str_t s = (str_t) buf;

	s->len = len;
	buf_copy(s->str,rstr,len);

	return s;
}
