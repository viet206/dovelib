#ifndef NEKO_CORE_LIB
#define NEKO_CORE_LIB

typedef char* byte_t;
typedef unsigned int len_t;

typedef enum {
	SIG_BUF_NIL = 0x00000001,
	SIG_ADDR_NIL = 0x00000002,
}sig_t;

typedef struct {
	len_t len;
	char data[];
}neko_str_t;

sig_t buf_copy(byte_t dst,byte_t src,len_t len);

str_t str_new(byte_t buf,byte_t rstr,len_t len);
len_t str_len(byte_t rstr);

str_t sig_2msg(sig_t sig);

#endif
