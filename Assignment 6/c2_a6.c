#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINES 1000 // Số dòng tối đa hỗ trợ
#define MAXLEN 1000   // Độ dài tối đa của một dòng

/* Biến toàn cục điều khiển hành vi sắp xếp */
char *lineptr[MAXLINES]; // Mảng các con trỏ trỏ đến từng dòng văn bản
int numeric = 0;         // Cờ sắp xếp theo số học (-n). 0: String, 1: Numeric
int field = 1;           // Thứ tự cột cần sắp xếp (mặc định là cột 1)

/**
 * @Function: get_field
 * @Description: Trích xuất nội dung của một cột (trường) cụ thể từ một dòng văn bản.
 * Các trường được định nghĩa là các cụm ký tự phân cách bởi khoảng trắng hoặc tab.
 * @Parameter: 
 * - line: Chuỗi ký tự gốc chứa toàn bộ dòng.
 * - n: Số thứ tự của cột muốn lấy (bắt đầu từ 1).
 * - result: Vùng nhớ để lưu trữ nội dung cột trích xuất được.
 * @Return: void
 */
void get_field(char *line, int n, char *result) {
    int i = 0, j = 0, k = 1; //Biến i: Con trỏ vị trí trên dòng gốc (line)
                             //Biến k: Bộ đếm số thứ tự cột
                             //Biến j: Con trỏ vị trí trên chuỗi kết quả (result)
    // Bỏ qua các khoảng trắng dư thừa ở đầu dòng
    while (isspace(line[i])) i++;
    
    // Duyệt qua các cụm ký tự để tìm đến đúng cột thứ n hoặc là hết dòng
    while (line[i] != '\0' && k < n) {
        // Bỏ qua các ký tự thuộc cột hiện tại
        while (line[i] != '\0' && !isspace(line[i])) i++;
        // Bỏ qua khoảng trắng giữa cột hiện tại và cột kế tiếp
        while (isspace(line[i])) i++;
        k++;
    }
    
    // Sao chép nội dung của cột tìm được vào biến kết quả
    while (line[i] != '\0' && !isspace(line[i])) {
        result[j++] = line[i++];
    }
    result[j] = '\0'; // Đảm bảo chuỗi kết quả có ký tự kết thúc
}

/**
 * @Function: compare_fields
 * @Description: Hàm so sánh tùy biến (Callback) cung cấp cho hàm qsort.
 * Hàm này sẽ trích xuất đúng cột yêu cầu từ hai dòng và so sánh chúng
 * theo kiểu chuỗi hoặc kiểu số dựa trên tham số dòng lệnh.
 * @Parameter: 
 * - a: Con trỏ void trỏ tới phần tử thứ nhất (dòng 1).
 * - b: Con trỏ void trỏ tới phần tử thứ hai (dòng 2).
 * @Return: int - Trả về <0 nếu a < b, >0 nếu a > b, và 0 nếu bằng nhau.
 */
int compare_fields(const void *a, const void *b) {
    // Ép kiểu ngược từ void* về char** vì lineptr là mảng các con trỏ chuỗi
    char *s1 = *(char **)a;
    char *s2 = *(char **)b;
    char field1[MAXLEN], field2[MAXLEN];
    
    // Lấy nội dung trường cần so sánh của cả 2 dòng
    get_field(s1, field, field1);
    get_field(s2, field, field2);
    
    if (numeric) {
        // So sánh theo giá trị số thực nếu người dùng chọn flag -n
        // Ham
        double v1 = atof(field1);
        double v2 = atof(field2);
        if (v1 < v2) return -1;
        else if (v1 > v2) return 1;
        else return 0;
    } else {
        // So sánh theo thứ tự từ điển (Lexicographic) mặc định
        return strcmp(field1, field2);
    }
}

/**
 * @Function: main
 * @Description: Luồng chính của chương trình: xử lý tham số dòng lệnh, 
 * nhận dữ liệu đầu vào, thực hiện sắp xếp bằng qsort và in kết quả.
 * @Parameter: 
 * - argc: Số lượng tham số dòng lệnh.
 * - argv: Mảng các chuỗi tham số (ví dụ: -n, -k).
 * @Return: int - 0 nếu thành công.
 
 
 Cú pháp: ./c2_a6 -n -k 3  
             với  -n là theo số, không có mặc định là theo chữ
		  -k 3 là sắp xếp theo cột( trường) thứ 3, nếu không có thì bằng định là cột 1

 */
int main(int argc, char *argv[]) {
    int nlines = 0;
    char buffer[MAXLEN];

    // 1. Phân tích tham số (Parsing arguments)
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0) {
            numeric = 1; 
        } else if (strcmp(argv[i], "-k") == 0 && i + 1 < argc) {
            field = atoi(argv[++i]); 
        }
    }

    printf("Nhap du lieu (Ctrl+D de ket thuc):\n");
    
    // 2. Nhận dữ liệu và cấp phát bộ nhớ động
    while (fgets(buffer, MAXLEN, stdin) != NULL && nlines < MAXLINES) {
        buffer[strcspn(buffer, "\n")] = 0; // Loại bỏ ký tự xuống dòng
        
        // Cấp phát vùng nhớ vừa đủ cho độ dài của dòng hiện tại
        lineptr[nlines] = (char *)malloc(strlen(buffer) + 1);
        if (lineptr[nlines] != NULL) {
            strcpy(lineptr[nlines], buffer);
            nlines++;
        }
    }

    // 3. Thực hiện sắp xếp nhanh (Quick Sort)
    // qsort sẽ gọi hàm compare_fields để quyết định thứ tự các dòng
    qsort(lineptr, nlines, sizeof(char *), compare_fields);

    // 4. In kết quả và giải phóng bộ nhớ (Freeing memory)
    printf("\n--- Ket qua (Cot: %d, So hoc: %s) ---\n", field, numeric ? "Co" : "Khong");
    for (int i = 0; i < nlines; i++) {
        printf("%s\n", lineptr[i]);
        free(lineptr[i]); // Giải phóng bộ nhớ của từng dòng đã malloc
    }

    return 0;
}
