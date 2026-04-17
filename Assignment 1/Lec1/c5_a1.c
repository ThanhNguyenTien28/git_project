#include <stdio.h>

/**
 * @Function: main
 * @Description: Đọc dữ liệu từ đầu vào và sao chép sang đầu ra. 
 * Trong quá trình sao chép, chương trình sẽ thay thế các ký tự không nhìn thấy 
 * (Tab, Backspace) và dấu gạch chéo ngược thành các chuỗi ký tự hiển thị được 
 * (ví dụ: '\t' trở thành "\t").
 * @Parameter: Không có
 * @Return: int - Trả về 0 khi kết thúc chương trình thành công.
 */
int main() {
    int c; // Biến lưu trữ ký tự đọc được từ getchar()

    // Vòng lặp đọc từng ký tự cho đến khi kết thúc luồng dữ liệu (EOF)
    while ((c = getchar()) != EOF) {
        
        // Kiểm tra nếu là ký tự Tab
        if (c == '\t') {
            printf("\\t"); // In ra chuỗi văn bản "\t" (cần 2 dấu \ để in được 1 dấu \)
        } 
        // Kiểm tra nếu là ký tự Backspace
        else if (c == '\b') {
            printf("\\b"); // In ra chuỗi văn bản "\b"
        } 
        // Kiểm tra nếu là ký tự Backslash (dấu gạch chéo ngược \)
        else if (c == '\\') {
            printf("\\\\"); // In ra chuỗi văn bản "\\"
        } 
        // Đối với các ký tự bình thường khác
        else {
            putchar(c); // In ký tự đó ra bình thường
        }
    }

    return 0;
}


