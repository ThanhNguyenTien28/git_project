#include <stdio.h>
#include <stdlib.h>

/**
 * @Description: Định nghĩa cấu trúc của một Node trong danh sách liên kết đơn.
 * Mỗi Node bao gồm dữ liệu số nguyên và một con trỏ trỏ đến Node tiếp theo.
 */
struct node
{
    int data;           // Dữ liệu lưu trữ trong node
    struct node* next;  // Con trỏ trỏ đến node kế tiếp trong danh sách
};

/**
 * @Function: makeNode
 * @Description: Cấp phát bộ nhớ động và khởi tạo một Node mới.
 * @Parameter: 
 * - x: Giá trị số nguyên muốn lưu vào Node.
 * @Return: struct node* - Con trỏ trỏ đến Node vừa được tạo.
 */
struct node* makeNode(int x)
{
    struct node* newNode = (struct node*)malloc(sizeof(struct node));

    newNode->data = x;
    newNode->next = NULL;

    return newNode;
}

/**
 * @Function: display
 * @Description: Duyệt qua toàn bộ danh sách và in dữ liệu của từng Node ra màn hình.
 * @Parameter: 
 * - head: Con trỏ trỏ đến Node đầu tiên của danh sách.
 * @Return: void
 */
void display(struct node* head)
{
    struct node* p = head;

    while(p != NULL)
    {
        printf("%d ", p->data);
        p = p->next; // Di chuyển đến node tiếp theo
    }

    printf("\n");
}

/**
 * @Function: addback
 * @Description: Thêm một Node mới chứa dữ liệu vào cuối danh sách liên kết.
 * @Parameter: 
 * - head: Con trỏ trỏ đến đầu danh sách hiện tại.
 * - data: Giá trị cần thêm vào.
 * @Return: struct node* - Trả về head mới (đặc biệt quan trọng khi thêm vào danh sách rỗng).
 */
struct node* addback(struct node* head, int data)
{
    struct node* newNode = makeNode(data);

    // Nếu danh sách rỗng, Node mới chính là head
    if(head == NULL)
        return newNode;

    struct node* p = head;

    // Duyệt đến node cuối cùng (node có next là NULL)
    while(p->next != NULL)
        p = p->next;

    p->next = newNode; // Nối node mới vào cuối

    return head;
}

/**
 * @Function: find
 * @Description: Tìm kiếm một giá trị trong danh sách liên kết.
 * @Parameter: 
 * - head: Con trỏ trỏ đến đầu danh sách.
 * - data: Giá trị cần tìm kiếm.
 * @Return: struct node* - Trả về địa chỉ của Node tìm thấy, hoặc NULL nếu không thấy.
 */
struct node* find(struct node* head, int data)
{
    struct node* p = head;

    while(p != NULL)
    {
        if(p->data == data)
            return p;

        p = p->next;
    }

    return NULL;
}

/**
 * @Function: delnode
 * @Description: Xóa một Node cụ thể ra khỏi danh sách liên kết và giải phóng bộ nhớ.
 * @Parameter: 
 * - head: Con trỏ trỏ đến đầu danh sách.
 * - pelement: Địa chỉ của Node cần xóa.
 * @Return: struct node* - Trả về head mới sau khi xóa.
 */
struct node* delnode(struct node* head, struct node* pelement)
{
    if(head == NULL || pelement == NULL)
        return head;

    // Trường hợp Node cần xóa nằm ngay đầu danh sách
    if(pelement == head)
    {
        head = head->next;
        free(pelement);
        return head;
    }

    struct node* prev = head;

    // Tìm node đứng ngay trước node cần xóa
    while(prev->next != pelement)
        prev = prev->next;

    // "Bắc cầu" qua node cần xóa
    prev->next = pelement->next;

    free(pelement); // Giải phóng bộ nhớ

    return head;
}

/**
 * @Function: freelist
 * @Description: Giải phóng toàn bộ bộ nhớ của danh sách liên kết khi không còn sử dụng.
 * @Parameter: 
 * - head: Con trỏ đầu danh sách.
 * @Return: void
 */
void freelist(struct node* head)
{
    struct node* p = head;

    while(p != NULL)
    {
        struct node* temp = p;
        p = p->next;
        free(temp); // Giải phóng từng node
    }
}

/**
 * @Function: main
 * @Description: Luồng chính điều khiển chương trình: nhập danh sách, tìm kiếm và xóa phần tử.
 */
int main()
{
    struct node* head = NULL;

    int n;
    printf("Nhap so luong phan tu: ");
    scanf("%d", &n);

    // Nhập danh sách từ người dùng
    for(int i = 0; i < n; i++)
    {
        int x;
        printf("Nhap phan tu thu %d: ", i+1);
        scanf("%d", &x);

        head = addback(head, x);
    }

    printf("\nDanh sach:\n");
    display(head);

    // Thực hiện tìm kiếm và xóa
    int value;
    printf("\nNhap so can tim: ");
    scanf("%d", &value);

    struct node* f = find(head, value);

    if(f != NULL)
    {
        printf("Tim thay %d\n", f->data);

        head = delnode(head, f); // Xóa node vừa tìm thấy

        printf("Sau khi xoa:\n");
        display(head);
    }
    else
        printf("Khong tim thay\n");

    // Dọn dẹp bộ nhớ trước khi kết thúc
    freelist(head);

    return 0;
}
