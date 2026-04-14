#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LEN 1000  // Độ dài tối đa của một dòng văn bản
#define LINE_PER_PAGE 10   // Quy định số dòng hiển thị trên mỗi trang

/**
 * @Function: print_file
 * @Description: Đọc nội dung của một tệp tin và in ra màn hình theo từng trang.
 * Mỗi trang sẽ có tiêu đề bao gồm tên tệp và số thứ tự trang. Mỗi dòng văn bản
 * đều được đánh số thứ tự để dễ theo dõi.
 * @Parameter: 
 * - file_name: Chuỗi ký tự chứa đường dẫn/tên tệp cần in.
 * @Return: void
 */
void print_file(char *file_name) {
    FILE *fp;
    char line[MAX_LINE_LEN];
    int line_number = 1; // Biến đếm tổng số dòng đã đọc được

    // Mở tệp tin ở chế độ đọc văn bản
    fp = fopen(file_name, "r"); 
    if (fp == NULL) {
        printf("Cannot open %s\n", file_name); 
        return;
    }

    // Đọc liên tục cho đến khi hết tệp tin
    while (fgets(line, MAX_LINE_LEN, fp) != NULL) { 
        
        /* * Kiểm tra điều kiện bắt đầu một trang mới:
         * (line_number - 1) % LINE_PER_PAGE == 0 sẽ đúng tại các dòng 1, 11, 21, ...
         */
        if ((line_number - 1) % LINE_PER_PAGE == 0) {
            int page = (line_number - 1) / LINE_PER_PAGE + 1; 
            printf("\n--- [%s] - Page %d ---\n", file_name, page); 
        }

        // In số thứ tự dòng và nội dung dòng đó
        printf("%4d: %s", line_number, line);
        line_number++; 
    }
    
    // Giải phóng tài nguyên tệp tin sau khi sử dụng
    fclose(fp); 
}

/**
 * @Function: main
 * @Description: Điểm bắt đầu của chương trình. Tiếp nhận danh sách các tệp tin
 * từ tham số dòng lệnh và lần lượt gọi hàm in cho từng tệp.
 * @Parameter: 
 * - argc: Số lượng tham số dòng lệnh.
 * - argv: Mảng các chuỗi ký tự chứa tên các tệp tin cần xử lý.
 * @Return: int - Trả về 0 khi hoàn thành, 1 nếu thiếu tham số đầu vào.
 */
int main(int argc, char *argv[]) {
    // Kiểm tra nếu người dùng không truyền tên file nào
    if (argc < 2) { 
        printf("Usage: %s <file1> <file2> ...\n", argv[0]); 
        return 1;
    }

    // Duyệt qua danh sách các file được truyền vào từ tham số thứ 1 đến hết
    for (int i = 1; i < argc; i++) { 
        print_file(argv[i]);
        printf("\n\n"); // Khoảng cách giữa các file khác nhau
    }

    return 0;
}
