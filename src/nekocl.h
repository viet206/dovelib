#ifndef NEKO_CORE_LIB
#define NEKO_CORE_LIB

#define NEKO_VER "0.0.2"

/* 
 * MỤC TIÊU ĐỈNH CAO CỦA NEKO CORE LIB
 *
 * #1 : thay thế libc , không phải vì libc
 * dởm , đơn giản là nó vẫn còn quá thô kệch
 * phụ thuộc nặng nề vào OS . NekoCL sinh ra
 * để "cần ít hơn để làm nhiều việc hơn"
 *
 * #2 : Freestanding . Tại sao NekoCL lại
 * chọn con đường Freestanding ? Xuất phát
 * từ ý tưởng "độc lập nền tảng" . code có
 * build bất kỳ môi trường nào hỗ trợ tối
 * thiểu C99 . điều này không chỉ đơn giản
 * giúp lib sạch phụ thuộc hơn , mà giúp
 * dev tập trung hơn vào vấn đề chính.
 *
 * #3 : NekoCL tập trung vào sự linh hoạt ,
 * vì khi có được sự linh hoạt một cách mượt
 * mà , thì Dev sẽ có thể làm được nhiều việc
 * hơn chỉ với 1 thư viện nhỏ như NekoCL
 *
 */

// All value is same true
#define FALSE 0
#define NIL 0
#define TRUE 1

typedef char* byte_t;
typedef unsigned int len_t;
typedef unsigned short uint2;
typedef unsigned long long usize;
typedef unsigned char bool_t;
typedef void* ptr_t;

typedef struct {
	len_t len;
	char str[];
}neko_str_t;

typedef enum {
	PTR_T = 0,
	INT_T = 1,
	CHAR_T = 2,
	LEN_T = 3,
	BOOL_T = 4,
	UINT2_T = 5,
}dyn_tag_t;

typedef struct {
	dyn_tag_t tag;
	union {
		byte_t p;
		int i;
		len_t ui;
		uint2 ui2;
		bool_t b;
		char c;
	};
}neko_dyn_t;

typedef neko_str_t* str_t;
typedef neko_dyn_t* dyn_t;

void buf_copy(byte_t dst,byte_t src,len_t size);
void buf_zero(byte_t src,len_t size);
str_t str_new(byte_t buf,byte_t rstr,len_t len);
int str_2int(str_t s);
bool_t str_cmpz(str_t dst,str_t src,len_t len);
void str_upper(str_t src);
void str_lower(str_t src);
dyn_t dyn_new(byte_t dst,byte_t src,dyn_tag_t tag);

#define dyn_lint(dst,src,tag) dyn_new(dst,(byte_t)&(int){src},tag)
#define dyn_lchar(dst,src,tag) dyn_new(dst,&(char){src},tag)

#define is_num(x) ( x >= '0' && x <= '9' )
#define is_alpha(x) ( ( x >= 'a' && x <= 'z' ) || ( x >= 'A' && x <= 'Z') )
#define is_lower(x) ( x >= 'a' && x <= 'z' )
#define is_upper(x) ( x >= 'A' && x <= 'Z' )

#endif
