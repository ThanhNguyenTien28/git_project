#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @Description: Định nghĩa cấu trúc thông tin của một sinh viên.
 * Bao gồm tên, họ và tuổi.
 */
struct student
{
    char firstname[20];
    char lastname[20];
    int age;
};

/**
 * @Function: printStudent
 * @Description: In thông tin của một sinh viên cụ thể ra màn hình.
 * @Parameter: 
 * - s: Biến kiểu struct student chứa dữ liệu cần in.
 * @Return: void
 */
void printStudent(struct student s)
{
    printf("%-10s %-10s %d\n", s.firstname, s.lastname, s.age);
}

/**
 * @Function: printArray
 * @Description: Duyệt qua mảng sinh viên và gọi hàm in cho từng phần tử.
 * @Parameter: 
 * - arr[]: Mảng các struct student.
 * - n: Số lượng sinh viên trong mảng.
 * @Return: void
 */
void printArray(struct student arr[], int n)
{
    for(int i = 0; i < n; i++)
    {
        printStudent(arr[i]);
    }
}

/**
 * @Function: cmp_firstname
 * @Description: Hàm callback so sánh hai sinh viên theo tên (firstname).
 * Được sử dụng làm tham số cho hàm qsort.
 * @Parameter: 
 * - a, b: Con trỏ void (địa chỉ của hai phần tử cần so sánh).
 * @Return: int - Kết quả của strcmp (<0, 0, >0).
 */
int cmp_firstname(const void* a, const void* b)
{
    // Ép kiểu từ con trỏ void về con trỏ struct student để truy cập dữ liệu
    struct student* s1 = (struct student*)a;
    struct student* s2 = (struct student*)b;

    return strcmp(s1->firstname, s2->firstname);
}

/**
 * @Function: cmp_lastname
 * @Description: Hàm callback so sánh hai sinh viên theo họ (lastname).
 * @Parameter: 
 * - a, b: Con trỏ void.
 * @Return: int - Kết quả so sánh chuỗi.
 */
int cmp_lastname(const void* a, const void* b)
{
    struct student* s1 = (struct student*)a;
    struct student* s2 = (struct student*)b;

    return strcmp(s1->lastname, s2->lastname);
}

/**
 * @Function: isolder
 * @Description: Kiểm tra và in thông tin nếu sinh viên có tuổi lớn hơn 20.
 * Hàm này được thiết kế để dùng chung với hàm apply.
 * @Parameter: 
 * - s: Struct student cần kiểm tra.
 * @Return: void
 */
void isolder(struct student s)
{
    if(s.age > 20)
    {
        printStudent(s);
    }
}

/**
 * @Function: apply
 * @Description: Một hàm bậc cao (Higher-order function) duyệt qua mảng và
 * thực thi một hàm chức năng (fp) lên từng phần tử của mảng đó.
 * @Parameter: 
 * - arr[]: Mảng dữ liệu đầu vào.
 * - n: Số lượng phần tử.
 * - fp: Con trỏ hàm trỏ tới hàm nhận tham số là struct student.
 * @Return: void
 */
void apply(struct student arr[], int n, void (*fp)(struct student))
{
    for(int i = 0; i < n; i++)
    {
        fp(arr[i]); // sử dụng fp là con trỏ hàm, gọi hàm thông qua con trỏ hàm
    }
}

/**
 * @Function: main
 * @Description: Điểm bắt đầu chương trình. Khởi tạo dữ liệu, thực hiện
 * sắp xếp theo nhiều tiêu chí và lọc dữ liệu bằng con trỏ hàm.
 */
int main()
{
    // Khởi tạo mảng sinh viên mẫu
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

    // Sử dụng qsort để sắp xếp theo Firstname
    printf("\n=== Sort by firstname ===\n");
    qsort(class, n, sizeof(struct student), cmp_firstname);
    printArray(class,n);

    // Sử dụng qsort để sắp xếp theo Lastname
    printf("\n=== Sort by lastname ===\n");
    qsort(class, n, sizeof(struct student), cmp_lastname);
    printArray(class,n);

    // Sử dụng hàm apply kết hợp với con trỏ hàm isolder để lọc dữ liệu
    printf("\n=== Students age > 20 ===\n");
    apply(class,n,isolder); //fp của hàm apppy là con trỏ hàm, gọi hàm isolder để duyệt tất cả sinh viên hơn 20 tuổi trong mảng class//

    return 0;
}
