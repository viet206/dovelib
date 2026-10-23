#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dove.h"

// Hàm phụ trợ in kết quả test
void print_test_header(const char* name) {
    printf("\n========================================\n");
    printf(" [TEST] %s\n", name);
    printf("================================--------\n");
}

int main() {
    printf("=== BAT DAU KIEM THU TOAN BO API DOVE (Ver %s) ===\n", _VER);

    // ==========================================
    // 1. TEST CÁC MACRO KÝ TỰ (is_num, is_alpha, is_lower, is_upper)
    // ==========================================
    print_test_header("1. MACRO KIEM TRA KY TU");
    
    printf("is_num('7'): %d (Mong doi: TRUE/1)\n", is_num('7'));
    printf("is_num('a'): %d (Mong doi: FALSE/0)\n", is_num('a'));
    
    printf("is_alpha('G'): %d (Mong doi: TRUE/1)\n", is_alpha('G'));
    printf("is_alpha('#'): %d (Mong doi: FALSE/0)\n", is_alpha('#'));
    
    printf("is_lower('z'): %d (Mong doi: TRUE/1)\n", is_lower('Z'));
    printf("is_upper('Z'): %d (Mong doi: TRUE/1)\n", is_upper('z'));


    // ==========================================
    // 2. TEST COMPAT FUNCTIONS & ERROR CASES
    // ==========================================
    print_test_header("2. COMPAT FUNCTIONS & ERROR CASES");

    char buf[128];
    
    // 2.1. compat_buf_clear
    compat_buf_clear(buf, sizeof(buf));
    printf("compat_buf_clear thanh cong.\n");

    // [Error Case]: compat_buf_clear với buf = NULL
    bool_t err_clear = compat_buf_clear(NULL, 10);
    printf("[ERROR] compat_buf_clear(NULL) -> Result: %d (Mong doi: FALSE/0)\n", err_clear);

    // 2.2. compat_str_len & compat_str_cmp
    char* sample_str = "DoveFrameworkTest";
    uint_t len = compat_str_len(sample_str, 50);
    printf("compat_str_len(\"%s\") = %u\n", sample_str, len);

    // [Error Case]: compat_str_len với s = NULL
    uint_t err_len = compat_str_len(NULL, 50);
    printf("[ERROR] compat_str_len(NULL) -> Result: %u (Mong doi: 0)\n", err_len);

    char cmp_buf1[] = "Hello";
    char cmp_buf2[] = "Hellz";
    bool_t cmp_res1 = compat_str_cmp(cmp_buf1, cmp_buf1, 5);
    bool_t cmp_res2 = compat_str_cmp(cmp_buf1, cmp_buf2, 5);
    printf("compat_str_cmp(\"Hello\", \"Hello\", 5) = %d (Mong doi: TRUE/1)\n", cmp_res1);
    printf("compat_str_cmp(\"Hello\", \"Hellz\", 5) = %d (Mong doi: FALSE/0)\n", cmp_res2);

    // 2.3. compat_buf_copy (và macro fn_copy)
    bool_t copy_res = fn_copy(buf, sample_str, len + 1);
    printf("fn_copy result: %d | Copied text: %s\n", copy_res, buf);

    // [Error Case]: compat_buf_copy với size = 0 hoặc dst/src = NULL
    bool_t err_copy = compat_buf_copy(buf, sample_str, 0);
    printf("[ERROR] compat_buf_copy(..., 0) -> Result: %d (Mong doi: FALSE/0)\n", err_copy);


    // ==========================================
    // 3. TEST DYN_NEW & TAG_NOT_FOUND ERROR
    // ==========================================
    print_test_header("3. DYN_NEW & TAG_NOT_FOUND");

    char dyn_storage[512];
    compat_buf_clear(dyn_storage, sizeof(dyn_storage));

    int val_i = 999;
    uint_t val_u = 888;
    void* val_p = (void*)buf;

    dyn_t* d_int = dyn_new(dyn_storage, &val_i, INT);
    dyn_t* d_uint = dyn_new(dyn_storage + DYN_SIZE, &val_u, UINT);
    dyn_t* d_ptr = dyn_new(dyn_storage + (DYN_SIZE * 2), &val_p, PTR);

    if (d_int) printf("dyn_new(INT) = %d\n", d_int->type.i);
    if (d_uint) printf("dyn_new(UINT) = %u\n", d_uint->type.u);
    if (d_ptr) printf("dyn_new(PTR) = %p\n", d_ptr->type.p);

    // [Error Case]: dyn_new với src = NULL (Lỗi TAG_NOT_FOUND hoặc FALSE tùy cài đặt lib)
    dyn_t* err_dyn_new = dyn_new(dyn_storage + (DYN_SIZE * 3), NULL, INT);
    printf("[ERROR] dyn_new với src = NULL -> Result code: %d (Mong doi: TAG_NOT_FOUND/%d hoac FALSE)\n", 
           (int)err_dyn_new, TAG_NOT_FOUND);


    // ==========================================
    // 4. TEST DYN_CMP & TAG_NEQ ERROR
    // ==========================================
    print_test_header("4. DYN_CMP & TAG_NEQ");

    int val_i_dup = 999;
    dyn_t* d_int_dup = dyn_new(dyn_storage + (DYN_SIZE * 4), &val_i_dup, INT);

    // So sánh giống nhau
    bool_t cmp_same = dyn_cmp(d_int, d_int_dup);
    printf("dyn_cmp(INT 999, INT 999) = %d (Mong doi: TRUE/1)\n", cmp_same);

    // [Error Case]: So sánh khác tag (INT và UINT) -> Lỗi TAG_NEQ
    bool_t err_tag_neq = dyn_cmp(d_int, d_uint);
    printf("[ERROR] dyn_cmp(INT, UINT) -> Result code: %d (Mong doi: TAG_NEQ/%d)\n", 
           (int)err_tag_neq, TAG_NEQ);


    // ==========================================
    // 5. TEST DYN_STR & ZERO_SIZE ERROR
    // ==========================================
    print_test_header("5. DYN_STR & ZERO_SIZE");

    char str_store[128];
    dyn_t* d_str = dyn_str(str_store, "DoveString", 10);
    if (d_str) {
        printf("dyn_str thanh công. Len: %u, Str: %.*s\n", 
               d_str->type.str.len, (int)d_str->type.str.len, (char*)d_str->type.str.p);
    }

    // [Error Case]: dyn_str với len = 0 -> Lỗi ZERO_SIZE
    dyn_t* err_zero_size = dyn_str(str_store, "Test", 0);
    printf("[ERROR] dyn_str với len = 0 -> Result code: %d (Mong doi: ZERO_SIZE/%d)\n", 
           (int)err_zero_size, ZERO_SIZE);


    // ==========================================
    // 6. TEST LIST_NEW & NOT_ENO_MEM ERROR
    // ==========================================
    print_test_header("6. LIST_NEW & NOT_ENO_MEM");

    char list_buf[256];
    compat_buf_clear(list_buf, sizeof(list_buf));

    char meta_buf[32];
    
    // Gọi tạo list bình thường (giả định thông số hợp lệ)
    dyn_t** my_list = list_new(meta_buf, sizeof(meta_buf), list_buf, sizeof(list_buf), sizeof(dyn_t), 2);
    printf("list_new result pointer: %p\n", (void*)my_list);

    // [Error Case]: list_new với buffer quá nhỏ hoặc số lượng phần tử (idx) vượt mức bộ nhớ -> Lỗi NOT_ENO_MEM
    dyn_t** err_mem_list = list_new(meta_buf, sizeof(meta_buf), list_buf, 10, 100, 5); 
    // 100 * 5 = 500 > 10 (vượt quá len)
    printf("[ERROR] list_new vượt quá bộ nhớ -> Result code: %d (Mong doi: NOT_ENO_MEM/%d)\n", 
           (int)err_mem_list, NOT_ENO_MEM);

    printf("\n========================================\n");
    printf("   HOAN TAT TAT CA KICH BAN KIEM THU API  \n");
    printf("========================================\n");

    return 0;
}
