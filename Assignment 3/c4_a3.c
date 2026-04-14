#include <stdio.h>

/**
 * @Function: shift_element
 * @Description: Thực hiện việc "dịch chuyển" các phần tử lớn hơn giá trị cần chèn sang bên phải
 * và đặt phần tử đó vào đúng vị trí để duy trì thứ tự tăng dần. Đây là hàm lõi của Insertion Sort.
 * @Parameter: 
 * - pElement: Con trỏ trỏ tới phần tử hiện tại đang cần tìm vị trí thích hợp để chèn.
 * - arr: Con trỏ trỏ tới phần tử đầu tiên của mảng (để biết giới hạn dừng).
 * @Return: void
 */
void shift_element(int *pElement, int *arr) {
    int value = *pElement; // Lưu giá trị của phần tử cần chèn vào biến tạm
    
    /* * Vòng lặp chạy ngược về phía đầu mảng:
     * - pElement > arr: Đảm bảo không truy cập ra ngoài vùng nhớ phía trước mảng.
     * - *(pElement - 1) > value: Nếu phần tử bên trái vẫn lớn hơn giá trị cần chèn.
     */
    while (pElement > arr && *(pElement - 1) > value) {
        *pElement = *(pElement - 1); // Dịch chuyển phần tử lớn hơn sang vị trí bên phải
        pElement--;                  // Di chuyển con trỏ lùi về phía đầu mảng
    }
    
    *pElement = value; // Chèn giá trị ban đầu vào vị trí trống sau khi đã dịch chuyển xong
}

/**
 * @Function: insertion_sort
 * @Description: Thuật toán sắp xếp chèn sử dụng con trỏ. Chia mảng thành hai phần: 
 * phần đã sắp xếp và phần chưa sắp xếp. Lần lượt lấy từng phần tử từ phần chưa 
 * sắp xếp chèn vào đúng vị trí trong phần đã sắp xếp.
 * @Parameter: 
 * - arr: Con trỏ trỏ đến mảng cần sắp xếp.
 * - len: Số lượng phần tử của mảng.
 * @Return: void
 */
void insertion_sort(int *arr, int len) {
    // Bắt đầu từ phần tử thứ 2 (địa chỉ arr + 1) vì phần tử đầu tiên coi như đã được sắp xếp
    for (int *p = arr + 1; p < arr + len; p++) {
        
        // Nếu phần tử hiện tại nhỏ hơn phần tử ngay trước nó, tiến hành dịch chuyển
        if (*p < *(p - 1)) {
            shift_element(p, arr); 
        }
    }
}

/**
 * @Function: main
 * @Description: Điểm bắt đầu chương trình. Khởi tạo một mảng số nguyên mẫu, 
 * thực hiện sắp xếp và in kết quả ra màn hình.
 * @Parameter: Không có
 * @Return: int - Trả về 0 khi thực thi thành công.
 */
int main() {
    int arr[] = {12, 11, 13, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]); // Tính số lượng phần tử mảng bằng toán tử sizeof

    insertion_sort(arr, n);

    // In mảng sau khi đã được sắp xếp
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
