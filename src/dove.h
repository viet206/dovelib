#ifndef DOVE_LIB
#define DOVE_LIB

#define _VER "0.0.6"
#define fn_copy compat_buf_copy
#define DYN_SIZE (int)sizeof(dyn_t)
#define NIL (void*)0

typedef unsigned int uint_t;
typedef unsigned long long usize_t;
typedef unsigned short uhalf_t;

typedef enum {
        COMPAT_FALSE = 0,
        COMPAT_TRUE = 1,
	PTR_NIL = 2,
	TAG_NEQ = 3,
	ENO_SIZE = 4,
	ENO_MEM = 5
}msg_t;

typedef struct {
        uint_t len;
        char* p;
} str_t;

typedef enum {
	INT,
	STR,
	UINT_T,
	PTR,
}dyn_tag;

typedef struct {
        dyn_tag tag;
        union {
		int i;
		str_t s;
		uint_t u;
		void* _v;
		int* _i;
		uint_t* _u;
	};
} dyn_t;

typedef struct {
	uint_t size;
	char d[];
}buf_t;

typedef union {
 int* _i;
 char* _c;
 uint_t* _u;
 dyn_t* _d;
 void* _v;
 } ptr_t;

// Compat function
int compat_str_cmp(char* d, char* d1, uint_t n);
uint_t compat_str_len(char* s, uint_t range);
int compat_buf_copy(char* dst, char* src, uint_t size);
int compat_buf_clear(char* buf, uint_t size);

// Core function
dyn_t* dyn_str(char* buf, char* src, uint_t len);
int dyn_cmp(dyn_t* d1, dyn_t* d2);
dyn_t** list_new(char* mt, uint_t mt_len, char* buf, uint_t len, uint_t blk_size, uint_t idx);
dyn_t* dyn_new(char* buf, void* src, dyn_tag t);

#define cif(stat) if ( stat >= COMPAT_FALSE && stat <= ENO_MEM )
#define is_num(x) ( x >= '0' && x <= '9' )
#define is_alpha(x) ( ( x >= 'a' && x <= 'z' ) || ( x >= 'A' && x <= 'Z') )
#define is_lower(x) ( x >= 'a' && x <= 'z' )
#define is_upper(x) ( x >= 'A' && x <= 'Z' )
#endif
