//Chuyển đổi vòng lặp for thành while

int factorial(int n) {
    int i, ret = 1;
    
    i = 2; // Khởi tạo (Initialization) đặt trước while
    while (i <= n) { // Điều kiện (Condition)
        ret *= i;
        i++; // Bước tăng (Increment) đặt ở cuối thân vòng lặp
    }
    
    return ret;
}


//Chuyển đổi vòng lặp do-while thành while

int sample_geometric_rv(double p) {
    double q;
    int n = 0;

    /* 
       Để tương đương với do-while, ta thực hiện gán q lần đầu 
       hoặc khởi tạo q sao cho q >= p để vòng lặp chạy ít nhất 1 lần.
    */
    q = rand_double(); // Thực hiện lần đầu tiên tương đương khối 'do'
    n++;// Tăng n cho lần chạy đầu tiên này

    while (q >= p) { // Kiểm tra điều kiện
        q = rand_double();
        n++;
    }

    return n;
}
