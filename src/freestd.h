#ifndef FREE_STANDARD_LIBRARY
#define FREE_STANDARD_LIBRARY

#define FREESTD_VER "0.0.4"
#define fn_copy buf_copy
#define DYN_SIZE (int)sizeof(dyn_t)

#define NIL (void*)0
#define FALSE 0
#define TRUE 1

typedef unsigned char bool_t;
typedef unsigned int uint_t;
typedef unsigned long long ull_t;
typedef unsigned short uhalf_t;

typedef enum {
	INT = 0x0,
	UINT = 0x01,
	PTR = 0x03,
	PTR_INT = 0x04,
	PTR_UINT = 0x05,
	STR = 0x06
}tag_t;

typedef struct {
	uint_t len;
	char* p;
}str_t;

typedef union {
	str_t str;
	int i;
	uint_t u;
	void* p;
	int* int_p;
	uint_t* uint_p;
}dyn_type;

typedef struct {
	tag_t tag;
	dyn_type type;	
}dyn_t;

dyn_t* dyn_new(char* buf,void* src,tag_t tag);
uint_t str_len(char* s,uint_t range);
bool_t dyn_cmp(dyn_t* d1,dyn_t* d2);
bool_t buf_copy(char* dst,char* src,uint_t size);
bool_t buf_zero(char* buf,uint_t size);
dyn_t* dyn_str(char* buf,char* s,uint_t range);
char** alloc_buf(char* mt_buf,uint_t mt_len,char* buf,uint_t len,uint_t blk_size,uint_t elm);

#define is_num(x) ( x >= '0' && x <= '9' )
#define is_alpha(x) ( ( x >= 'a' && x <= 'z' ) || ( x >= 'A' && x <= 'Z') )
#define is_lower(x) ( x >= 'a' && x <= 'z' )
#define is_upper(x) ( x >= 'A' && x <= 'Z' )

#endif
