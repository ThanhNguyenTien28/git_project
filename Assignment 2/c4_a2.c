#include <stdio.h>
#include <stdlib.h> // Thư viện cho hàm abs()

/**
 * @Function: itob
 * @Description: Chuyển đổi số nguyên n thành chuỗi ký tự s biểu diễn dưới hệ cơ số b.
 * Hàm xử lý được các hệ cơ số từ 2 đến 36. Đối với các hệ cơ số lớn hơn 10,
 * hàm sử dụng các chữ cái viết hoa 'A', 'B', 'C',... để biểu diễn giá trị 10, 11, 12,...
 * @Parameter: 
 * - n: Số nguyên cần chuyển đổi.
 * - s[]: Mảng ký tự để lưu trữ chuỗi kết quả.
 * - b: Hệ cơ số muốn chuyển đổi sang (ví dụ: 2, 8, 10, 16).
 * @Return: void
 */
void itob(int n, char s[], int b) {
    int i = 0;
    int sign = n; // Lưu lại giá trị gốc của n để kiểm tra dấu âm/dương sau này

    // Sử dụng vòng lặp do-while để đảm bảo số 0 vẫn được xử lý ít nhất một lần
    do {
        // Lấy giá trị tuyệt đối của phần dư khi chia cho cơ số b
        // Sử dụng abs() giúp hàm xử lý đúng cả khi n là số âm
        int digit = abs(n % b); 

        /* * Chuyển đổi giá trị số (digit) sang ký tự:
         * - Nếu digit < 10: Chuyển thành ký tự số '0'-'9'
         * - Nếu digit >= 10: Chuyển thành ký tự chữ 'A'-'Z' (ví dụ: 10 -> 'A', 11 -> 'B')
         */
        s[i++] = (digit < 10) ? (digit + '0') : (digit - 10 + 'A'); 

    } while ((n /= b) != 0); // Tiếp tục chia nguyên n cho b cho đến khi n bằng 0

    // Nếu số ban đầu là số âm, thêm dấu '-' vào cuối chuỗi kết quả
    if (sign < 0) {
        s[i++] = '-'; 
    }

    // Kết thúc chuỗi bằng ký tự null
    s[i] = '\0'; 

    // Đảo ngược chuỗi để có kết quả đúng thứ tự từ trái sang phải
    // (Lưu ý: Cần định nghĩa hoặc include hàm reverse của bạn ở trên)
    reverse(s, 0, i - 1); 
}
