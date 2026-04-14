#include <stdio.h>
#include "hashtable.h"

int main(void) {
    init_table();

    printf("--- KIỂM THỬ THƯ VIỆN BẢNG BĂM ---\n");
    insert("Nguyễn Văn An", "0912000001");
    insert("Trần Thị Bình", "0912000002");
    
    search("Nguyễn Văn An");
    delete_contact("Trần Thị Bình");
    
    free_table();
    return 0;
}
