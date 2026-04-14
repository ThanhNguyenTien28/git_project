#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100

// Cấu trúc dữ liệu bệnh nhân
typedef struct {
    char name[50];
    int priority; // Độ ưu tiên (Ví dụ: 5 là cấp cứu, 1 là khám thường)
} Patient;

Patient heap[MAX_SIZE]; // Mảng lưu trữ các nút của cây Heap
int size = 0;           // Số lượng bệnh nhân hiện có

// Hàm hoán đổi vị trí hai phần tử
void swap(Patient *a, Patient *b) {
    Patient temp = *a;
    *a = *b;
    *b = temp;
}

// Thêm bệnh nhân mới và vun đống ngược lên (Heapify-up)
void push(Patient p) {
    if (size >= MAX_SIZE) return;

    heap[size] = p; // Đưa vào cuối hàng đợi
    int i = size;
    size++;

    // So sánh với nút cha (vị trí (i-1)/2). Nếu con > cha thì đổi chỗ
    while (i > 0 && heap[i].priority > heap[(i - 1) / 2].priority) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2; // Tiếp tục kiểm tra nút cha ở tầng trên
    }
}

// Gọi bệnh nhân ưu tiên nhất khám và vun đống xuống (Heapify-down)
void pop() {
    if (size <= 0) return;

    // Người ở vị trí gốc (heap[0]) luôn có ưu tiên cao nhất
    printf("Moi benh nhan: %s (Muc uu tien: %d)\n", heap[0].name, heap[0].priority);

    // Lấy phần tử cuối cùng đưa lên gốc để thay thế
    heap[0] = heap[size - 1];
    size--;

    // Duy trì tính chất Max-Heap từ gốc xuống dưới
    int i = 0;
    while (1) {
        int largest = i;
        int left = 2 * i + 1;  // Chỉ số con trái
        int right = 2 * i + 2; // Chỉ số con phải

        // Tìm xem trong 3 nút (cha, con trái, con phải) nút nào có ưu tiên lớn nhất
        if (left < size && heap[left].priority > heap[largest].priority)
            largest = left;
        if (right < size && heap[right].priority > heap[largest].priority)
            largest = right;

        // Nếu cha đã là người có ưu tiên lớn nhất, kết thúc vun đống
        if (largest == i) break;

        swap(&heap[i], &heap[largest]);
        i = largest; // Tiếp tục kiểm tra tại vị trí mới sau khi đổi chỗ
    }
}

// Xem người đứng đầu hàng đợi
void peek() {
    if (size > 0) {
        printf("Benh nhan tiep theo: %s\n", heap[0].name);
    }
}
int main() {
    // 1. Nhập vào ít nhất 5 bệnh nhân với các mức ưu tiên khác nhau
    Patient p1 = {"Nguyen Van A", 3}; // Uu tien thuong
    Patient p2 = {"Tran Thi B", 5};   // Cap cuu (Cao nhat)
    Patient p3 = {"Le Van C", 1};     // Kham nhe
    Patient p4 = {"Pham Van D", 4};   // Uu tien cao
    Patient p5 = {"Hoang Thi E", 2};   // Kham trung binh

    printf("--- THEM BENH NHAN VAO HANG DOI ---\n");
    push(p1); printf("Da them A, nguoi dau hang: %s\n", heap[0].name);
    push(p2); printf("Da them B, nguoi dau hang: %s\n", heap[0].name);
    push(p3); printf("Da them C, nguoi dau hang: %s\n", heap[0].name);
    push(p4); printf("Da them D, nguoi dau hang: %s\n", heap[0].name);
    push(p5); printf("Da them E, nguoi dau hang: %s\n", heap[0].name);

    printf("\n--- THU TU GOI KHAM (UU TIEN CAO DEN THAP) ---\n");
    // 2. Lay lan luot tung benh nhan ra khoi hang doi
    while (size > 0) {
        pop();
    }

    return 0;
}
