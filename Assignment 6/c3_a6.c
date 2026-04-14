#include <stdio.h>
#include <stdlib.h> /* Cho hàm atof() */
#include <ctype.h>

#define MAXVAL 100 // Độ sâu tối đa của ngăn xếp

/* Biến toàn cục phục vụ quản lý Stack */
int sp = 0;          // Con trỏ ngăn xếp (stack pointer)
double val[MAXVAL];  // Mảng chứa các giá trị của ngăn xếp

/**
 * @Function: push
 * @Description: Đẩy một giá trị kiểu thực (double) vào đỉnh ngăn xếp.
 * Kiểm tra lỗi tràn ngăn xếp (Stack Overflow) trước khi thêm.
 * @Parameter: 
 * - f: Giá trị số thực cần lưu trữ.
 * @Return: void
 */
void push(double f) {
    if (sp < MAXVAL) {
        val[sp++] = f;
    } else {
        printf("Loi: Ngan xep day, khong the day them gia tri %g\n", f);
    }
}

/**
 * @Function: pop
 * @Description: Lấy ra và trả về giá trị nằm ở đỉnh của ngăn xếp.
 * Kiểm tra lỗi ngăn xếp rỗng (Stack Underflow) để tránh lấy sai dữ liệu.
 * @Parameter: Không có
 * @Return: double - Giá trị lấy được từ đỉnh ngăn xếp, trả về 0.0 nếu rỗng.
 */
double pop(void) {
    if (sp > 0) {
        return val[--sp];
    } else {
        printf("Loi: Ngan xep trong (Thieu toan hang)\n");
        return 0.0;
    }
}

/**
 * @Function: main
 * @Description: Điểm nhập chính của chương trình. Tiếp nhận biểu thức hậu tố từ 
 * dòng lệnh, duyệt qua từng phần tử để phân loại là toán hạng (số) hay toán tử 
 * (+, -, *, /). Sử dụng ngăn xếp để thực hiện các phép tính trung gian.
 * @Parameter: 
 * - argc: Số lượng tham số truyền vào từ terminal.
 * - argv: Mảng các chuỗi ký tự chứa các thành phần của biểu thức.
 * @Return: int - Trả về 0 nếu tính toán thành công, 1 nếu gặp lỗi logic.
 */
int main(int argc, char *argv[]) {
    double op2;
    int i;

    // 1. Kiểm tra nếu người dùng không truyền biểu thức
    if (argc == 1) {
        printf("Su dung: expr <bieu thuc hau to>\n");
        printf("Vi du: ./expr 2 3 4 + \\*\n");
        return 1;
    }

    // 2. Duyệt qua từng argument, bắt đầu từ argv[1]
    for (i = 1; i < argc; i++) {
        
        /* * Kiểm tra xem tham số là số hay toán tử:
         * - Nếu ký tự đầu là số (isdigit).
         * - Hoặc nếu ký tự đầu là dấu '-' và ký tự thứ hai là số (số âm).
         */
        if (isdigit(argv[i][0]) || (argv[i][0] == '-' && isdigit(argv[i][1]))) {
            // Chuyển chuỗi thành số thực và đẩy vào ngăn xếp
            push(atof(argv[i]));
        } 
        else {
            // 3. Xử lý các phép toán bằng cách lấy toán hạng từ Stack
            switch (argv[i][0]) {
                case '+':
                    push(pop() + pop());
                    break;
                case '*':
                case 'x': // Hỗ trợ ký tự 'x' thay cho '*' để tránh lỗi shell wildcard
                    push(pop() * pop());
                    break;
                case '-':
                    /* * Phép trừ không có tính giao hoán: 
                     * Lấy số bị trừ (op2) ra trước, sau đó lấy số trừ và thực hiện phép tính.
                     */
                    op2 = pop(); 
                    push(pop() - op2);
                    break;
                case '/':
                    op2 = pop();
                    if (op2 != 0.0) {
                        push(pop() / op2);
                    } else {
                        printf("Loi: Phep chia cho 0\n");
                        return 1;
                    }
                    break;
                default:
                    printf("Loi: Toan tu khong hop le '%s'\n", argv[i]);
                    return 1;
            }
        }
    }
    
    // 4. In ra kết quả cuối cùng (phần tử còn lại duy nhất trong Stack)
    printf("Ket qua: %.8g\n", pop());
    
    return 0;
}
