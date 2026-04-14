#include <stdio.h>

/**
 * @Function: main
 * @Description: Chương trình đếm tần suất xuất hiện của các ký tự ASCII trong luồng dữ liệu nhập vào.
 * Sau khi kết thúc nhập liệu (EOF), chương trình sẽ hiển thị một biểu đồ nằm ngang (histogram)
 * bằng các dấu sao (*), trong đó mỗi dấu sao đại diện cho một lần xuất hiện của ký tự đó.
 * @Parameter: Không có
 * @Return: int - Trả về 0 khi thực thi thành công.
 */
int main() {
    int c;              // Biến lưu trữ ký tự đọc vào từ getchar()
    int freq[128] = {0}; // Mảng lưu trữ số lần xuất hiện của 128 ký tự ASCII, khởi tạo tất cả bằng 0

    // Giai đoạn 1: Đọc dữ liệu và đếm tần suất
    // Vòng lặp chạy cho đến khi người dùng nhấn Ctrl+D (Linux) hoặc Ctrl+Z (Windows) để gửi tín hiệu EOF
    while ((c = getchar()) != EOF) {
        // Chỉ đếm các ký tự nằm trong bảng mã ASCII chuẩn (từ 0 đến 127)
        if (c < 128) {
            freq[c]++;
        }
    }

    // Giai đoạn 2: In biểu đồ tần suất
    // Duyệt qua toàn bộ mảng tần suất
    for (int i = 0; i < 128; i++) {
        // Chỉ xử lý và in những ký tự có xuất hiện ít nhất 1 lần
        if (freq[i] > 0) {
            
            // In ký tự đại diện (Nếu là ký tự không in được như ' ' hay '\n', nó sẽ hiển thị khoảng trắng hoặc xuống dòng)
            printf("%c: ", i);
            
            // In số lượng dấu sao tương ứng với số lần xuất hiện (tần suất)
            for (int j = 0; j < freq[i]; j++) {
                printf("*");
            }
            
            // Xuống dòng để bắt đầu hàng cho ký tự tiếp theo
            printf("\n");
        }
    }

    return 0;
}


