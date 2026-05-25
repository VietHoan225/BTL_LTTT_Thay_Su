# BÁO CÁO ĐỒ ÁN NHÓM - MÔN LÝ THUYẾT THÔNG TIN (LTTT)
* **Tên dự án:** Công cụ mô phỏng Mã hóa Số học, LZW và Khoảng cách Hamming 
* **Mã môn học:** ELE1319 - Lý thuyết thông tin
* **Lớp:** D24CTCN01-B
* **Repository Git:** [https://github.com/viethoan/BTL_LTTT_Thay_Su](https://github.com/VietHoan225/BTL_LTTT_Thay_Su)

---

## 1. THÀNH VIÊN NHÓM & VAI TRÒ CHÍNH

| STT | Họ và Tên | Mã Sinh Viên | Lớp | 
|-----|-----------|--------------|-----|
| 1 | Viết Hoàn | B24DCCN229 | D24CTCN01-B |
| 2 | Nguyễn Đức Anh | B24DCCN028 | D24CTCN01-B 
| 3 | Nguyễn Văn Quang | B24DCCN478 | D24CTCN01-B 

---

## 2. KIẾN TRÚC THIẾT KẾ DỰ ÁN (DESIGN SYSTEM)

Dự án áp dụng mô hình kiến trúc kết hợp **Hybrid System Architecture (C++ Core Native Execution + Python Web GUI Wrapper)**:

```text
  [Trình Duyệt Web Frontend]
          │       ▲
 (Payload)│       │(HTML Dashboard)
          ▼       │
   [Server Python Flask]  ◄── Môi trường ảo (.venv) cách ly độc lập
          │       ▲
    (stdin)│       │(stdout)  ◄── Giao tiếp liên tiến trình ngầm (IPC - Pipes)
          ▼       │
     [C++ Binary Engine]  ◄── Tối ưu hóa biên dịch -O3 tốc độ cao
```

* **C++ Core Engine (`main.cpp`):** Đảm nhiệm xử lý tính toán cốt lõi.
* **Python Backend Wrapper (`app.py`):** Đóng vai trò là một Lightweight Web Server sử dụng framework Flask. Backend giao tiếp với file thực thi C++ qua cơ chế ống dẫn dòng vào/ra chuẩn (`stdin`/`stdout`) bằng thư viện `subprocess.Popen` an toàn của hệ thống, không mở port hay ghi dữ liệu trung gian ra ổ đĩa, giúp tối ưu hóa bộ nhớ RAM.
* **Frontend Dashboard (`templates/index.html`):** Sử dụng một bộ thông dịch cú pháp (Parser JavaScript) ở phía client để tự động bắt các chuỗi định dạng từ C++ in ra để bọc thành bảng HTML (`<table>`) và các thẻ Card câu hỏi, tách biệt phần hiển thị ra khỏi logic thuật toán giúp giao diện sạch sẽ và hiện đại.

---

## 3. YÊU CẦU HỆ THỐNG

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
```cmd
g++ --version
python --version
``` 
---

## 4. CẤU TRÚC THƯ MỤC

| Đường dẫn | Mô tả |
|-----------|--------|
| `main.cpp` | Mã nguồn C++ chính (thuật toán). |
| `app.py` | Ứng dụng Flask; gọi binary `./main` qua `stdin`/`stdout`. |
| `templates/index.html` | Giao diện web dạng Report Dashboard. |
| `tests/` | 100 bộ testcase (mỗi bộ một thư mục). |
| `tests/{ID}/{ID}.in` | Input của testcase `ID` (1–100). |
| `tests/{ID}/{ID}.out` | **Đáp án chuẩn** (không được ghi đè khi chạy thử). |
| `README.md` | Hướng dẫn sử dụng gốc của project. |

---

## 5. CÀI ĐẶT

### 1. Lấy mã nguồn

Di chuyển vào thư mục gốc của dự án:

- **Linux/macOS/Git Bash:**
```bash
cd /đường/dẫn/tới/BTL_LTTT_Thay_Su
```
- **Windows (CMD/PowerShell):**
```cmd
cd D:\du-an\BTL_LTTT_Thay_Su
```

Tất cả lệnh bên dưới giả định bạn đang đứng **ở thư mục gốc chứa** `main.cpp`, `app.py`, `templates/`, `tests/`.

### 2. Biên dịch chương trình C++

```bash
g++ -O3 -std=c++17 main.cpp -o main
```

Sau khi biên dịch thành công, trong thư mục gốc sẽ có file thực thi `main` (trên Windows sau bước tương tự sẽ là `main.exe`)

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

## 6. CHẠY PROJECT

### A. Chạy từ dòng lệnh (stdin/stdout)

**Không** chuyển hướng output thẳng vào `tests/{ID}/{ID}.out` — đó là file đáp án để đối chiếu.

Chạy một testcase và lưu kết quả tạm để so sánh:
- Linux:
```bash
./main < tests/1/1.in > /tmp/run1.out
diff -u tests/1/1.out /tmp/run1.out
```
- Windows Command Prompt:
```cmd
main.exe < tests\1\1.in > run1.out
fc tests\1\1.out run1.out
```

* Nếu không có khác biệt: output trùng hoàn toàn với file đáp án đính kèm.
* Có thể thay `1` bằng bất kỳ `ID` từ `1` đến `100`.

**Lưu ý khi so sánh với `tests/{ID}/{ID}.out`:**

- Các file `.out` trong `tests/` là **bản tham chiếu** (có thể được tạo khi format in chi tiết / MCQ khác phiên bản hiện tại). Nếu `diff` báo khác toàn bộ cấu trúc chữ nhưng thuật toán vẫn đúng, cần **tạo lại expected** hoặc đối chiếu thủ công phần kết quả số học/LZW/Hamming.
- Các testcase có **MODE = 2 (MCQ)** dùng cơ chế xáo trộn thứ tự đáp án ngẫu nhiên bằng `std::shuffle` kết hợp bộ lọc trùng `std::set`, nên **không** kỳ vọng khớp từng byte với một file `.out` cố định trên mọi lần chạy.

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

3. Mở trình duyệt tại: **[http://127.0.0.1:5000](http://127.0.0.1:5000)**

Trang web gửi request tới endpoint `/run`; backend gọi `./main` với input đã định dạng. Nếu báo lỗi kiểu “không tìm thấy `./main`”, quay lại bước biên dịch hoặc kiểm tra đang chạy `python3 app.py` đúng thư mục gốc dự án.

---

## 7. ĐỊNH DẠNG INPUT (TÓM TẮT)

* Dòng đầu: số nguyên `T` — số testcase trong file.
* Mỗi testcase bắt đầu bằng hai số `TYPE` và `MODE`:
  * **TYPE `1`**: Mã hóa / giải mã **Arithmetic coding**
  * **TYPE `2`**: **LZW**
  * **TYPE `3`**: **Khoảng cách Hamming** giữa các từ mã
* **MODE**: `0` = Standard (ICPC), `1` = Detailed, `2` = MCQ

Chi tiết từng loại (chuỗi, danh sách mã, v.v.) xem trong các file `tests/{ID}/{ID}.in` và trong `main.cpp`.

---

