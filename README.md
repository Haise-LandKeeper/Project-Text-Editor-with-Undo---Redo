# Mini Text Editor (Console C++)

## Giới thiệu

Mini Text Editor là một ứng dụng chỉnh sửa văn bản chạy trên console Windows, được xây dựng bằng C/C++.  
Project mô phỏng các chức năng cơ bản của một text editor như quản lý file, chỉnh sửa nội dung, undo/redo và lưu lịch sử thao tác.

---

## Tính năng chính

### Quản lý file
- Mở danh sách file `.txt` trong thư mục
- Lưu nội dung vào file
- Tạo file mới
- Tự động tạo thư mục lưu trữ nếu chưa tồn tại

### Chỉnh sửa văn bản
- Thêm nội dung vào văn bản
- Ghi đè toàn bộ nội dung
- Xóa toàn bộ văn bản

### Undo / Redo
- Hoàn tác thao tác trước đó
- Làm lại thao tác đã hoàn tác

### Lịch sử thao tác
- Lưu lại các hành động người dùng đã thực hiện
- Hiển thị dạng bảng

### Hiển thị nội dung
- Xem toàn bộ văn bản ở chế độ full screen
- Hiển thị nội dung nhanh trong giao diện chính

### Thống kê
- Đếm số ký tự trong văn bản

---

## Phím điều khiển

----------------------------------------------
| Phím | Chức năng                           |
|------|-------------------------------------|
| Mũi tên lên / xuống | Di chuyển trong menu |
| Mũi tên trái / phải | Chuyển tab           |
| Enter | Chọn chức năng                     |
| Esc | Thoát chương trình                   |
----------------------------------------------

## Cấu trúc thư mục lưu file

Thư mục sẽ tự động được tạo nếu chưa tồn tại.

---

## Cấu trúc dữ liệu sử dụng

- Stack: Undo / Redo
- Queue: Lưu lịch sử thao tác
- Linked List: Cài đặt Stack và Queue
- Vector: Quản lý danh sách file `.txt`

---

## Công nghệ sử dụng

- C / C++
- Windows API
- Console UI
- STL vector, string
- File handling

---

## Hướng phát triển

- Thêm con trỏ nhập văn bản giống Notepad thật
- Hỗ trợ chỉnh sửa theo từng dòng
- Tìm kiếm và thay thế
- Auto save
- Giao diện không cần clear screen liên tục
- Nâng cấp lên GUI (Qt hoặc SDL)

---

## Mục tiêu dự án

- Luyện tập cấu trúc dữ liệu (Stack, Queue)
- Hiểu quản lý bộ nhớ động
- Thực hành xử lý file
- Xây dựng ứng dụng console hoàn chỉnh

---

## Tác giả

Haise_

---

## Ghi chú

Đây là project học tập, tập trung vào việc áp dụng cấu trúc dữ liệu vào thực tế và xây dựng ứng dụng console có giao diện.
