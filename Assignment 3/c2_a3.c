#include <stdio.h>
#include <string.h>

#define MAX_LINE_LEN 1000 // Độ dài tối đa của một dòng có thể đọc được

/**
 * @Function: main
 * @Description: So sánh nội dung của hai tệp tin theo từng dòng.
 * Nếu phát hiện sự khác biệt, chương trình sẽ in ra số dòng và nội dung khác biệt 
 * của cả hai tệp, sau đó dừng lại. Nếu hai tệp giống hệt nhau, chương trình sẽ thông báo.
 * @Parameter: 
 * - argc: Số lượng tham số (kỳ vọng là 3: tên chương trình, file1, file2).
 * - argv: Mảng chứa tên tệp thực thi và đường dẫn tới hai tệp cần so sánh.
 * @Return: int - Trả về 0 nếu thực thi bình thường, 1 nếu có lỗi (thiếu tham số hoặc không mở được file).
 */
int main(int argc, char *argv[]) {
    FILE *f1, *f2;                    // Con trỏ quản lý hai tệp tin
    char line1[MAX_LINE_LEN], line2[MAX_LINE_LEN]; // Bộ đệm chứa nội dung dòng hiện tại
    int line_num = 1;                 // Biến đếm số dòng đang xét
    int same = 1;                     // Biến cờ (flag) đánh dấu trạng thái giống nhau

    // 1. Kiểm tra tham số dòng lệnh: người dùng phải truyền đủ 2 tên file
    if (argc != 3) {
        printf("Usage: compare <file1> <file2>\n");
        return 1;
    }

    // 2. Mở hai tệp tin ở chế độ đọc ("r")
    f1 = fopen(argv[1], "r");
    f2 = fopen(argv[2], "r");

    // Kiểm tra xem việc mở file có thành công hay không (tránh lỗi NULL pointer)
    if (f1 == NULL || f2 == NULL) {
        printf("Error: Cannot open files\n");
        return 1;
    }

    /**
     * 3. Quá trình so sánh:
     * Sử dụng fgets để đọc đồng thời từng dòng từ cả hai file f1 và f2.
     * Vòng lặp dừng lại khi một trong hai file kết thúc (NULL).
     */
    while (fgets(line1, MAX_LINE_LEN, f1) != NULL && 
           fgets(line2, MAX_LINE_LEN, f2) != NULL) {
        
        // So sánh chuỗi nội dung của hai dòng
        if (strcmp(line1, line2) != 0) { 
            // Nếu phát hiện khác biệt: in thông tin và thoát vòng lặp
            printf("Different at line %d\n", line_num);
            printf("%s: %s", argv[1], line1);
            printf("%s: %s", argv[2], line2);
            same = 0; // Đánh dấu là đã tìm thấy điểm khác nhau
            break; 
        }
        line_num++; // Tăng số dòng sau mỗi lần so sánh khớp
    }

    /**
     * 4. Kết luận:
     * Nếu đã duyệt hết mà biến same vẫn là 1, nghĩa là không tìm thấy dòng nào khác biệt.
     */
    if (same) {
        // Lưu ý: Logic này giả định hai file có cùng số lượng dòng.
        printf("Files are identical\n"); 
    }

    // 5. Đóng file để giải phóng tài nguyên hệ thống
    fclose(f1); 
    fclose(f2); 
    return 0;
}
