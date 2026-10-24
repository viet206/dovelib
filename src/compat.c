#include "dove.h"

int compat_str_cmp(char* d, char* d1, uint_t n) {
        if ( d == NIL || d1 == NIL || n == 0 ) return COMPAT_FALSE;

        for ( uint_t i = 0 ; i < n ; ++i ) {
                if ( *d != *d1 ) return COMPAT_FALSE;
                if ( *d == '\0' && *d1 == '\0' ) break;
                ++d;
                ++d1;
        }
        return COMPAT_TRUE;
}

int compat_buf_clear(char* buf, uint_t size) {
        if ( buf == NIL || size == 0 ) return COMPAT_FALSE;

        usize_t* u = (usize_t*) buf;
        uhalf_t* h = (uhalf_t*) buf;
        char* c = buf;

        // Xóa theo khối 8 bytes (usize_t)
        while ( size >= 8 ) {
                *u = 0;
                ++u;
                size -= 8;
        }
        
        // Cập nhật lại vị trí con trỏ h dựa trên vùng nhớ còn lại sau khi trừ khối 8
        h = (uhalf_t*) u;

        // Xóa theo khối 2 bytes (uhalf_t)
        while ( size >= 2 ) {
                *h = 0;
                ++h;
                size -= 2;
        }

        // Cập nhật lại vị trí con trỏ c dựa trên vùng nhớ còn lại
        c = (char*) h;

        // Xóa byte lẻ còn lại nếu có
        if ( size == 1 ) {
                *c = 0;
        }

        return COMPAT_TRUE;
}

int compat_buf_copy(char* dst, char* src, uint_t size) {
        if ( dst == NIL ) return COMPAT_FALSE;
        if ( src == NIL ) return COMPAT_FALSE;
        if ( size == 0 ) return COMPAT_FALSE;

        usize_t* d0 = (usize_t*) dst;
        usize_t* d1 = (usize_t*) src;
        uhalf_t* u0 = (uhalf_t*) dst;
        uhalf_t* u1 = (uhalf_t*) src;
        char* c0 = dst;
        char* c1 = src;

        // Copy theo khối 8 bytes (usize_t)
        while ( size >= 8 ) {
                *d0 = *d1;
                ++d0;
                ++d1;
                size -= 8;
        }

        u0 = (uhalf_t*) d0;
        u1 = (uhalf_t*) d1;

        // Copy theo khối 2 bytes (uhalf_t)
        while ( size >= 2 ) {
                *u0 = *u1;
                ++u0;
                ++u1;
                size -= 2;
        }

        c0 = (char*) u0;
        c1 = (char*) u1;

        // Copy byte lẻ cuối cùng nếu có
        if ( size == 1 ) {
                *c0 = *c1;
        }

        return COMPAT_TRUE;
}

uint_t compat_str_len(char* s, uint_t range) {
        if ( s == NIL ) return 0;
        if ( range == 0 ) return 0;

        char* p = s;

        for ( uint_t i = 0 ; i < range ; ++i ) {
                if ( *s == '\0' ) return (uint_t)(s - p);
                ++s;
        }
        return range; // Trả về tối đa phạm vi nếu không tìm thấy ký tự kết thúc chuỗi '\0'
}
