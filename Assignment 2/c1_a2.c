#include <stdio.h>

/**
 * @Function: main
 * @Description: Xác định và in ra dải giá trị (range) của các kiểu dữ liệu nguyên cơ bản 
 * (char, short, int, long) cả có dấu (signed) và không dấu (unsigned). 
 * Chương trình sử dụng các phép toán trên bit để tự tính toán các giá trị cực đại và cực tiểu.
 * @Parameter: Không có
 * @Return: int - Trả về 0 sau khi hoàn thành việc tính toán và hiển thị kết quả.
 */
int main() {
    
    // 1. Kiểu char (Thường là 8-bit)
    // ~0 tạo ra một dãy bit toàn 1. Ép kiểu về unsigned char để có giá trị 255 (11111111).
    unsigned char uc = (unsigned char)~0; 
    // Dịch phải 1 bit (01111111) để lấy giá trị dương lớn nhất cho kiểu có dấu.
    char cmax = (char)(uc >> 1); 
    // Trong hệ số bù 2, giá trị âm nhỏ nhất bằng -(max + 1).
    char cmin = -cmax - 1; 
    printf("char: %d to %d\n", cmin, cmax); 
    printf("unsigned char: 0 to %u\n\n", uc); 

    // 2. Kiểu short (Thường là 16-bit)
    unsigned short us = (unsigned short)~0; 
    short smax = (short)(us >> 1); 
    short smin = -smax - 1; 
    printf("short: %d to %d\n", smin, smax); 
    printf("unsigned short: 0 to %u\n\n", us); 

    // 3. Kiểu int (Thường là 32-bit)
    unsigned int ui = (unsigned int)~0; 
    int imax = (int)(ui >> 1); 
    int imin = -imax - 1; 
    printf("int: %d to %d\n", imin, imax); 
    printf("unsigned int: 0 to %u\n\n", ui); 

    // 4. Kiểu long (Thường là 32-bit hoặc 64-bit tùy hệ điều hành/trình biên dịch)
    unsigned long ul = (unsigned long)~0; 
    long lmax = (long)(ul >> 1); 
    long lmin = -lmax - 1; 
    printf("long: %ld to %ld\n", lmin, lmax); 
    printf("unsigned long: 0 to %lu\n", ul); 

    return 0;
}
