#ifndef NEKO_CORE_LIB
#define NEKO_CORE_LIB

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
 * #3 : lý do quan trọng nhất của tất cả lý
 * do khác . đó là "HÃY ĐỂ NÓ ĐƠN GIẢN NẾU
 * KHÔNG CÓ GÌ PHỨC TẠP"
 *
 */

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
int str_2int(str_t s);
sig_t str_cmpz(str_t dst,str_t src,len_t len);

str_t sig_2msg(byte_t buf,sig_t sig);

#endif
