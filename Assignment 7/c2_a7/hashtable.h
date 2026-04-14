#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>

/* --- CẤU HÌNH HỆ THỐNG --- */
#define HASH_TABLE_SIZE 10 
#define MAX_NAME_LEN    50
#define MAX_PHONE_LEN   15

/* --- CẤU TRÚC DỮ LIỆU --- */
typedef struct Node {
    char name[MAX_NAME_LEN];    
    char phone[MAX_PHONE_LEN];  
    struct Node* next;          
} Node;

/* --- CÁC HÀM GIAO TIẾP (API) --- */

/**
 * Function:    init_table
 * Description: Khởi tạo bảng băm về trạng thái trống.
 * Return:      void
 */
void init_table(void);

/**
 * Function:    insert
 * Description: Thêm một liên hệ mới vào bảng băm (xử lý xung đột bằng Chaining).
 */
void insert(char *name, char *phone);

/**
 * Function:    search
 * Description: Tìm kiếm số điện thoại theo tên.
 */
void search(char *name);

/**
 * Function:    delete_contact
 * Description: Xóa liên hệ khỏi hệ thống và giải phóng bộ nhớ.
 */
void delete_contact(char *name);

/**
 * Function:    print_all
 * Description: Hiển thị toàn bộ danh bạ và cấu trúc bảng băm.
 */
void print_all(void);

/**
 * Function:    free_table
 * Description: Giải phóng toàn bộ bộ nhớ của bảng băm trước khi thoát.
 */
void free_table(void);

#endif
