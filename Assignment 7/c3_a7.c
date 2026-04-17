#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * --- CẤU HÌNH HỆ THỐNG ---
 * MAX_SIZE: Giới hạn số lượng phần tử tối đa trong hàng đợi.
 */
#define MAX_SIZE 100

/**
 * @Description: Định nghĩa cấu trúc dữ liệu Bệnh nhân.
 * Trong Priority Queue, 'priority' đóng vai trò là "khóa" (key) để sắp xếp.
 */
typedef struct {
    char name[50];
    int priority; // Mức độ ưu tiên: Giá trị càng lớn càng được khám trước
} Patient;

/* Mảng lưu trữ các nút của cây Heap (Cài đặt Heap bằng mảng) */
Patient heap[MAX_SIZE]; 
int size = 0;           // Số lượng bệnh nhân hiện tại trong hàng đợi

/**
 * @Function: swap
 * @Description: Hoán đổi vị trí của hai bệnh nhân trong mảng heap.
 */
void swap(Patient *a, Patient *b) {
    Patient temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * @Function: push (Insert)
 * @Description: Thêm một bệnh nhân mới vào cuối hàng đợi và thực hiện 
 * thao tác vun đống ngược lên (Heapify-up) để duy trì tính chất Max-Heap.
 * Độ phức tạp: O(log n).
 * @Parameter: p - Cấu trúc dữ liệu bệnh nhân mới.
 */
void push(Patient p) {
    if (size >= MAX_SIZE) return;

    heap[size] = p; // Đưa vào vị trí cuối cùng của cây
    int i = size;
    size++;

    // Heapify-up: So sánh với cha (i-1)/2, nếu con > cha thì đổi chỗ
    while (i > 0 && heap[i].priority > heap[(i - 1) / 2].priority) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2; 
    }
}

/**
 * @Function: pop (Extract-Max)
 * @Description: Lấy ra bệnh nhân có độ ưu tiên cao nhất (nằm ở gốc heap[0]).
 * Sau đó đưa phần tử cuối lên gốc và thực hiện vun đống xuống (Heapify-down).
 * Độ phức tạp: O(log n).
 */
void pop() {
    if (size <= 0) return;

    // Phần tử heap[0] luôn là phần tử có độ ưu tiên lớn nhất trong Max-Heap
    printf("Moi benh nhan: %s (Muc uu tien: %d)\n", heap[0].name, heap[0].priority);

    // Thay thế gốc bằng phần tử cuối cùng
    heap[0] = heap[size - 1];
    size--;

    // Heapify-down: Duy trì tính chất Max-Heap từ gốc xuống dưới
    int i = 0;
    while (1) {
        int largest = i;
        int left = 2 * i + 1;  // Công thức tìm con trái
        int right = 2 * i + 2; // Công thức tìm con phải

        // So sánh nút hiện tại với 2 nút con để tìm nút có ưu tiên lớn nhất
        if (left < size && heap[left].priority > heap[largest].priority)
            largest = left;
        if (right < size && heap[right].priority > heap[largest].priority)
            largest = right;

        // Nếu nút cha đã lớn hơn cả 2 con thì dừng lại
        if (largest == i) break;

        swap(&heap[i], &heap[largest]);
        i = largest; // Tiếp tục kiểm tra tại vị trí mới
    }
}

/**
 * @Function: peek
 * @Description: Xem thông tin bệnh nhân ưu tiên nhất mà không xóa khỏi hàng đợi.
 */
void peek() {
    if (size > 0) {
        printf("Benh nhan tiep theo dang cho: %s\n", heap[0].name);
    }
}

/**
 * @Function: main
 * @Description: Mô phỏng quy trình nhập viện và gọi khám dựa trên độ ưu tiên.
 */
int main() {
    // Khởi tạo danh sách bệnh nhân giả lập
    Patient p1 = {"Nguyen Van A", 3}; 
    Patient p2 = {"Tran Thi B", 5};   // Ưu tiên cao nhất (Cấp cứu)
    Patient p3 = {"Le Van C", 1};     
    Patient p4 = {"Pham Van D", 4};   
    Patient p5 = {"Hoang Thi E", 2};  

    printf("--- THEM BENH NHAN VAO HANG DOI (PUSH) ---\n");
    push(p1); printf("Nguoi uu tien nhat hien tai: %s\n", heap[0].name);
    push(p2); printf("Nguoi uu tien nhat hien tai: %s\n", heap[0].name);
    push(p3); 
    push(p4); 
    push(p5); 

    printf("\n--- THU TU GOI KHAM (POP) ---\n");
    // Lấy lần lượt từng người theo độ ưu tiên từ cao xuống thấp
    while (size > 0) {
        pop();
    }

    return 0;
}
