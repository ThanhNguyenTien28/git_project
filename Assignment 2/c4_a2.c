#include <stdio.h>
#include <stdlib.h> // Thư viện cho hàm abs()

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
        // Sử dụng abs() giúp hàm xử lý đúng cả khi n là số âm, là lấy trị tuyệt đối
        int digit = abs(n % b); 

        /* * Chuyển đổi giá trị số (digit) sang ký tự:
         * - Nếu digit < 10: Chuyển thành ký tự số '0'-'9'
         * - Nếu digit >= 10: Chuyển thành ký tự chữ 'A'-'Z' (ví dụ: 10 -> 'A', 11 -> 'B')
         */
        s[i++] = (digit < 10) ? (digit + '0') : (digit - 10 + 'A'); // 11 - 10 +'A' ='B'

    } while ((n /= b) != 0); // Tiếp tục chia nguyên n cho b cho đến khi n bằng 0

    // Nếu số ban đầu là số âm, thêm dấu '-' vào cuối chuỗi kết quả
    if (sign < 0) {
        s[i++] = '-'; 
    }

    // Kết thúc chuỗi bằng ký tự null
    s[i] = '\0'; 

    // Đảo ngược chuỗi để có kết quả đúng thứ tự từ trái sang phải
    reverse(s, 0, i - 1); 
}



int main() {
    int n, b;
    char s[64]; 

    printf("--- Chuong trinh chuyen doi he co so ---\n");
    printf("Nhap so nguyen n: ");
    if (scanf("%d", &n) != 1) {
        printf("Loi: Vui long nhap mot so nguyen!\n");
        return 1;
    }

    printf("Nhap he co so b (2-36): ");
    if (scanf("%d", &b) != 1 || b < 2 || b > 36) {
        printf("Loi: He co so phai nam trong khoang tu 2 den 36!\n");
        return 1;
    }

    // Goi ham chuyen doi
    itob(n, s, b);

    // In ket qua
    printf("Gia tri %d trong he co so %d la: %s\n", n, b, s);

    return 0;
}
