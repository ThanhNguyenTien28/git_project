#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

/* Biến tĩnh nội bộ lưu trữ bảng băm */
static Node* buckets[HASH_TABLE_SIZE];

/**
 * Function:    hash
 * Description: Thuật toán băm đa thức nhân với 31.
 */
static unsigned int hash(char *str) {
    unsigned int h = 0U;
    if (str != NULL) {
        while (*str != '\0') {
            h = (h * 31U) + (unsigned int)(*str);
            str++;
        }
    }
    return (h % HASH_TABLE_SIZE);
}

void init_table(void) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        buckets[i] = NULL;
    }
    printf("He thong: Da khoi tao bang bam thanh cong.\n");
}

void insert(char *name, char *phone) {
    unsigned int index = hash(name);
    Node* newNode = (Node*)malloc(sizeof(Node));
    
    if (newNode == NULL) {
        printf("Loi: Khong the cap phat bo nho.\n");
        return;
    }

    /* Sao chép dữ liệu an toàn */
    strncpy(newNode->name, name, MAX_NAME_LEN - 1);
    newNode->name[MAX_NAME_LEN - 1] = '\0';
    strncpy(newNode->phone, phone, MAX_PHONE_LEN - 1);
    newNode->phone[MAX_PHONE_LEN - 1] = '\0';

    /* Chèn vào đầu danh sách liên kết */
    newNode->next = buckets[index];
    buckets[index] = newNode;
    printf("Da them: %s - %s\n", name, phone);
}

void search(char *name) {
    unsigned int index = hash(name);
    Node* curr = buckets[index];

    while (curr != NULL) {
        if (strcmp(curr->name, name) == 0) {
            printf("Tim thay '%s': %s\n", name, curr->phone);
            return;
        }
        curr = curr->next;
    }
    printf("Ket qua: Khong tim thay '%s'.\n", name);
}

void delete_contact(char *name) {
    unsigned int index = hash(name);
    Node *curr = buckets[index];
    Node *prev = NULL;

    while (curr != NULL) {
        if (strcmp(curr->name, name) == 0) {
            if (prev == NULL) {
                buckets[index] = curr->next;
            } else {
                prev->next = curr->next;
            }
            free(curr);
            printf("Da xoa: %s\n", name);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    printf("Loi: Khong tim thay '%s' de xoa.\n", name);
}

void print_all(void) {
    printf("\n--- CHI TIET CAU TRUC BANG BAM ---\n");
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        Node* curr = buckets[i];
        printf("Bucket [%d]: ", i);
        while (curr != NULL) {
            printf("[%s] -> ", curr->name);
            curr = curr->next;
        }
        printf("NULL\n");
    }
}

void free_table(void) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        Node* curr = buckets[i];
        while (curr != NULL) {
            Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
        buckets[i] = NULL;
    }
    printf("He thong: Da giai phong toan bo bo nho.\n");
}
