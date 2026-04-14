#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* --- CẤU HÌNH HỆ THỐNG (Ganssle Standard) --- */
#define HASH_TABLE_SIZE 10 
#define MAX_NAME_LEN    50
#define MAX_PHONE_LEN   15

/* --- CẤU TRÚC DỮ LIỆU --- */
typedef struct Node {
    char name[MAX_NAME_LEN];    
    char phone[MAX_PHONE_LEN];  
    struct Node* next;          
} Node;

/* Bảng băm toàn cục */
Node* buckets[HASH_TABLE_SIZE] = {NULL};

/* * Function:    hash
 * Description: Chuyển đổi một chuỗi ký tự thành chỉ số mảng (index) bằng thuật toán đa thức.
 * Parameter:   str - Con trỏ đến chuỗi ký tự cần băm.
 * Return:      Giá trị index nguyên không dấu trong khoảng [0, HASH_TABLE_SIZE - 1].
 */
unsigned int hash(char *str) {
    unsigned int h = 0U; 
    
    if (str == NULL) {
        return 0U;
    }

    while (*str != '\0') {
        h = (h * 31U) + (unsigned int)(*str);
        str++;
    }
    return (h % HASH_TABLE_SIZE); 
}

/* * Function:    insert
 * Description: Tạo một nút mới và thêm liên hệ vào đầu danh sách liên kết tại bucket tương ứng.
 * Parameter:   name - Tên liên hệ cần thêm.
 * phone - Số điện thoại tương ứng.
 * Return:      void
 */
void insert(char *name, char *phone) {
    unsigned int index = hash(name);
    Node* newNode = (Node*)malloc(sizeof(Node));
    
    /* Kiểm tra an toàn bộ nhớ (Ganssle Standard) */
    if (newNode == NULL) {
        printf("Lỗi hệ thống: Không thể cấp phát bộ nhớ.\n");
        return;
    }

    /* Sao chép dữ liệu an toàn tránh tràn bộ đệm */
    strncpy(newNode->name, name, MAX_NAME_LEN - 1);
    newNode->name[MAX_NAME_LEN - 1] = '\0';
    
    strncpy(newNode->phone, phone, MAX_PHONE_LEN - 1);
    newNode->phone[MAX_PHONE_LEN - 1] = '\0';

    /* Chèn vào đầu danh sách (O(1)) */
    newNode->next = buckets[index]; 
    buckets[index] = newNode;
    printf("Đã thêm thành công: %s\n", name);
}

/* * Function:    search
 * Description: Tìm kiếm số điện thoại dựa trên tên trong bảng băm.
 * Parameter:   name - Tên cần tìm kiếm.
 * Return:      void (In kết quả ra màn hình).
 */
void search(char *name) {
    unsigned int index = hash(name);
    Node* curr = buckets[index];

    while (curr != NULL) {
        if (strcmp(curr->name, name) == 0) {
            printf("Tìm thấy '%s': %s\n", name, curr->phone);
            return;
        }
        curr = curr->next;
    }
    printf("Kết quả: Không tìm thấy '%s' trong danh bạ.\n", name);
}

/* * Function:    delete_contact
 * Description: Xóa một nút liên hệ khỏi bảng băm và giải phóng bộ nhớ.
 * Parameter:   name - Tên liên hệ cần xóa.
 * Return:      void
 */
void delete_contact(char *name) {
    unsigned int index = hash(name);
    Node *curr = buckets[index];
    Node *prev = NULL;

    while (curr != NULL) {
        if (strcmp(curr->name, name) == 0) {
            if (prev == NULL) {
                buckets[index] = curr->next;
            } else {
                prev->next = curr->next;
            }
            free(curr);
            printf("Đã xóa liên hệ: %s\n", name);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    printf("Lỗi: Không tìm thấy '%s' để xóa.\n", name);
}

/* * Function:    print_all
 * Description: Hiển thị toàn bộ cấu trúc bảng băm hiện tại để kiểm tra xung đột.
 * Parameter:   none
 * Return:      void
 */
void print_all(void) {
    printf("\n--- CHI TIẾT BẢNG BĂM ---\n");
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        Node* curr = buckets[i];
        printf("Vị trí [%d]: ", i);
        while (curr != NULL) {
            printf("[%s] -> ", curr->name);
            curr = curr->next;
        }
        printf("NULL\n");
    }
}

/* * Function:    main
 * Description: Điểm bắt đầu chương trình, thực hiện các kịch bản kiểm thử theo yêu cầu.
 * Parameter:   none
 * Return:      0 khi kết thúc thành công.
 */
int main(void) {
    /* 1. Nhập thử 8 liên hệ tiếng Việt */
    printf("--- KHỞI TẠO DỮ LIỆU ---\n");
    insert("Nguyễn Văn An", "0912000001");
    insert("Trần Thị Bình", "0912000002");
    insert("Lê Văn Cường", "0912000003");
    insert("Phạm Minh Đức", "0912000004");
    insert("Hoàng Thu Hà", "0912000005");
    insert("Vũ Duy Hùng", "0912000006");
    insert("Đỗ Quang Lâm", "0912000007");
    insert("Phan Thanh Nam", "0912000008");

    /* 2. Kiểm thử tìm kiếm */
    printf("\n--- KIỂM THỬ TÌM KIẾM ---\n");
    search("Nguyễn Văn An");
    search("Vũ Duy Hùng");
    search("Trương Gia Bảo"); /* Không tồn tại */

    /* 3. Kiểm thử xóa và in lại bảng băm */
    printf("\n--- KIỂM THỬ XÓA ---\n");
    delete_contact("Trần Thị Bình");
    delete_contact("Lê Văn Cường");

    print_all();

    return 0;
}
