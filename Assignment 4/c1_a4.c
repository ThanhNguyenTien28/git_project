#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node* next;
};

// tạo node
struct node* makeNode(int x)
{
    struct node* newNode = (struct node*)malloc(sizeof(struct node));

    newNode->data = x;
    newNode->next = NULL;

    return newNode;
}

// hiển thị
void display(struct node* head)
{
    struct node* p = head;

    while(p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }

    printf("\n");
}

// thêm cuối
struct node* addback(struct node* head, int data)
{
    struct node* newNode = makeNode(data);

    if(head == NULL)
        return newNode;

    struct node* p = head;

    while(p->next != NULL)
        p = p->next;

    p->next = newNode;

    return head;
}

// tìm
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

// xóa node
struct node* delnode(struct node* head, struct node* pelement)
{
    if(head == NULL || pelement == NULL)
        return head;

    // xóa head
    if(pelement == head)
    {
        head = head->next;
        free(pelement);
        return head;
    }

    struct node* prev = head;

    while(prev->next != pelement)
        prev = prev->next;

    prev->next = pelement->next;

    free(pelement);

    return head;
}

// xóa toàn bộ
void freelist(struct node* head)
{
    struct node* p = head;

    while(p != NULL)
    {
        struct node* temp = p;
        p = p->next;
        free(temp);
    }
}

int main()
{
    struct node* head = NULL;

    int n;
    printf("Nhap so luong phan tu: ");
    scanf("%d", &n);

    // nhập danh sách
    for(int i = 0; i < n; i++)
    {
        int x;
        printf("Nhap phan tu thu %d: ", i+1);
        scanf("%d", &x);

        head = addback(head, x);
    }

    printf("\nDanh sach:\n");
    display(head);

    // tìm
    int value;
    printf("\nNhap so can tim: ");
    scanf("%d", &value);

    struct node* f = find(head, value);

    if(f != NULL)
    {
        printf("Tim thay %d\n", f->data);

        head = delnode(head, f);

        printf("Sau khi xoa:\n");
        display(head);
    }
    else
        printf("Khong tim thay\n");

    freelist(head);

    return 0;
}
