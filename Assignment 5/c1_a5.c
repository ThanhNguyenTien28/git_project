#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Cấu trúc sinh viên
    gồm:
    firstname
    lastname
    age
*/
struct student
{
    char firstname[20];
    char lastname[20];
    int age;
};

/*
    Hàm in thông tin 1 sinh viên
*/
void printStudent(struct student s)
{
    printf("%s %s %d\n", s.firstname, s.lastname, s.age);
}

/*
    Hàm in toàn bộ mảng sinh viên
*/
void printArray(struct student arr[], int n)
{
    for(int i = 0; i < n; i++)
    {
        printStudent(arr[i]);
    }
}

/*
    Callback function để so sánh firstname

    qsort sẽ gọi hàm này
    a và b là con trỏ void
    cần ép kiểu về student

    return:
    <0  nếu s1 < s2
    =0  nếu bằng
    >0  nếu s1 > s2
*/
int cmp_firstname(const void* a, const void* b)
{
    struct student* s1 = (struct student*)a;
    struct student* s2 = (struct student*)b;

    return strcmp(s1->firstname, s2->firstname);
}

/*
    Callback so sánh lastname
*/
int cmp_lastname(const void* a, const void* b)
{
    struct student* s1 = (struct student*)a;
    struct student* s2 = (struct student*)b;

    return strcmp(s1->lastname, s2->lastname);
}

/*
    Hàm kiểm tra sinh viên > 20 tuổi

    Nếu >20 thì in
*/
void isolder(struct student s)
{
    if(s.age > 20)
    {
        printStudent(s);
    }
}

/*
    apply()

    Duyệt toàn bộ mảng
    và gọi function pointer fp

    fp là hàm nhận struct student
*/
void apply(struct student arr[], int n, void (*fp)(struct student))
{
    for(int i = 0; i < n; i++)
    {
        fp(arr[i]);
    }
}

int main()
{
    /*
        Tạo mảng sinh viên
    */
    struct student class[] =
    {
        {"Thanh","Nguyen",22},
        {"An","Tran",19},
        {"Binh","Le",21},
        {"Cuong","Pham",18},
        {"Dung","Hoang",23}
    };

    int n = sizeof(class)/sizeof(class[0]);

    printf("=== Original list ===\n");
    printArray(class,n);

    /*
        Sắp xếp theo firstname
        qsort( mảng, số phần tử, size, callback )
    */
    printf("\n=== Sort by firstname ===\n");

    qsort(class, n, sizeof(struct student), cmp_firstname);

    printArray(class,n);

    /*
        Sắp xếp theo lastname
    */
    printf("\n=== Sort by lastname ===\n");

    qsort(class, n, sizeof(struct student), cmp_lastname);

    printArray(class,n);

    /*
        In sinh viên tuổi >20
        apply sẽ gọi isolder
    */
    printf("\n=== Students age > 20 ===\n");

    apply(class,n,isolder);

    return 0;
}
