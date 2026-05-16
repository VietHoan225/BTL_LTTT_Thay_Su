# Information Theory & Coding — Đồ án nhóm

Dự án triển khai các thuật toán mã hóa, giải mã và kiểm tra mã lỗi theo chuẩn ICPC. Chương trình có thể xuất kết quả ở ba chế độ: **Standard** (đáp án gọn), **Detailed** (lời giải từng bước), và **MCQ** (câu hỏi trắc nghiệm).

Ngoài chạy dòng lệnh với file test, có **giao diện web** (Flask) trong `app.py` + `templates/` để nhập liệu và xem kết quả.

---

## Yêu cầu hệ thống

| Thành phần | Mục đích |
|------------|----------|
| **GCC** (g++) hỗ trợ **C++17** | Biên dịch `main.cpp` |
| **Python 3.8+** (khuyến nghị 3.10+) | Chạy server web `app.py` |
| **pip** | Cài đặt Flask |

Kiểm tra nhanh phiên bản trong terminal:

- Linux / macOS / Git Bash:
  ```bash
  g++ --version
  python3 --version
  ```
- Windows (CMD / PowerShell):
  ```bash
  g++ --version
  python --version
  ```

---

## Cấu trúc thư mục

| Đường dẫn | Mô tả |
|-----------|--------|
| `main.cpp` | Mã nguồn C++ chính (thuật toán). |
| `app.py` | Ứng dụng Flask; gọi binary `./main` qua `stdin`/`stdout`. |
| `templates/index.html` | Giao diện web. |
| `tests/` | 100 bộ testcase (mỗi bộ một thư mục). |
| `tests/{ID}/{ID}.in` | Input của testcase `ID` (1–100). |
| `tests/{ID}/{ID}.out` | **Đáp án chuẩn** (không được ghi đè khi chạy thử). |
| `README.md` | Hướng dẫn này. |

---

## Cài đặt

### 1. Lấy mã nguồn

Clone repository hoặc giải nén archive vào một thư mục, ví dụ:

- **Linux/macOS/Git Bash:** `cd /đường/dẫn/tới/BTL_LTTT_Thay_Su`
- **Windows (CMD/PowerShell):** `cd D:\du-an\BTL_LTTT_Thay_Su`

Tất cả lệnh bên dưới giả định bạn đang đứng **ở thư mục gốc chứa** `main.cpp`, `app.py`, `templates/`, `tests/`.

### 2. Biên dịch chương trình C++

```bash
g++ -O3 -std=c++17 main.cpp -o main
```

Sau khi biên dịch thành công, trong thư mục gốc sẽ có file thực thi `main` (trên Windows sau bước tương tự thường là `main.exe` — khi đó cần sửa đường dẫn trong `app.py` cho phù hợp).

### 3. Cài đặt Flask (chỉ cần nếu dùng giao diện web)

Cách đơn giản (cài cho user hiện tại):

```bash
python3 -m pip install --user flask
```

Hoặc dùng môi trường ảo (khuyến nghị nếu nhiều dự án):

```bash
python3 -m venv .venv
source .venv/bin/activate   # Linux / macOS
# .venv\Scripts\activate    # Windows (cmd/PowerShell)
pip install flask
```

---

## Chạy project

### A. Chạy từ dòng lệnh (stdin/stdout)

**Không** chuyển hướng output thẳng vào `tests/{ID}/{ID}.out` — đó là file đáp án để đối chiếu.

Chạy một testcase và lưu kết quả tạm để so sánh:
- Linux:
```bash
./main < tests/1/1.in > /tmp/run1.out
diff -u tests/1/1.out /tmp/run1.out
```
- Windows Command Prompt:
```bash
main.exe < tests\1\1.in > run1.out
fc tests\1\1.out run1.out
```

- Nếu không có khác biệt: output trùng với file đáp án đính kèm.
- Có thể thay `1` bằng bất kỳ `ID` từ `1` đến `100`.

**Lưu ý khi so sánh với `tests/{ID}/{ID}.out`:**

- Các file `.out` trong `tests/` là **bản tham chiếu** (có thể được tạo khi format in chi tiết / MCQ khác phiên bản hiện tại). Nếu `diff` báo khác to bộ nhưng thuật toán vẫn đúng, cần **tạo lại expected** hoặc đối chiếu thủ công phần kết quả số học/LZW/Hamming.
- Các testcase có **MODE = 2 (MCQ)** dùng xáo trộn thứ tự đáp án ngẫu nhiên, nên **không** kỳ vọng khớp từng byte với một file `.out` cố định trên mọi lần chạy.

Chỉ xem output trên terminal (không lưu file):

```bash
./main < tests/1/1.in
```

### B. Chạy giao diện web (Flask)

1. Đảm bảo đã biên dịch xong và tồn tại file `./main` **cùng thư mục** với `app.py`.
2. Khởi động server:

```bash
python3 app.py
```

3. Mở trình duyệt tại: **http://127.0.0.1:5000**

Trang web gửi request tới endpoint `/run`; backend gọi `./main` với input đã định dạng. Nếu báo lỗi kiểu “không tìm thấy `./main`”, quay lại bước biên dịch hoặc kiểm tra đang chạy `python3 app.py` đúng thư mục gốc dự án.

---

## Định dạng input (tóm tắt)

- Dòng đầu: số nguyên `T` — số testcase trong file.
- Mỗi testcase bắt đầu bằng hai số `TYPE` và `MODE`:
  - **TYPE `1`**: Mã hóa / giải mã **Arithmetic coding**
  - **TYPE `2`**: **LZW**
  - **TYPE `3`**: **Khoảng cách Hamming** giữa các từ mã
- **MODE**: `0` = Standard (ICPC), `1` = Detailed, `2` = MCQ

Chi tiết từng loại (chuỗi, danh sách mã, v.v.) xem trong các file `tests/{ID}/{ID}.in` và trong `main.cpp`.

---

