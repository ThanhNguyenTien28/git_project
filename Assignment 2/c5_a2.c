// In phan tu dinh stack ma khong xoa
void show_top(void) {
    if (sp > 0) printf("Stack head: %g\n", stack[sp-1]); 
    else printf("Error: Stack empty\n"); 
}

// Nvoid duplicate(void) han ban phan tu dinh stack 
void duplicate(void) {
    if (sp > 0) push(stack[sp-1]); 
    else printf("Error: Stack empty\n"); 
}

// Hoan doi hai phan tu tren cung 
void swap(void) {
    if (sp >= 2) {
        double temp = stack[sp-1]; 
        stack[sp-1] = stack[sp-2]; 
        stack[sp-2] = temp; 
    } else printf("Error: Not enough elements\n"); 
}

// Xoa toan bo Stack 
void clear_stack(void) {
    sp = 0; 
}
