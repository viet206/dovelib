#include "nekocl.h"

typedef struct {
	len_t len;
	char* str;
}msg_t;

str_t sig_2msg(byte_t buf,sig_t sig) {
	static const msg_t msg_tab[] = {
		[SIG_NULL] =
		{ 
		.len = 17 ,
		.str = "Null pointer"
		}
	};

	if ( buf == SIG_NULL ) return (void*)SIG_NULL;

	str_t s = (str_t) buf;

	s->len = msg_tab[sig].len;

	buf_copy(s->str,msg_tab[sig].str,s->len);

	return s;
}
