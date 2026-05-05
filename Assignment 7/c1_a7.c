#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * --- CẤU HÌNH HỆ THỐNG ---
 * HASH_TABLE_SIZE: Số lượng bucket để quản lý dữ liệu.
 */
#define HASH_TABLE_SIZE 10 
#define MAX_NAME_LEN    50
#define MAX_PHONE_LEN   15

/**
 * @Description: Định nghĩa cấu trúc của một nút (Node) trong danh sách liên kết.
 * Được sử dụng để lưu trữ thông tin liên hệ và xử lý xung đột băm (collision).
 */
typedef struct Node {
    char name[MAX_NAME_LEN];    // Tên liên hệ
    char phone[MAX_PHONE_LEN];  // Số điện thoại
    struct Node* next;          // Con trỏ trỏ đến nút tiếp theo trong cùng một bucket
} Node;

/* Khởi tạo bảng băm toàn cục gồm các danh sách liên kết rỗng */
Node* buckets[HASH_TABLE_SIZE] = {NULL};

/**
 * @Function: hash
 * @Description: Thuật toán băm đa thức. Chuyển đổi tên liên hệ thành một chỉ số mảng.
 * @Parameter: str - Chuỗi ký tự (tên) cần băm.
 * @Return: unsigned int - Chỉ số index từ 0 đến HASH_TABLE_SIZE - 1.
 */
unsigned int hash(char *str) {
    unsigned int h = 0U; 
    
    if (str == NULL) {
        return 0U;
    }

    while (*str != '\0') {
        // Sử dụng số nguyên tố 31 để giảm thiểu xung đột băm
        h = (h * 31U) + (unsigned int)(*str);
        str++;
    }
    return (h % HASH_TABLE_SIZE); 
}

/**
 * @Function: insert
 * @Description: Thêm một liên hệ mới vào bảng băm. 
 * Xử lý xung đột bằng cách chèn nút mới vào đầu danh sách liên kết (O(1)).
 * @Parameter: name - Tên liên hệ.
 * @Parameter: phone - Số điện thoại.
 * @Return: void
 */
void insert(char *name, char *phone) {
    unsigned int index = hash(name);
    Node* newNode = (Node*)malloc(sizeof(Node));
    
    if (newNode == NULL) {
        printf("Lỗi hệ thống: Không thể cấp phát bộ nhớ.\n");
        return;
    }

    /* Sao chép dữ liệu và đảm bảo có ký tự kết thúc chuỗi \0 */
    strncpy(newNode->name, name, MAX_NAME_LEN - 1);
    newNode->name[MAX_NAME_LEN - 1] = '\0';
    
    strncpy(newNode->phone, phone, MAX_PHONE_LEN - 1);
    newNode->phone[MAX_PHONE_LEN - 1] = '\0';

// Kỹ thuật chèn vào đầu linked list: nút mới trỏ tới nút cũ, bucket trỏ tới nút mới
    newNode->next = buckets[index]; //Nối nút mới với linked list
    buckets[index] = newNode; //Đưa nút mới thêm vào thành đầu danh sách linked list
    printf("Đã thêm thành công: %s\n", name);
}

/**
 * @Function: search
 * @Description: Tìm kiếm liên hệ theo tên. Hỗ trợ in ra tất cả các kết quả nếu trùng tên.
 * @Parameter: name - Tên cần tìm.
 * @Return: void
 */
void search(char *name) {
    unsigned int index = hash(name);
    Node* curr = buckets[index];
    int found = 0;

    while (curr != NULL) {
        if (strcmp(curr->name, name) == 0) {
            printf("Tìm thấy '%s': %s\n", name, curr->phone);
            found = 1;
        }
        curr = curr->next;
    }
    if (!found) {
        printf("Kết quả: Không tìm thấy '%s' trong danh bạ.\n", name);
    }
}

/**
 * @Function: delete
 * @Description: Xóa TẤT CẢ các liên hệ có tên trùng khớp và giải phóng bộ nhớ (free).
 * @Parameter: name - Tên cần xóa.
 * @Return: void
 */
void delete(char *name) {
    unsigned int index = hash(name);
    Node *curr = buckets[index];
    Node *prev = NULL;
    int count = 0;

    while (curr != NULL) {
        if (strcmp(curr->name, name) == 0) {
            Node *temp = curr; // Lưu tạm nút cần xóa để giải phóng sau
            if (prev == NULL) {   // Node cần xóa nằm ngay đầu bucket
              
                buckets[index] = curr->next; //Nối nút sau nút hiện tại lên đầu danh sách
                curr = buckets[index]; 
            } else {      // Node cần xóa nằm ở giữa hoặc cuối danh sách
            
           // Cho prev->next bỏ qua nút curr và trỏ thẳng tới curr->next 
                prev->next = curr->next;
                curr = curr->next;
            }
            free(temp); 
            count++;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
    if (count > 0) {
        printf("Hệ thống: Đã xóa %d liên hệ tên '%s'.\n", count, name);
    } else {
        printf("Lỗi: Không tìm thấy '%s' để xóa.\n", name);
    }
}

/**
 * @Function: print_all
 * @Description: In toàn bộ cấu trúc bảng băm để quan sát các bucket và xung đột.
 * @Return: void
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

/**
 * @Function: free_table
 * @Description: Giải phóng toàn bộ bộ nhớ của bảng băm trước khi thoát chương trình.
 * @Return: void
 */
void free_table(void) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        Node* curr = buckets[i];
        while (curr != NULL) {
            Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
        buckets[i] = NULL;
    }
}

/**
 * @Function: main
 * @Description: Thực hiện kịch bản kiểm thử: Thêm ít nhất 8 liên hệ, tìm kiếm và xóa.
 */
int main(void) {
    printf("--- KHỞI TẠO DỮ LIỆU ---\n");
    insert("Thanh", "0912000001");
    insert("An", "0912000002");
    insert("Binh", "0912000003");
    insert("Thanh", "0912000999"); // Test trùng tên
    insert("Duc", "0912000004");
    insert("Ha", "0912000005");
    insert("Hung", "0912000006");
    insert("Lam", "0912000007");

    printf("\n--- KIỂM THỬ TÌM KIẾM ---\n");
    search("Thanh");
    search("Minh");
    search("Duc");	

    printf("\n--- KIỂM THỬ XÓA ---\n");
    delete("An");
    delete("Thanh"); // Xóa cả 2 người tên Thanh
    
    print_all();

    free_table();
    return 0;
}

