/* ======= THUẬT TOÁN TÌM KIẾM NHỊ PHÂN ========
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
DẠNG 1: TÌM KIẾM TRÊN MẢNG/MA TRẬN ĐÃ SẮP XẾP
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
✅ Binary Search (classic)
✅ Search a 2D Matrix         ← BÀI NÀY
✅ Search in Rotated Array    (mảng bị xoay)
✅ Find Minimum in Rotated Array
✅ Find Peak Element

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
DẠNG 2: TÌM BIÊN (FIRST/LAST POSITION)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
✅ Find First and Last Position of Element
✅ Search Insert Position
✅ Count occurrences of element

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
DẠNG 3: TÌM KIẾM TRÊN KHÔNG GIAN GIÁ TRỊ (Binary Search on Answer)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
✅ Koko Eating Bananas        (tìm tốc độ tối thiểu)
✅ Minimum Capacity Ships     (tìm tải trọng tối thiểu)
✅ Split Array Largest Sum    (tìm tổng lớn nhất tối thiểu)
✅ Sqrt(x)                    (tìm căn bậc hai nguyên)

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
DẤU HIỆU NHẬN BIẾT bài dùng Binary Search:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  📌 Dữ liệu đã sắp xếp (mảng, ma trận, khoảng giá trị)
  📌 Tìm kiếm trong O(log n)
  📌 "Tìm giá trị nhỏ nhất/lớn nhất thỏa điều kiện"
  📌 Không gian tìm kiếm có thể chia đôi sau mỗi bước */

/*/  CÁC DẠNG BÀI ÁP DỤNG BINARY SEARCH /*/
/*      ① Tìm CHÍNH XÁC giá trị target
while (left <= right) 
{
    int mid = left + (right - left) / 2;
    if (nums[mid] == target) return mid;
    else if (nums[mid] < target) left = mid + 1;
    else right = mid - 1;
}
return -1; // không tìm thấy

      ② Tìm vị trí TRÁI NHẤT (first occurrence)
while (left < right) 
{
    int mid = left + (right - left) / 2;
    if (nums[mid] < target) left = mid + 1;
    else right = mid; // giữ mid vì có thể là đáp án
}
return left;

      ③ Tìm vị trí PHẢI NHẤT (last occurrence)
while (left < right) 
{
    int mid = left + (right - left + 1) / 2; // +1 tránh vòng lặp vô hạn
    if (nums[mid] > target) right = mid - 1;
    else left = mid;
}
return left; */


class Solution 
{
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) 
    {

    // ════════════════════════════════════════════
    // PHẦN 1: KHỞI TẠO
    // ════════════════════════════════════════════

    // ① Lấy số hàng và số cột của ma trận
    int m = matrix.size();    // số hàng
    int n = matrix[0].size(); // số cột

    // ② Thiết lập Binary Search trên "mảng 1D ảo"
    //    left = index đầu tiên = 0
    //    right = index cuối cùng = m*n - 1
    //    Ví dụ ma trận 3×4: left=0, right=11
    int left  = 0;
    int right = m * n - 1;

    // ════════════════════════════════════════════
    // PHẦN 2: BINARY SEARCH
    // ════════════════════════════════════════════

    // ③ Vòng lặp Binary Search chuẩn
    //    Điều kiện: còn không gian tìm kiếm (left <= right)
    while (left <= right) 
    {

        // ④ Tính mid = điểm giữa của không gian tìm kiếm hiện tại
        //    Dùng left + (right-left)/2 thay vì (left+right)/2  để tránh tràn số (overflow) khi left+right quá lớn
        int mid = left + (right - left) / 2;

        // ⑤ Chuyển index 1D (mid) → index 2D (row, col)
        //    Đây là bước quan trọng nhất của bài!
        //    row = mid / n  →  phần tử thứ mid nằm ở hàng nào?
        //    col = mid % n  →  phần tử thứ mid nằm ở cột nào?
        //
        //    Ví dụ n=4:
        //    mid=5 → row=5/4=1, col=5%4=1 → matrix[1][1]
        //    mid=9 → row=9/4=2, col=9%4=1 → matrix[2][1]
        int row = mid / n;
        int col = mid % n;
        int val = matrix[row][col]; // ⑥ Giá trị tại vị trí mid

        // ⑦ So sánh val với target — 3 trường hợp:
        if (val == target) 
        {
            // Tìm thấy → trả về true ngay
            return true;

        } else if (val < target) 
        {
            // val nhỏ hơn target → target nằm bên PHẢI mid
            // → Loại bỏ nửa trái, thu hẹp về [mid+1, right]
            left = mid + 1;

        } else 
        {
            // val lớn hơn target → target nằm bên TRÁI mid
            // → Loại bỏ nửa phải, thu hẹp về [left, mid-1]
            right = mid - 1;
        }
    }

    // ⑧ Duyệt hết không gian tìm kiếm mà không tìm thấy → false
    return false;
    }
};
