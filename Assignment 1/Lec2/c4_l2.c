//Viết một vòng lặp tương đương với vòng lặp for mà không sử dụng && hoặc || .



for (khoi_tao; dieu_kien_1 && dieu_kien_2; buoc_tang) {
    /* Thân vòng lặp */
}


khoi_tao; // Đặt phần khởi tạo trước vòng lặp
while (dieu_kien_1) { // Giữ điều kiện chính ở đây
    if (!(dieu_kien_2)) { // Kiểm tra điều kiện phụ bằng lệnh if
        break; // Thoát vòng lặp nếu điều kiện phụ không thỏa mãn
    }

    /* Thân vòng lặp */

    buoc_tang; // Đặt bước tăng ở cuối thân vòng lặp
}
