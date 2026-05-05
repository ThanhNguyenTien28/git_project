#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @Description: Kích thước của mảng băm (Buckets). 
 * Số lượng bucket càng lớn thì khả năng xung đột càng thấp.
 */
#define SIZE 100

/**
 * @Description: Cấu trúc của một Node trong danh sách liên kết.
 * Được dùng để lưu trữ dữ liệu tại mỗi bucket của bảng băm.
 * - word: Từ vựng cần lưu.
 * - count: Số lần xuất hiện của từ đó.
 * - next: Con trỏ trỏ đến node tiếp theo trong trường hợp xảy ra xung đột (collision).
 */
struct node
{
    char word[50];
    int count;
    struct node* next;
};

/**
 * @Description: Khai báo bảng băm (Hash Table).
 * Là một mảng các con trỏ trỏ tới struct node, tất cả khởi tạo là NULL.
 */
struct node* table[SIZE] = {NULL};

/**
 * @Function: hash
 * @Description: Hàm băm (Hash function). Chuyển đổi một chuỗi ký tự thành một chỉ số mảng.
 * Sử dụng thuật toán nhân với số nguyên tố 31 - một kỹ thuật phổ biến để phân phối dữ liệu đồng đều.
 * @Parameter: 
 * - s: Chuỗi ký tự cần băm.
 * @Return: unsigned int - Chỉ số (index) trong mảng từ 0 đến SIZE-1.
 */
unsigned int hash(char* s)
{
    unsigned int h = 0;

    while(*s)
    {
        // Công thức băm: h_n = h_{n-1} * 31 + ký tự_n
        //VD: chuỗi "Ab",Mã ASCII: 'A' = 65, 'b' = 98 va => h = 65 * 31 + 98 = 2113
        h = h * 31 + *s;
        s++;
    }

    return h % SIZE; // Trả về chỉ số nằm trong phạm vi mảng từ 0 đến 99
                    // 2113 % 100 =13  => dữ liệu "Ab" được đặt vào arr[13] trong bảng hăm
}

/**
 * @Function: lookup
 * @Description: Tìm kiếm một từ trong bảng băm. 
 * - Nếu tìm thấy: Trả về con trỏ tới node chứa từ đó.
 * - Nếu không thấy: Tạo một node mới, chèn vào đầu danh sách tại bucket tương ứng.
 * @Parameter: 
 * - word: Từ cần tìm hoặc thêm mới.
 * @Return: struct node* - Con trỏ tới node chứa dữ liệu.
//** Chuyển từ cần tìm sang dạng index, dò index xem có trùng index trong bảng hăm  không(có thể chứa nhiều chuỗi khác cùng index), nếu có thì so sánh các từ trong Node  với từ cần tìm không, nếu không thì thêm vào bảng hăm
 */
struct node* lookup(char* word)
{
    unsigned int index = hash(word); // Tính vị trí bucket

    struct node* p = table[index];

    /* 1. Duyệt qua danh sách liên kết tại bucket index để tìm từ */
    while(p != NULL)
    {
        if(strcmp(p->word, word) == 0)
        {
            return p; // Tìm thấy từ đã tồn tại
        }
        p = p->next;
    }

    /* 2. Nếu không tìm thấy, thực hiện cấp phát node mới */
    p = (struct node*)malloc(sizeof(struct node));
    if (p == NULL) return NULL; // Kiểm tra lỗi cấp phát

    strcpy(p->word, word);
    p->count = 0;

    /* 3. Chèn node mới vào đầu danh sách liên kết (Collision Handling: Chaining) */
    p->next = table[index];
    table[index] = p;

    return p;
}

/**
 * @Function: printtable
 * @Description: Duyệt qua toàn bộ bảng băm và in ra các cặp (từ : tần suất).
 * @Return: void
 */
void printtable()
{
    for(int i = 0; i < SIZE; i++)
    {
        struct node* p = table[i];
        while(p != NULL)
        {
            printf("%s : %d\n", p->word, p->count);
            p = p->next;
        }
    }
}

/**
 * @Function: cleartable
 * @Description: Giải phóng toàn bộ bộ nhớ động đã cấp phát cho bảng băm để tránh rò rỉ bộ nhớ.
 * @Return: void
 */
void cleartable()
{
    for(int i = 0; i < SIZE; i++)
    {
        struct node* p = table[i];
        while(p != NULL)
        {
            struct node* temp = p;
            p = p->next;
            free(temp); // Giải phóng từng node trong danh sách liên kết
        }
        table[i] = NULL; // Reset bucket về trạng thái trống
    }
}

/**
 * @Function: main
 * @Description: Luồng chính: Mở file, đọc từng từ, cập nhật bảng băm, in kết quả và dọn dẹp bộ nhớ.
 */
int main()
{
    FILE* f = fopen("book.txt","r");

    if(f == NULL)
    {
        printf("Cannot open file\n");
        return 1;
    }

    char word[50];

    // Đọc từng chuỗi ký tự (cách nhau bởi khoảng trắng) cho đến cuối file
    while(fscanf(f,"%s",word) != EOF)
    {
        struct node* p = lookup(word);
        if (p != NULL) {
            p->count++; // Tăng biến đếm tần suất
        }
    }

    fclose(f);

    printtable(); // Hiển thị kết quả thống kê

    cleartable(); // Dọn dẹp bộ nhớ trước khi thoát

    return 0;
}
