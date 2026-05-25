# BÁO CÁO ĐỒ ÁN NHÓM - MÔN LÝ THUYẾT THÔNG TIN (LTTT)
* **Tên dự án:** Công cụ mô phỏng Mã hóa Số học, LZW và Khoảng cách Hamming 
* **Mã môn học:** ELE1319 - Lý thuyết thông tin
* **Lớp:** D24CTCN01-B
* **Repository Git:** [https://github.com/VietHoan225/BTL_LTTT_Thay_Su](https://github.com/VietHoan225/BTL_LTTT_Thay_Su)

---

## 1. THÀNH VIÊN NHÓM & VAI TRÒ CHÍNH

| STT | Họ và Tên | Mã Sinh Viên | Lớp | 
|-----|-----------|--------------|-----|
| 1 | Viết Hoàn | B24DCCN229 | D24CTCN01-B |
| 2 | Nguyễn Đức Anh | B24DCCN028 | D24CTCN01-B |
| 3 | Nguyễn Văn Quang | B24DCCN478 | D24CTCN01-B |

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
g++ -O3 -std=c++17 main.cpp -o main # Linux / macOS
# g++ -O3 -std=c++17 main.cpp -o main.exe   # Windows (cmd/PowerShell)
```

Sau khi biên dịch thành công, trong thư mục gốc sẽ có file thực thi `main` (trên Windows sau bước tương tự sẽ là `main.exe`)

### 3. Cài đặt Flask 

Khuyến nghị sử dụng môi trường ảo (venv) để tránh xung đột thư viện:
- Linux: 
```bash
python3 -m venv .venv
source .venv/bin/activate
pip install flask
```
- Windows (Command Prompt - CMD):
```
python -m venv .venv
.venv\Scripts\activate.bat
pip install flask
```

- Windows (PowerShell):
Nếu PowerShell chặn không cho chạy script kích hoạt, hãy dùng lệnh sau để khởi chạy:

```
python -m venv .venv
powershell -ExecutionPolicy Bypass -File .venv\Scripts\Activate.ps1
pip install flask
```

---

## 6. CHẠY PROJECT

1. Đảm bảo đã biên dịch xong và tồn tại file `./main` **cùng thư mục** với `app.py`.
2. Khởi động server:

```bash
python3 app.py # Linux
# python app.py # Windows (cmd/PowerShell)
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

