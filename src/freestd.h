#ifndef FREE_STANDARD_LIBRARY
#define FREE_STANDARD_LIBRARY

#define FREESTD_VER "0.0.3"

// All value is same true
#define NIL (void*)0
#define FALSE 0
#define TRUE 1

typedef unsigned char bool_t;
typedef unsigned int uint_t;

typedef enum {
	INT = 0x0,
	UINT = 0x01,
	PTR = 0x03,
	PTR_INT = 0x04,
	PTR_UINT = 0x05
}tag_t;

typedef struct {
	tag_t tag;
	
	union {
		struct {
			uint_t len;
			char* p;
		}str;

		uint_t u;
		int i;
		void* p;
		int* int_p;
		uint_t* uint_p;
	}type;
}dyn_t;

dyn_t* dyn_new(char* buf,void* src,tag_t tag);

#define is_num(x) ( x >= '0' && x <= '9' )
#define is_alpha(x) ( ( x >= 'a' && x <= 'z' ) || ( x >= 'A' && x <= 'Z') )
#define is_lower(x) ( x >= 'a' && x <= 'z' )
#define is_upper(x) ( x >= 'A' && x <= 'Z' )

#endif
