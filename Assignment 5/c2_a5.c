#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Kích thước bảng hash
*/
#define SIZE 100

/*
    Node của linked list

    word  : từ
    count : số lần xuất hiện
    next  : node tiếp theo
*/
struct node
{
    char word[50];
    int count;
    struct node* next;
};

/*
    Hash table
    là mảng con trỏ node
*/
struct node* table[SIZE] = {NULL};

/*
    Hàm hash

    chuyển word -> index

    công thức:
    h = h*31 + ký tự

    sau đó mod SIZE
*/
unsigned int hash(char* s)
{
    unsigned int h = 0;

    while(*s)
    {
        h = h * 31 + *s;
        s++;
    }

    return h % SIZE;
}

/*
    lookup()

    tìm word trong hash table

    nếu có -> return node
    nếu chưa có -> tạo mới
*/
struct node* lookup(char* word)
{
    unsigned int index = hash(word);

    struct node* p = table[index];

    /*
        duyệt linked list
    */
    while(p != NULL)
    {
        if(strcmp(p->word, word) == 0)
        {
            return p;
        }

        p = p->next;
    }

    /*
        nếu chưa có thì tạo node mới
    */
    p = (struct node*)malloc(sizeof(struct node));

    strcpy(p->word, word);
    p->count = 0;

    /*
        thêm vào đầu danh sách
    */
    p->next = table[index];
    table[index] = p;

    return p;
}

/*
    In hash table
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

/*
    cleartable()

    giải phóng toàn bộ bộ nhớ
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

            free(temp);
        }

        table[i] = NULL;
    }
}



int main()
{
    FILE* f = fopen("book.txt","r");

    if(f == NULL)
    {
        printf("Cannot open file\n");
        return 1;
    }

    char word[50];

    while(fscanf(f,"%s",word) != EOF)
    {
        struct node* p = lookup(word);
        p->count++;
    }

    fclose(f);

    printtable();

    cleartable();

    return 0;
}
