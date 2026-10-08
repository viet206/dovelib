#ifndef NEKO_CORE_LIB
#define NEKO_CORE_LIB

#define NULL 0x0

typedef char* byte_t;
typedef unsigned int len_t;
typedef unsigned short uint2;
typedef unsigned long long usize;

typedef enum {
	SIG_BUF_NIL = 0x00000001,
	SIG_ADDR_NIL = 0x00000002,
}sig_t;

typedef struct {
	len_t len;
	char str[];
}neko_str_t;

typedef neko_str_t* str_t;
typedef char** node_t;

void buf_copy(byte_t dst,byte_t src,len_t size);
void buf_zero(byte_t src,len_t size);

str_t str_new(byte_t buf,byte_t rstr,len_t len);
len_t str_len(byte_t rstr);

str_t sig_2msg(byte_t buf,sig_t sig);

#endif
