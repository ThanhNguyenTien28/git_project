#include <stdio.h>

/**
 * @Function: main
 * @Description: Chương trình thực hiện đếm số lượng khoảng trắng (blanks), 
 * ký tự Tab (\t) và ký tự xuống dòng (\n) từ dữ liệu nhập vào qua stdin.
 * Chương trình tiếp tục chạy cho đến khi nhận được tín hiệu kết thúc tệp (EOF).
 * @Parameter: Không có
 * @Return: int - Trả về 0 sau khi in kết quả thống kê thành công.
 */
int main() {
    int c; // Biến lưu trữ mã ASCII của ký tự đọc được
    int blanks = 0, tabs = 0, newlines = 0; // Các biến đếm khởi tạo bằng 0
    
    // Đọc từng ký tự cho đến khi gặp EOF (Ctrl+D trên Linux/Mac, Ctrl+Z trên Windows)
    while ((c = getchar()) != EOF) {
        
        // Kiểm tra nếu là ký tự khoảng trắng (Space)
        if (c == ' ') {
            ++blanks;
        } 
        // Kiểm tra nếu là ký tự Tab
        else if (c == '\t') {
            ++tabs;
        } 
        // Kiểm tra nếu là ký tự xuống dòng
        else if (c == '\n') {
            ++newlines;
        }
    }

    // In kết quả thống kê ra màn hình đầu ra tiêu chuẩn
    printf("Blanks: %d\nTabs: %d\nNewlines: %d\n", blanks, tabs, newlines);

    return 0;
}
