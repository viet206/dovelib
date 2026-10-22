#ifndef DOVE_LIB
#define DOVE_LIB

#define _VER "0.0.5"
#define fn_copy compat_buf_copy
#define DYN_SIZE (int)sizeof(dyn_t)

typedef enum {
	FALSE = 0,
	TRUE = 1,
	OOM = 2,
	TAG_NOT_FOUND = 3
}err_t;
#define NIL (void*) FALSE

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

// Primitive function+
bool_t compat_str_cmp(char* d,char* d1,uint_t n);
uint_t compat_str_len(char* s,uint_t range);
bool_t compat_buf_copy(char* dst,char* src,uint_t size);
char** compat_alloc_buf(char* mt_buf,uint_t mt_len,char *buf,uint_t len,uint_t blk_size,uint_t elm);
bool_t compat_buf_clear(char* buf,uint_t size);
bool_t compat_str_cmp(char* d,char* d1,uint_t n);

// dyn_t* function
bool_t dyn_cmp(dyn_t* d1,dyn_t* d2);

#define is_num(x) ( x >= '0' && x <= '9' )
#define is_alpha(x) ( ( x >= 'a' && x <= 'z' ) || ( x >= 'A' && x <= 'Z') )
#define is_lower(x) ( x >= 'a' && x <= 'z' )
#define is_upper(x) ( x >= 'A' && x <= 'Z' )

#endif
