#include <stdio.h>

/**
 * @Function: main
 * @Description: Đọc văn bản từ đầu vào tiêu chuẩn và in ra đầu ra tiêu chuẩn, 
 * nhưng thay thế mỗi chuỗi gồm một hoặc nhiều khoảng trắng bằng một khoảng trắng duy nhất.
 * Thuật toán sử dụng một biến để ghi nhớ ký tự ngay trước đó (last_c).
 * @Parameter: Không có
 * @Return: int - Trả về 0 sau khi hoàn thành việc xử lý luồng dữ liệu.
 */
int main() {
    int c;              // Biến lưu trữ ký tự hiện tại vừa đọc
    int last_c = EOF;   // Biến lưu trữ ký tự ngay trước đó, khởi tạo bằng EOF
    
    // Vòng lặp đọc từng ký tự từ đầu vào cho đến khi kết thúc (EOF)
    while ((c = getchar()) != EOF) {
        
        /**
         * Logic điều kiện: 
         * Chỉ in ký tự hiện tại (c) nếu:
         * 1. c không phải là khoảng trắng.
         * 2. HOẶC ký tự trước đó (last_c) không phải là khoảng trắng.
         * Điều này đảm bảo nếu có nhiều khoảng trắng liên tiếp, chỉ ký tự đầu tiên được in.
         */
        if (c != ' ' || last_c != ' ') {
            putchar(c);
        }
        
        // Cập nhật ký tự vừa xử lý vào last_c để phục vụ lần lặp sau
        last_c = c;
    }
    
    return 0;
}
