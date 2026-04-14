#include <stdio.h>

/**
 * @Function: expand
 * @Description: Mở rộng các biểu thức viết tắt như 'a-z', 'A-Z', '0-9' từ chuỗi s1 
 * thành chuỗi đầy đủ tương ứng trong s2 (ví dụ: 'a-d' sẽ thành 'abcd').
 * Hàm có khả năng xử lý các chuỗi hỗn hợp như 'a-b-c' hoặc 'a-z0-9'.
 * @Parameter: 
 * - s1[]: Chuỗi nguồn chứa các biểu thức viết tắt.
 * - s2[]: Chuỗi đích để lưu trữ kết quả sau khi đã mở rộng.
 * @Return: void
 */
void expand(char s1[], char s2[]) {
    int i = 0; // Chỉ số chạy cho chuỗi nguồn s1
    int j = 0; // Chỉ số chạy cho chuỗi đích s2
    char c;    // Biến tạm lưu ký tự hiện tại

    // Duyệt qua từng ký tự của chuỗi s1 cho đến khi gặp ký tự kết thúc '\0'
    while ((c = s1[i++]) != '\0') { 
        
        /* * Kiểm tra xem ký tự tiếp theo có phải là dấu gạch ngang '-' hay không 
         * và ký tự sau dấu gạch ngang có lớn hơn hoặc bằng ký tự hiện tại (theo mã ASCII) hay không.
         */
        if (s1[i] == '-' && s1[i+1] >= c) { 
            
            i++; // Bỏ qua dấu '-' trong chuỗi nguồn
            
            /* * Vòng lặp này thực hiện việc "điền đầy" các ký tự còn thiếu.
             * Nó sẽ chạy từ ký tự bắt đầu (c) đến trước ký tự kết thúc của dải (s1[i]).
             */
            while (c < s1[i]) { 
                s2[j++] = c++; 
            }
            // Ký tự cuối của dải (s1[i]) sẽ được xử lý ở vòng lặp ngoài hoặc lần lặp kế tiếp
        } 
        else {
            // Nếu không phải định dạng viết tắt, chỉ cần chép ký tự sang chuỗi s2
            s2[j++] = c; 
        }
    }
    
    // Đóng chuỗi đích bằng ký tự null
    s2[j] = '\0'; 
}
