#include <stdio.h>
#include <stdlib.h>

/**
 * @Description: Định nghĩa cấu trúc của một nút trong cây nhị phân (tnode).
 * Mỗi nút chứa một giá trị nguyên và hai con trỏ trỏ tới nhánh con bên trái và bên phải.
 */
struct tnode
{
    int data;           // Dữ liệu của nút
    struct tnode* left;  // Con trỏ tới nút con bên trái
    struct tnode* right; // Con trỏ tới nút con bên phải
};

/**
 * @Function: talloc
 * @Description: Cấp phát bộ nhớ cho một nút mới và khởi tạo các giá trị mặc định.
 * @Parameter: 
 * - data: Giá trị số nguyên khởi tạo cho nút.
 * @Return: struct tnode* - Con trỏ tới nút vừa cấp phát.
 */
struct tnode* talloc(int data)
{
    struct tnode* newNode;

    newNode = (struct tnode*)malloc(sizeof(struct tnode));

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

/**
 * @Function: addnode
 * @Description: Thêm một giá trị vào cây tìm kiếm nhị phân (BST) bằng đệ quy.
 * Duy trì tính chất: trái < cha < phải.
 * @Parameter: 
 * - root: Con trỏ tới gốc của cây hoặc cây con.
 * - data: Giá trị cần thêm.
 * @Return: struct tnode* - Con trỏ tới gốc của cây sau khi đã thêm nút.
 */
struct tnode* addnode(struct tnode* root, int data)
{
    // Nếu vị trí hiện tại trống, tạo nút mới tại đây
    if(root == NULL)
        return talloc(data);

    // Nếu dữ liệu nhỏ hơn gốc, đi về phía bên trái
    if(data < root->data)
        root->left = addnode(root->left, data);
    // Nếu dữ liệu lớn hơn hoặc bằng gốc, đi về phía bên phải
    else
        root->right = addnode(root->right, data);

    return root;
}

/**
 * @Function: preorder
 * @Description: Duyệt cây theo thứ tự Trước (Root -> Left -> Right).
 * @Parameter: 
 * - root: Gốc của cây cần duyệt.
 * @Return: void
 */
void preorder(struct tnode* root)
{
    if(root == NULL)
        return;

    printf("%d ", root->data); // Thăm nút gốc
    preorder(root->left);      // Duyệt nhánh trái
    preorder(root->right);     // Duyệt nhánh phải
}

/**
 * @Function: inorder
 * @Description: Duyệt cây theo thứ tự Giữa (Left -> Root -> Right).
 * Trong BST, cách duyệt này sẽ in ra dãy số đã được sắp xếp tăng dần.
 * @Parameter: 
 * - root: Gốc của cây cần duyệt.
 * @Return: void
 */
void inorder(struct tnode* root)
{
    if(root == NULL)
        return;

    inorder(root->left);       // Duyệt nhánh trái

    printf("%d ", root->data); // Thăm nút gốc

    inorder(root->right);      // Duyệt nhánh phải
}

/**
 * @Function: deltree
 * @Description: Xóa toàn bộ cây và giải phóng bộ nhớ bằng cách duyệt Postorder (Sau).
 * @Parameter: 
 * - root: Gốc của cây cần xóa.
 * @Return: int - Tổng số lượng nút đã được giải phóng.
 */
int deltree(struct tnode* root)
{
    if(root == NULL)
        return 0;

    // Đệ quy xóa các nhánh con trước
    int left = deltree(root->left);
    int right = deltree(root->right);

    // Sau khi các con đã được giải phóng, mới giải phóng nút cha
    free(root);

    // Trả về tổng số nút (con trái + con phải + chính nó)
    return left + right + 1;
}

/**
 * @Function: main
 * @Description: Khởi tạo cây, thêm dữ liệu mẫu, thực hiện các kiểu duyệt và xóa cây.
 */
int main()
{
    struct tnode* root = NULL;

    // Thêm các nút vào cây theo thứ tự đề bài
    root = addnode(root, 3);
    root = addnode(root, 1);
    root = addnode(root, 0);
    root = addnode(root, 2);
    root = addnode(root, 8);
    root = addnode(root, 6);
    root = addnode(root, 5);
    root = addnode(root, 9);

    // Hiển thị kết quả duyệt Preorder
    printf("Preorder:\n");
    preorder(root);

    // Hiển thị kết quả duyệt Inorder (Dãy tăng dần)
    printf("\n\nInorder (Sorted):\n");
    inorder(root);

    // Giải phóng bộ nhớ toàn bộ cây và đếm số nút
    int count = deltree(root);

    printf("\n\nTotal nodes deleted: %d\n", count);

    return 0;
}
