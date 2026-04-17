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
 Bước 1: Sử dụng malloc để xin cấp phát vùng nhớ cho một cấu trúc tnode.

Bước 2: Gán giá trị dữ liệu vào trường data.

Bước 3: Khởi tạo hai con trỏ left và right bằng NULL (nút mới luôn là nút lá khi vừa tạo).

Bước 4: Trả về con trỏ tới vùng nhớ vừa tạo.
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
Bước 1: Nếu cây hiện tại rỗng (root == NULL), tạo nút mới tại vị trí đó bằng hàm talloc.

Bước 2: Nếu data nhỏ hơn giá trị tại root, gọi đệ quy hàm addnode cho nhánh bên trái.

Bước 3: Nếu data lớn hơn hoặc bằng giá trị tại root, gọi đệ quy hàm addnode cho nhánh bên phải.

Bước 4: Trả về con trỏ root đã được cập nhật liên kết. 
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
Bước 1: Kiểm tra điều kiện dừng: nếu nút hiện tại là NULL thì quay lại.

Bước 2: Thăm (in giá trị) nút gốc trước.

Bước 3: Gọi đệ quy duyệt toàn bộ nhánh trái.

Bước 4: Gọi đệ quy duyệt toàn bộ nhánh phải. 
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
Bước 1: Kiểm tra điều kiện dừng: nếu nút hiện tại là NULL thì quay lại.

Bước 2: Gọi đệ quy duyệt nhánh trái trước (để lấy các giá trị nhỏ hơn).

Bước 3: Thăm (in giá trị) nút gốc.

Bước 4: Gọi đệ quy duyệt nhánh phải (để lấy các giá trị lớn hơn).

Đặc điểm: Kết quả thu được luôn là một dãy số tăng dần trong BST. 
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
Bước 1: Sử dụng phương pháp duyệt Postorder (Sau): Duyệt trái -> Duyệt phải -> Xóa gốc.

Bước 2: Đệ quy giải phóng nhánh trái và nhánh phải trước để không làm mất địa chỉ của các nút con.

Bước 3: Gọi free(root) để giải phóng nút hiện tại sau khi các con đã được xóa.

Bước 4: Tích lũy và trả về tổng số nút đã giải phóng bằng cách cộng kết quả từ các nhánh con cộng thêm 1 (nút hiện tại). 
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
