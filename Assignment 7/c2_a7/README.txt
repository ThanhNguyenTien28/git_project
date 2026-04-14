HƯỚNG DẪN BIÊN DỊCH VÀ LIÊN KẾT THƯ VIỆN - ASSIGNMENT 7
------------------------------------------------------

1. DANH SÁCH TỆP:
   - hashtable.h : Tệp tiêu đề (Header file) khai báo cấu trúc và API.
   - hashtable.c : Tệp thực thi (Implementation) chứa logic thuật toán.
   - main.c      : Chương trình chính dùng để kiểm thử.

2. CÁC BƯỚC BIÊN DỊCH THƯ VIỆN TĨNH (STATIC LIBRARY):
   Bước 1: Biên dịch hashtable.c thành tệp đối tượng (.o)
      $ gcc -c hashtable.c -o hashtable.o

   Bước 2: Tạo thư viện tĩnh (.a) từ tệp đối tượng
      $ ar rcs libhash.a hashtable.o

   Bước 3: Biên dịch chương trình chính và liên kết với thư viện tĩnh
      $ gcc main.c -L. -lhash -o app_static

   Bước 4: Chạy chương trình
      $ ./app_static

3. CÁC BƯỚC BIÊN DỊCH THƯ VIỆN ĐỘNG (DYNAMIC LIBRARY):
   Bước 1: Biên dịch mã nguồn thành tệp đối tượng không phụ thuộc vị trí (fPIC)
      $ gcc -fPIC -c hashtable.c -o hashtable.o

   Bước 2: Tạo thư viện chia sẻ (.so)
      $ gcc -shared -o libhash.so hashtable.o

   Bước 3: Biên dịch chương trình chính và liên kết với thư viện động
      $ gcc main.c -L. -lhash -o app_dynamic

   Bước 4: Thiết lập đường dẫn thư viện và chạy (Linux)
      $ export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
      $ ./app_dynamic

4. GHI CHÚ:
   - Tham số -L. thông báo cho trình biên dịch tìm thư viện ở thư mục hiện tại.
   - Tham số -lhash yêu cầu liên kết với tệp có tên bắt đầu bằng 'lib' và kết thúc bằng 'hash' (libhash.a hoặc libhash.so).
