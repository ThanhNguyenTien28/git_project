#include <stdio.h>  /* Cung cấp các hàm I/O như printf */

int main(void) {
  

    /* 1. Kieu char */
    unsigned char uc = (unsigned char)~0; /* Đảo bit 00...0 thành 11...1 để lấy giá trị max */
    char cmax = (char)(uc >> 1);          /* Dịch phải 1 bit để bỏ bit dấu */
    char cmin = -cmax - 1;                /* Hệ số bù 2: miền âm lớn hơn miền dương 1 đơn vị */
    printf("char: %d to %d\n", cmin, cmax);
    printf("unsigned char: 0 to %u\n\n", uc);

    /* 2. Kieu short */
    unsigned short us = (unsigned short)~0;
    short smax = (short)(us >> 1);
    short smin = -smax - 1;
    printf("short: %d to %d\n", smin, smax);
    printf("unsigned short: 0 to %u\n\n", us);

    /* 3. Kieu int */
    unsigned int ui = (unsigned int)~0;
    int imax = (int)(ui >> 1);
    int imin = -imax - 1;
    printf("int: %d to %d\n", imin, imax);
    printf("unsigned int: 0 to %u\n\n", ui);

    /* 4. Kieu long */
    unsigned long ul = (unsigned long)~0;
    long lmax = (long)(ul >> 1);
    long lmin = -lmax - 1;
    printf("long: %ld to %ld\n", lmin, lmax);
    printf("unsigned long: 0 to %lu\n", ul);

    return 0; 
}
