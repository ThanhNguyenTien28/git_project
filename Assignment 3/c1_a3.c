#include <stdio.h>
#include <string.h>
#include <ctype.h>

/**
 * @Function: main
 * @Description: Chương trình thực hiện chuyển đổi văn bản từ đầu vào chuẩn (stdin) 
 * thành chữ hoa hoặc chữ thường tùy thuộc vào tên của tệp thực thi.
 * - Nếu tên file chứa "lower": Chuyển toàn bộ thành chữ thường.
 * - Nếu tên file chứa "upper": Chuyển toàn bộ thành chữ hoa.
 * @Parameter: 
 * - argc: Số lượng tham số dòng lệnh (bao gồm cả tên chương trình).
 * - argv: Mảng các chuỗi ký tự chứa các tham số dòng lệnh. 
 * argv[0] lưu tên của chương trình đang chạy.
 * @Return: int - Trả về 0 nếu thành công, 1 nếu gặp lỗi tham số.
 */
int main(int argc, char *argv[]) {
    int c; // Biến lưu trữ từng ký tự đọc vào

    // Kiểm tra số lượng tham số truyền vào (đảm bảo ít nhất có tên chương trình)
    if (argc < 1) {
        return 1;
    }

    /* * Kiểm tra nội dung của argv[1] 
     * Hàm strstr tìm kiếm sự xuất hiện của chuỗi con "lower" trong argv[1].
     */
    if (strstr(argv[1], "lower") != NULL) {
        // Vòng lặp đọc từng ký tự cho đến khi gặp EOF
        while ((c = getchar()) != EOF) {
            // Sử dụng tolower() từ thư viện ctype.h để chuyển đổi
            putchar(tolower(c)); 
        }
    } 
    /* * Kiểm tra nếu argv[1] chứa chuỗi con "upper".
     */
    else if (strstr(argv[1], "upper") != NULL) {
        while ((c = getchar()) != EOF) {
            // Sử dụng toupper() từ thư viện ctype.h để chuyển đổi
            putchar(toupper(c)); 
        }
    } 
    /* * Trường hợp tên chương trình không chứa từ khóa hợp lệ.
     */
    else {
        printf("Error: Run program as 'lower' or 'upper'\n");
    }

    return 0;
}
