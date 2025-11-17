# Bài Tập Tô Màu Đồ Thị - TH08

## Mô tả
Chương trình tô màu đồ thị sử dụng thuật toán Greedy để tìm cách tô màu đồ thị với số màu ít nhất có thể.

## Cấu trúc file
- `tomau.cpp`: File source code chính (sử dụng thuật toán Greedy - nhanh)
- `tomau_optimal.cpp`: File source code tối ưu (sử dụng Backtracking - tìm số màu tối thiểu chính xác)
- `inp.txt`: File input chứa thông tin đồ thị (test case 1)
- `inp2.txt`: File input test case 2
- `inp3.txt`: File input test case 3
- `out.txt`: File output chứa kết quả tô màu

## Định dạng Input (inp.txt)
Dòng đầu tiên: `V E` (V = số đỉnh, E = số cạnh)
E dòng tiếp theo: mỗi dòng chứa 2 số `u v` biểu thị một cạnh nối đỉnh u và v

Ví dụ:
```
5 6
1 2
1 3
2 3
2 4
3 5
4 5
```

## Định dạng Output (out.txt)
Dòng đầu tiên: Số màu đã sử dụng
V dòng tiếp theo: Mỗi dòng ghi "Dinh i: Mau j" (đỉnh i được tô màu j)

Ví dụ:
```
3
Dinh 1: Mau 1
Dinh 2: Mau 2
Dinh 3: Mau 3
Dinh 4: Mau 1
Dinh 5: Mau 2
```

## Cách biên dịch và chạy

### Trên Windows (MinGW/GCC):
```bash
g++ -o tomau.exe tomau.cpp
tomau.exe
```

### Trên Linux/Mac:
```bash
g++ -o tomau tomau.cpp
./tomau
```

## Thuật toán

### tomau.cpp - Greedy Algorithm (Nhanh)
1. Tô màu đỉnh đầu tiên bằng màu 0
2. Với mỗi đỉnh tiếp theo:
   - Kiểm tra các màu đã được sử dụng bởi các đỉnh kề
   - Chọn màu nhỏ nhất chưa được sử dụng bởi các đỉnh kề
   - Tô màu cho đỉnh đó

**Ưu điểm**: Chạy nhanh, O(V + E)
**Nhược điểm**: Không đảm bảo tìm được số màu tối thiểu

### tomau_optimal.cpp - Backtracking Algorithm (Tối ưu)
1. Thử tô màu với số màu tăng dần từ 1
2. Với mỗi số màu, sử dụng backtracking để tìm cách tô màu hợp lệ
3. Dừng khi tìm được cách tô màu đầu tiên

**Ưu điểm**: Tìm được số màu tối thiểu chính xác (chromatic number)
**Nhược điểm**: Chạy chậm hơn, độ phức tạp cao hơn

## Lưu ý
- Đồ thị được đánh số từ 1 trong file input, nhưng chương trình xử lý từ 0
- Sử dụng `tomau.cpp` cho đồ thị lớn cần tốc độ
- Sử dụng `tomau_optimal.cpp` khi cần tìm số màu tối thiểu chính xác
- Có 3 file test case mẫu: `inp.txt`, `inp2.txt`, `inp3.txt`

