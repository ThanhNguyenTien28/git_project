#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * @Function: reverse
 * @Description: Đảo ngược thứ tự các ký tự trong một mảng (chuỗi) từ vị trí i đến vị trí j.
 * Thường được dùng để chỉnh lại thứ tự chuỗi sau khi trích xuất các chữ số từ phải sang trái.
 * @Parameter: 
 * - s[]: Mảng ký tự cần đảo ngược.
 * - i: Chỉ số bắt đầu (thường là 0).
 * - j: Chỉ số kết thúc.
 * @Return: void
 */
void reverse(char s[], int i, int j) {
    int c;
    while (i < j) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
        i++; 
        j--;
    }
}

/**
 * @Function: itoa_custom
 * @Description: Chuyển đổi một số nguyên (int) thành một chuỗi ký tự (ASCII).
 * Hàm này xử lý tốt cả số dương, số âm và số 0, đặc biệt là giá trị âm nhỏ nhất.
 * @Parameter: 
 * - n: Số nguyên cần chuyển đổi.
 * - s[]: Mảng ký tự dùng để chứa chuỗi kết quả đầu ra.
 * @Return: void
 */
void itoa_custom(int n, char s[]) {
    int i;
    // Sử dụng kiểu long nl để tránh lỗi tràn số khi thực hiện nl = -nl 
    // với giá trị âm lớn nhất của kiểu int (INT_MIN).
    long nl = n; 
    
    // Lưu lại dấu của số ban đầu
    int sign = (nl < 0); 
    if (sign) {
        nl = -nl; // Chuyển số âm thành số dương để trích xuất chữ số
    }

    i = 0;
    // Sử dụng vòng lặp do-while để đảm bảo số 0 vẫn được xử lý (sinh ra ký tự '0')
    do {
        // Trích xuất chữ số cuối cùng bằng phép chia lấy dư (%) 
        // và cộng với '0' để chuyển sang ký tự ASCII tương ứng.
        s[i++] = nl % 10 + '0'; 
    } while ((nl /= 10) > 0); // Chia nguyên cho 10 để loại bỏ chữ số đã xử lý

    // Nếu ban đầu là số âm, thêm dấu '-' vào cuối chuỗi
    if (sign) {
        s[i++] = '-';
    }
    
    // Thêm ký tự kết thúc chuỗi
    s[i] = '\0'; 
    
    // Vì các chữ số được lấy từ hàng đơn vị trở lên nên chuỗi đang bị ngược.
    // Cần gọi hàm reverse để đưa về đúng thứ tự đọc (từ trái sang phải).
    reverse(s, 0, i - 1); 
}
