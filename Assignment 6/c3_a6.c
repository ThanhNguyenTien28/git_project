/******************************************************************************
 * FILE NAME: postfix_expr.c
 *
 * PROGRAM DESCRIPTION
 * ----------------------------------------------------------------------------
 * This program evaluates a postfix (Reverse Polish Notation - RPN) expression
 * passed through command line arguments.
 *
 * The program uses a stack to store operands and performs arithmetic
 * operations such as:
 *
 *      +   addition
 *      -   subtraction
 *      *   multiplication ( Use x or "*" if * causes an error )
 *      /   division
 *
 *
 * USAGE
 * ----------------------------------------------------------------------------
 *
 * Compile:
 *      gcc expr.c -o expr
 *
 * Run:
 *      ./expr 2 3 4 + *
 *
 * Example:
 *      ./expr 2 3 4 + *
 *      Result: 14
 *
 *
 * IMPORTANT NOTE ABOUT "*" OPERATOR
 * ----------------------------------------------------------------------------
 *
 * In Linux/Unix terminal, the "*" character is a special wildcard symbol.
 *
 * Example:
 *      ./expr 2 3 4 + *
 *
 * The shell may expand "*" into file names in the current directory,
 * causing incorrect program behavior.
 *
 *
 * To avoid this problem, use one of the following methods:
 *
 * Method 1: Escape the character
 *      ./expr 2 3 4 + \*
 *
 * Method 2: Use quotes
 *      ./expr 2 3 4 + "*"
 *
 * Method 3: Use letter 'x' instead of '*'
 *      ./expr 2 3 4 + x
 *
 *
 * The program supports both:
 *
 *      '*'  -> multiplication
 *      'x'  -> multiplication
 *
 *
 * CODE GUIDELINE
 * ----------------------------------------------------------------------------
 *
 * 1. GENERAL RULES
 *    - Follow structured programming.
 *    - Each function performs a single task.
 *    - Avoid unnecessary global variables.
 *    - Validate command line arguments.
 *    - Handle stack overflow and underflow.
 *
 *
 * 2. STACK MANAGEMENT
 *    - push() adds a value to stack
 *    - pop() removes a value from stack
 *    - Stack size must not exceed MAXVAL
 *
 *
 * 3. ERROR HANDLING
 *    - Stack overflow must print error
 *    - Stack underflow must print error
 *    - Division by zero must stop program
 *    - Invalid operator must stop program
 *
 *
 * 4. OPERATOR RULE
 *    +   addition
 *    -   subtraction
 *    *   multiplication
 *    x   multiplication (backup operator)
 *    /   division
 *
 *
 * 5. COMMAND LINE INPUT RULE
 *    - Numbers are read using atof()
 *    - Operators are read using switch-case
 *    - Expression must be postfix
 *
 *
 * 6. MEMORY RULE
 *    - Stack uses static array
 *    - No dynamic memory allocation
 *    - Safe and predictable behavior
 *
 *
 * FUNCTION OVERVIEW
 * ----------------------------------------------------------------------------
 *
 * push(double f)
 *      Add value to stack
 *
 * pop(void)
 *      Remove and return top value
 *
 * main(int argc, char *argv[])
 *      Read arguments
 *      Process postfix expression
 *      Print result
 *
 *
 * LIMITATION
 * ----------------------------------------------------------------------------
 *
 * - Maximum stack size: 100
 * - Only basic arithmetic operations supported
 * - Input must be postfix format
 *
 *
 * AUTHOR: Thanh Nguyen Tien
 * VERSION: 1.0
 * DATE: 2026
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h> /* Cho hàm atof() */
#include <ctype.h>

#define MAXVAL 100 // Độ sâu tối đa của ngăn xếp

int sp = 0;          // Con trỏ ngăn xếp (stack pointer)
double val[MAXVAL];  // Mảng chứa các giá trị của ngăn xếp

/* Hàm đẩy một giá trị kiểu double vào đỉnh ngăn xếp */
void push(double f) {
    if (sp < MAXVAL) {
        val[sp++] = f;
    } else {
        printf("Loi: Ngan xep day, khong the day them gia tri %g\n", f);
    }
}

/* Hàm lấy và trả về giá trị ở đỉnh ngăn xếp */
double pop(void) {
    if (sp > 0) {
        return val[--sp];
    } else {
        printf("Loi: Ngan xep trong (Thieu toan hang)\n");
        return 0.0;
    }
}

int main(int argc, char *argv[]) {
    double op2;
    int i;

    // Kiem tra neu khong co tham so truyen vao
    if (argc == 1) {
        printf("Su dung: expr <bieu thuc hau to>\n");
        printf("Vi du: ./expr 2 3 4 + \\*\n");
        return 1;
    }

    // Duyệt qua từng argument, bắt đầu từ argv[1] (bỏ qua tên file thực thi)
    for (i = 1; i < argc; i++) {
        // Kiểm tra xem argument là số dương, số âm hay là toán tử
        if (isdigit(argv[i][0]) || (argv[i][0] == '-' && isdigit(argv[i][1]))) {
            // Chuyển chuỗi thành số thực và đẩy vào ngăn xếp
            push(atof(argv[i]));
        } else {
            // Xử lý các phép toán
            switch (argv[i][0]) {
                case '+':
                    push(pop() + pop());
                    break;
                case '*':
                case 'x': // Hỗ trợ thêm phím 'x' đề phòng lỗi ký tự '*' trong terminal
                    push(pop() * pop());
                    break;
                case '-':
                    op2 = pop(); // Phải lấy op2 ra trước vì phép trừ không có tính giao hoán
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
    
    // In ra kết quả cuối cùng nằm trong ngăn xếp
    printf("Ket qua: %.8g\n", pop());
    return 0;
}
