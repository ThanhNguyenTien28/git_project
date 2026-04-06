/******************************************************************************
 * FILE NAME: c2_a6.c (sort_fields)
 *
 * DESCRIPTION:
 * This program reads multiple lines from standard input and sorts them
 * based on a specified field (column).
 *
 * The program supports:
 *   -k <field_number> : select column to sort
 *   -n                : numeric sorting
 *
 * Example usage:
 *
 *   ./sort
 *      -> sort by column 1 (string)
 *
 *   ./sort -k 2
 *      -> sort by column 2 (string)
 *
 *   ./sort -n
 *      -> sort by column 1 (numeric)
 *
 *   ./sort -k 2 -n
 *      -> sort by column 2 (numeric)
 *
 *
 * CODE GUIDELINE
 *
 * 1. Follow structured programming
 * 2. Use clear function responsibilities
 * 3. Avoid global variable modification without control
 * 4. Validate command line parameters
 * 5. Free allocated memory
 * 6. Use standard library safely
 * 7. Keep functions single-purpose
 *
 *
 * FUNCTION OVERVIEW
 *
 * 1. get_field()
 *    Extract a specific column from a text line
 *
 * 2. compare_fields()
 *    Compare two lines based on selected column
 *    Supports:
 *        -k field
 *        -n numeric
 *
 * 3. main()
 *    Read input
 *    Parse arguments
 *    Sort data
 *    Print result
 *
 *
 * COMMAND LINE OPTIONS
 *
 * -k <number>
 *      Select field to sort
 *
 * -n
 *      Numeric sorting
 *
 * -k 2 -n
 *      Sort column 2 using numeric comparison
 *
 *
 * INPUT FORMAT
 *
 * Text lines separated by newline
 *
 * Example:
 *
 * A 30
 * B 10
 * C 20
 *
 *
 * OUTPUT
 *
 * Sorted lines
 *
 *
 * MEMORY RULE
 *
 * malloc() used for each line
 * free() must be called after printing
 *
 *
 * AUTHOR: Thanh Nguyen Tien
 * VERSION: 1.0
 * DATE: 2026
 ******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINES 1000 // Số dòng tối đa hỗ trợ
#define MAXLEN 1000   // Độ dài tối đa của một dòng

char *lineptr[MAXLINES];
int numeric = 0; // Cờ sắp xếp theo số học (-n)
int field = 1;   // Trường cần sắp xếp (mặc định là cột 1)

/* * Hàm get_field: Trích xuất trường thứ n từ một dòng văn bản.
 * Các trường được phân cách bởi một hoặc nhiều khoảng trắng/tab.
 */
void get_field(char *line, int n, char *result) {
    int i = 0, j = 0, k = 1; // k là biến đếm thứ tự trường hiện tại
    
    // Bỏ qua các khoảng trắng ở đầu dòng
    while (isspace(line[i])) i++;
    
    // Duyệt qua các trường cho đến khi tới trường thứ n
    while (line[i] != '\0' && k < n) {
        // Đi qua hết các ký tự của trường hiện tại
        while (line[i] != '\0' && !isspace(line[i])) i++;
        // Đi qua các khoảng trắng giữa các trường
        while (isspace(line[i])) i++;
        k++;
    }
    
    // Copy nội dung của trường thứ n vào biến result
    while (line[i] != '\0' && !isspace(line[i])) {
        result[j++] = line[i++];
    }
    result[j] = '\0'; // Kết thúc chuỗi
}

/* * Hàm compare_fields: Hàm so sánh tùy biến dùng cho qsort.
 */
int compare_fields(const void *a, const void *b) {
    // Ép kiểu con trỏ void về con trỏ chuỗi
    char *s1 = *(char **)a;
    char *s2 = *(char **)b;
    char field1[MAXLEN], field2[MAXLEN];
    
    // Lấy nội dung trường cần sắp xếp của cả 2 dòng
    get_field(s1, field, field1);
    get_field(s2, field, field2);
    
    // Nếu có cờ -n, chuyển chuỗi thành số thực (double) để so sánh
    if (numeric) {
        double v1 = atof(field1);
        double v2 = atof(field2);
        if (v1 < v2) return -1;
        else if (v1 > v2) return 1;
        else return 0;
    } else {
        // Nếu không, so sánh chuỗi theo từ điển (lexicographic)
        return strcmp(field1, field2);
    }
}

int main(int argc, char *argv[]) {
    int nlines = 0;
    char buffer[MAXLEN];

    // Phân tích tham số dòng lệnh từ người dùng
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0) {
            numeric = 1; // Bật cờ sắp xếp số
        } else if (strcmp(argv[i], "-k") == 0 && i + 1 < argc) {
            field = atoi(argv[++i]); // Lấy chỉ số của trường cần sắp xếp
        }
    }

    printf("Nhap du lieu tung dong (Nhan Ctrl+D tren Linux/Mac hoac Ctrl+Z tren Windows de ket thuc):\n");
    
    // Đọc dữ liệu đầu vào từ bàn phím (hoặc file qua pipe)
    while (fgets(buffer, MAXLEN, stdin) != NULL && nlines < MAXLINES) {
        buffer[strcspn(buffer, "\n")] = 0; // Xóa ký tự xuống dòng '\n' ở cuối
        
        // Cấp phát bộ nhớ cho từng dòng và lưu vào mảng con trỏ
        lineptr[nlines] = malloc(strlen(buffer) + 1);
        strcpy(lineptr[nlines], buffer);
        nlines++;
    }

    // Tiến hành sắp xếp mảng con trỏ
    qsort(lineptr, nlines, sizeof(char *), compare_fields);

    // In kết quả ra màn hình
    printf("\n--- Ket qua sap xep (Sap xep theo cot %d, Kieu so: %s) ---\n", field, numeric ? "Co" : "Khong");
    for (int i = 0; i < nlines; i++) {
        printf("%s\n", lineptr[i]);
        free(lineptr[i]); // Giải phóng bộ nhớ đã cấp phát
    }

    return 0;
}
