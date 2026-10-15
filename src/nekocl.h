#ifndef NEKO_CORE_LIB
#define NEKO_CORE_LIB

#define NEKO_VER "0.0.2"

/*
 Mục tiêu của NekoCL
 
 #1 : Freestanding 
 Có thể chạy bất cứ đâu có trình
 biên dịch C thì đây là 1 điểm mạnh
 lớn . Nó không cần phải gắn liền
 với 1 OS , hay 1 thư viện nào cả .
 
 #2 : Khả năng kết hợp cao
 Thiết kế phải độc lập để đảm bảo
 có thể kết hợp với các thư viện
 khác , giúp giảm số lượng code
 ban đầu

 #3 : Được viết như 1 "Extension C"
 Bởi C thì quá tối giản , và nghèo
 những tính năng nâng cao như Table ,
 Hash nên mới có sự xuất hiện của NekoCL
 . Vậy tại sao không sử dụng C++ cho khỏe
 ? bởi nó bây giờ là 1 ngôn ngữ siêu phức
 tạp , giống như 1 nồi lẩu thập cẩm và nhiều
 chi phí ẩn

 #4 : Người dùng của NekoCL là ai ?
 Là những người dùng C , nhưng cần các tính
 năng cấp cao nhưng lại không có đủ chi phí
 để xây dựng chúng từ đầu

 #5 : Thiết kế NekoCL xoay quanh cái gì ?
 Chủ yếu là xoay quanh kiểu động ( dyn_t )
 . Đó là 1 kiểu cho phép lưu trữ nhiều hình
 dạng khác nhau của dữ liệu trong một biến
 , được lấy cảm hứng từ Tagged Union . các
 kiểu cấp cao sau này chẳng hạn như Hash ,
 Array , Table , ... đều sẽ là những hình
 dạng của 1 tập hợp dyn_t

 #6 : Vậy NekoCL có thật sự thay thế libc ?
 Câu trả lời là không . Bởi như tôi đã nói
 nó được viết như 1 Extension C để sử dụng
 các tính năng cấp cao với ít chi phí code
 ban đầu hơn . Nên nói đúng hơn là "NekoCL
 sẽ hỗ trợ libc thay vì thay thế nó".

 #7 : Vậy những gì NekoCL quan tâm trong suốt
 quá trình phát triển ?
 Có khá nhiều , nhưng chủ yếu sẽ quan tâm vào
 tính năng , độ tin cậy

*/

// All value is same true
#define NIL (void*)0
#define FALSE 0
#define TRUE 1

#define DYN_SIZE (int)sizeof(neko_dyn_t)

typedef char* byte_t;
typedef unsigned int len_t;
typedef unsigned short uint2;
typedef unsigned long long usize;
typedef unsigned char bool_t;
typedef void* ptr_t;

typedef enum {
	PTR_T = 0,
	INT_T = 1,
	STR_T = 2,
	UINT_T = 3
}dyn_tag_t;

typedef struct {
	union {
		byte_t p;
		dyn_tag_t tag;
		int _int;
		len_t _uint;
	};
}neko_dyn_t;

typedef neko_dyn_t* dyn_t;

void buf_copy(byte_t dst,byte_t src,len_t size);
void buf_zero(byte_t src,len_t size);

dyn_t dyn_new(byte_t dst,byte_t src,dyn_tag_t tag);

#define is_num(x) ( x >= '0' && x <= '9' )
#define is_alpha(x) ( ( x >= 'a' && x <= 'z' ) || ( x >= 'A' && x <= 'Z') )
#define is_lower(x) ( x >= 'a' && x <= 'z' )
#define is_upper(x) ( x >= 'A' && x <= 'Z' )

#endif
