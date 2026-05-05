#include <stdio.h>
#include <ctype.h>

/**
 * @Function: htoi
 * @Description: Chuyển đổi một chuỗi ký tự biểu diễn số hệ thập lục phân (Hexadecimal) 
 * sang giá trị số nguyên (Integer) tương ứng. Hàm hỗ trợ các chữ cái từ a-f, A-F 
 * và có thể xử lý cả tiền tố "0x" hoặc "0X".
 * @Parameter: 
 * - s[]: Chuỗi ký tự chứa số Hex cần chuyển đổi.
 * @Return: int - Giá trị số nguyên sau khi chuyển đổi. Trả về kết quả tính toán được 
 * cho đến khi gặp ký tự không hợp lệ.
 */
int htoi(char s[]) {
    int i = 0;
    int n = 0; // Biến tích lũy giá trị kết quả
    
    // 1. Xử lý tiền tố: Bỏ qua "0x" hoặc "0X" nếu có ở đầu chuỗi
    if (s[i] == '0') {
        i++;
        if (s[i] == 'x' || s[i] == 'X') {
            i++;
        }
    }
    
    // 2. Vòng lặp duyệt qua từng ký tự của chuỗi
    for (; s[i] != '\0'; i++) {
        int digit;
        
        // Chuyển đổi ký tự hiện tại thành giá trị số tương ứng (0-15)
        if (isdigit(s[i])) {
            // Nếu là ký tự số '0'-'9'
            digit = s[i] - '0';
        } else if (s[i] >= 'a' && s[i] <= 'f') {
            // Nếu là chữ cái thường 'a'-'f'
            digit = s[i] - 'a' + 10;
        } else if (s[i] >= 'A' && s[i] <= 'F') {
            // Nếu là chữ cái hoa 'A'-'F'
            digit = s[i] - 'A' + 10; // VD: 'B' - 'A' = 1
        } else {
            // Gặp ký tự không thuộc hệ Hex thì dừng lại
            break; 
        }
        
        // 3. Công thức chuyển đổi hệ cơ số: n = n * cơ số + chữ số mới
        // VD: 123 = ((1 x 16) + 2) X 16 + 3
        n = 16 * n + digit;
    }
    
    return n;
}

int main(void) { 
    
    
    char test1[] = "0x1A";  
    char test2[] = "F3";    
    char test3[] = "0Xdead";

    
    printf("Hex: %s -> Decimal: %d\n", test1, htoi(test1));
    printf("Hex: %s -> Decimal: %d\n", test2, htoi(test2));
    printf("Hex: %s -> Decimal: %d\n", test3, htoi(test3));

    return 0; 
}
