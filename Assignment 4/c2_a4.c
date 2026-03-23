#include <stdio.h>
#include <stdlib.h>

// ================== struct node ==================
struct tnode
{
    int data;
    struct tnode* left;
    struct tnode* right;
};

// ================== a) talloc ==================
struct tnode* talloc(int data)
{
    struct tnode* newNode;

    newNode = (struct tnode*)malloc(sizeof(struct tnode));

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// ================== b) addnode ==================
struct tnode* addnode(struct tnode* root, int data)
{
    if(root == NULL)
        return talloc(data);

    if(data < root->data)
        root->left = addnode(root->left, data);
    else
        root->right = addnode(root->right, data);

    return root;
}

// ================== c) preorder ==================
void preorder(struct tnode* root)
{
    if(root == NULL)
        return;

    printf("%d ", root->data);

    preorder(root->left);
    preorder(root->right);
}

// ================== d) inorder ==================
void inorder(struct tnode* root)
{
    if(root == NULL)
        return;

    inorder(root->left);

    printf("%d ", root->data);

    inorder(root->right);
}

// ================== e) deltree ==================
int deltree(struct tnode* root)
{
    if(root == NULL)
        return 0;

    int left = deltree(root->left);
    int right = deltree(root->right);

    free(root);

    return left + right + 1;
}

// ================== f) test ==================
int main()
{
    struct tnode* root = NULL;

    // thêm các số theo đề bài
    root = addnode(root, 3);
    root = addnode(root, 1);
    root = addnode(root, 0);
    root = addnode(root, 2);
    root = addnode(root, 8);
    root = addnode(root, 6);
    root = addnode(root, 5);
    root = addnode(root, 9);

    // preorder
    printf("Preorder:\n");
    preorder(root);

    // inorder
    printf("\n\nInorder:\n");
    inorder(root);

    // xóa cây
    int count = deltree(root);

    printf("\n\nDeleted nodes: %d\n", count);

    return 0;
}
