#ifndef FREE_STANDARD_LIBRARY
#define FREE_STANDARD_LIBRARY

#define FREESTD_VER "0.0.3"

// All value is same true
#define NIL (void*)0
#define FALSE 0
#define TRUE 1

typedef enum {
	INT = 0x2,
	UINT = 0x3,
	PTR = 0x4
}dyn_tag_t;

typedef struct {
	dyn_tag_t tag;
	
	union {
		int i;
		unsigned int u;
		char* p;
	}type;
}dyn_t;

dyn_t* dyn_new(char* buf,char* src,dyn_tag_t tag);

#define is_num(x) ( x >= '0' && x <= '9' )
#define is_alpha(x) ( ( x >= 'a' && x <= 'z' ) || ( x >= 'A' && x <= 'Z') )
#define is_lower(x) ( x >= 'a' && x <= 'z' )
#define is_upper(x) ( x >= 'A' && x <= 'Z' )

#endif
