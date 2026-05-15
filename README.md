# Information Theory & Coding - Group Project

Dự án triển khai các thuật toán mã hóa, giải mã và kiểm tra mã lỗi theo chuẩn ICPC. Chương trình hỗ trợ xuất output ở 3 chế độ: Standard (đáp án ngắn gọn), Detailed (lời giải tự luận chi tiết từng bước), và MCQ (sinh câu hỏi trắc nghiệm).

## Cấu trúc thư mục
- `main.cpp`: Mã nguồn chính.
- `gen_tests.py`: Script tự động sinh dữ liệu mẫu và kết quả.
- `tests/`: Thư mục chứa 50 bộ testcase.
  - `{ID}/`: Thư mục chứa testcase thứ ID.
    - `{ID}.in`: Dữ liệu đầu vào.
    - `{ID}.out`: Đáp án tương ứng (bao gồm cả lời giải tự luận/trắc nghiệm).
- `README.md`: Hướng dẫn sử dụng và thông tin dự án.

## Hướng dẫn biên dịch và chạy (C++)
Sử dụng compiler chuẩn (GCC) để biên dịch:
```bash
g++ -O3 -std=c++17 main.cpp -o main
```

Cú pháp chạy thử với một bộ test cụ thể (ví dụ test số 1):
```bash
./main < tests/1/1.in > tests/1/1.out
```

## Định dạng Dữ liệu vào (Input Format)
Dòng đầu tiên chứa số nguyên `T` - số lượng testcases trong file.
Mỗi testcase bắt đầu bằng 2 số nguyên `TYPE` và `MODE`:
- `TYPE`:
  - `1`: Mã hóa/Giải mã Số học (Arithmetic Coding)
  - `2`: Mã hóa/Giải mã LZW (Lempel-Ziv-Welch)
  - `3`: Kiểm tra năng lực bộ mã (Khoảng cách Hamming)
- `MODE`:
  - `0`: Standard ICPC Output (Chỉ in kết quả)
  - `1`: Detailed Output (In lời giải tự luận từng bước)
  - `2`: MCQ Output (Sinh câu hỏi trắc nghiệm)