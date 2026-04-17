#include <stdio.h>
#include <string.h>

#define MAX_LINE 1000

/**
 * @Function: getline_custom
 * @Description: Đọc một dòng ký tự từ đầu vào chuẩn (stdin), lưu vào mảng s cho đến khi
 * gặp ký tự xuống dòng hoặc đạt giới hạn lim. Tự động thêm ký tự kết thúc chuỗi '\0'.
 * @Parameter: 
 * - s[]: Mảng char để lưu trữ chuỗi đọc được.
 * - lim: Số lượng ký tự tối đa mảng có thể chứa.
 * @Return: int - Số lượng ký tự thực tế đã đọc (độ dài chuỗi).
 */
int getline_custom(char s[], int lim) {
    int c, i = 0;
    // Đọc từng ký tự cho đến khi: hết giới hạn, gặp EOF hoặc gặp ký tự xuống dòng
    while (i < lim - 1 && (c = getchar()) != EOF && c != '\n') {
        s[i++] = c;
    }
    s[i] = '\0'; // Thêm ký tự kết thúc chuỗi
    return i;    // Trả về độ dài chuỗi đã đọc
}

/**
 * @Function: trim
 * @Description: Loại bỏ các ký tự khoảng trắng (space) và tab ('\t') ở phía cuối chuỗi.
 * Hàm duyệt ngược từ cuối chuỗi về đầu cho đến khi gặp ký tự hợp lệ đầu tiên.
 * @Parameter: 
 * - s[]: Chuỗi cần được cắt bỏ khoảng trắng ở cuối.
 * @Return: void
 */
void trim(char s[]) {
    int i = strlen(s) - 1; // Bắt đầu từ vị trí ký tự cuối cùng trước '\0'
    
    // Lùi dần chỉ số i nếu gặp khoảng trắng hoặc tab
    while (i >= 0 && (s[i] == ' ' || s[i] == '\t')) {
        i--;
    }
    
    // Đặt ký tự kết thúc chuỗi ngay sau ký tự hợp lệ cuối cùng tìm được
    s[i + 1] = '\0';
}

/**
 * @Function: main
 * @Description: Điểm bắt đầu của chương trình. Thực hiện vòng lặp đọc từng dòng,
 * gọi hàm trim để xử lý và chỉ in ra những dòng không bị trống sau khi đã trim.
 * @Parameter: Không có
 * @Return: int - Trả về 0 khi thực thi thành công.
 */
int main() {
    char line[MAX_LINE]; // Mảng đệm chứa dòng văn bản hiện tại

    // Tiếp tục đọc nếu độ dài dòng lớn hơn 0
    while (getline_custom(line, MAX_LINE) > 0) {
        trim(line); // Loại bỏ khoảng trắng thừa ở cuối dòng
        
        // Kiểm tra nếu dòng không trống (ký tự đầu tiên không phải là kết thúc chuỗi)
        if (line[0] != '\0') {
            printf("%s\n", line); // In dòng đã qua xử lý
        }
    }

    return 0;
}
