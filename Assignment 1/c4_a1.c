#include <stdio.h>

/**
 * @Function: main
 * @Description: Đọc các ký tự từ đầu vào chuẩn (stdin) và in ra đầu ra chuẩn (stdout), 
 * đồng thời thu gọn các chuỗi khoảng trắng (space) liên tiếp thành một khoảng trắng duy nhất.
 * @Parameter: Không có
 * @Return: int - Trả về 0 khi chương trình thực thi và kết thúc thành công.
 */
int main() {
    int c;          // Biến lưu trữ ký tự hiện tại vừa được đọc vào
    int prev = EOF; // Biến lưu trữ ký tự ngay trước đó, khởi tạo là EOF để tránh rác bộ nhớ

    // Đọc liên tục từng ký tự từ bàn phím/file cho đến khi gặp End-Of-File (EOF)
    while ((c = getchar()) != EOF) {
        
        // Nếu ký tự hiện tại là một khoảng trắng
        if (c == ' ') {
            // Kiểm tra xem ký tự trước đó có phải khoảng trắng không
            // Chỉ in ra khoảng trắng nếu ký tự trước đó KHÔNG phải là khoảng trắng
            if (prev != ' ') {
                putchar(c);
            }
        } 
        // Nếu ký tự hiện tại không phải là khoảng trắng
        else {
            putchar(c); // In ra bình thường
        }
        
        // Cập nhật biến prev bằng ký tự hiện tại để chuẩn bị cho vòng lặp tiếp theo
        prev = c;
    }

    return 0; // Báo hiệu chương trình kết thúc không có lỗi
}


