// ====== THUÂT TOÁN TÌM KIẾM NHỊ PHÂN NÂNG CAO =======
/* Quy luật: k tăng → giờ ăn giảm (hoặc bằng) k giảm → giờ ăn tăng (hoặc bằng)
→ Hàm F(k) = "có ăn hết trong h giờ không?" là HÀM ĐƠN ĐIỆU
→ Áp dụng Binary Search được!  */

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
DẤU HIỆU NHẬN BIẾT:  Binary Search On Answer  
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
📌 "Tìm giá trị NHỎ NHẤT / LỚN NHẤT thỏa điều kiện"
📌 Có hàm kiểm tra F(x) = true/false
📌 F(x) có tính đơn điệu:
   x tăng → F(x) chỉ đổi từ false→true (hoặc true→false)
   không bao giờ đổi ngược lại
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

✅ Koko Eating Bananas      Tìm tốc độ ăn nhỏ nhất
✅ Minimum Ship Capacity    Tìm tải trọng tàu nhỏ nhất
✅ Split Array Largest Sum  Tìm tổng lớn nhất nhỏ nhất
✅ Capacity to Ship Packages trong D ngày
✅ Find the Smallest Divisor Given a Threshold
✅ Magnetic Force Between Balls
✅ Sqrt(x)                   Tìm căn bậc hai nguyên
✅ Allocate Books            Tìm tổng trang tối thiểu */

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
TEMPLATE CHUNG BINARY SEARCH ON ANSWER
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
 Bài toán: Tìm giá trị NHỎ NHẤT x trong [lo, hi] sao cho condition(x) = true

bool condition(int x) 
{
    // Kiểm tra x có thỏa điều kiện không?
    // Hàm này phải có tính đơn điệu!
}

int binarySearchOnAnswer() 
{
    int left  = /* giá trị nhỏ nhất có thể //;
    int right = /* giá trị lớn nhất có thể //;
    int result = right; // hoặc left tùy bài

    while (left <= right) 
    {
        int mid = left + (right - left) / 2;

        if (condition(mid)) 
        {
            result = mid;      // mid hợp lệ, lưu lại
            right = mid - 1;   // thử tìm nhỏ hơn
        } else 
        {
            left = mid + 1;    // mid không đủ, tăng lên
        }
    }
    return result;
} */


class Solution 
{
public:
// ════════════════════════════════════════════
// HÀM HELPER: Kiểm tra tốc độ k có đủ không?
// ════════════════════════════════════════════

// ① Hàm canFinish: với tốc độ k quả/giờ,
//    Koko có ăn hết tất cả trong h giờ không?
bool canFinish(vector<int>& piles, int k, int h) 
{

    // ② Đếm tổng số giờ cần thiết với tốc độ k
    long long totalHours = 0;

    for (int pile : piles) 
    {
        // ③ Số giờ để ăn hết 1 đống = ceil(pile / k)
        //    Trong C++: ceil(a/b) = (a + b - 1) / b  (với số nguyên dương)
        //
        //    Tại sao không dùng (double)pile/k rồi ceil()?
        //    → Dùng số nguyên nhanh hơn và tránh lỗi làm tròn float
        //
        //    Ví dụ pile=7, k=4:
        //    (7 + 4 - 1) / 4 = 10 / 4 = 2  ✅ (ceil(7/4)=2)
        //    Ví dụ pile=8, k=4:
        //    (8 + 4 - 1) / 4 = 11 / 4 = 2  ✅ (ceil(8/4)=2)
        totalHours += (pile + k - 1) / k;
    }

    // ④ Nếu tổng giờ ≤ h → tốc độ k đủ để ăn hết → true
    return totalHours <= h;
}

// ════════════════════════════════════════════
// HÀM CHÍNH: Binary Search on Answer
// ════════════════════════════════════════════

    int minEatingSpeed(vector<int>& piles, int h) 
    {

    // ⑤ Xác định không gian tìm kiếm [left, right]
    //    left  = 1        (tốc độ tối thiểu có thể)
    //    right = max(piles) (tốc độ tối đa cần thiết)
    //
    //    Tại sao right = max(piles)?
    //    Vì k > max(piles) vô nghĩa: ăn hết đống lớn nhất trong 1 giờ
    //    → k lớn hơn không giúp tiết kiệm thêm giờ nào
    int left  = 1;
    int right = *max_element(piles.begin(), piles.end());

    // ⑥ Lưu kết quả tốt nhất (k nhỏ nhất hợp lệ tìm được)
    //    Khởi tạo = right vì chắc chắn right luôn hợp lệ
    int result = right;

    // ⑦ Binary Search tìm k NHỎ NHẤT thỏa canFinish
    while (left <= right) 
    {

        // ⑧ mid = tốc độ ăn thử nghiệm ở giữa khoảng
        int mid = left + (right - left) / 2;

        // ⑨ Kiểm tra: tốc độ mid có đủ ăn hết trong h giờ không?
        if (canFinish(piles, mid, h)) 
        {
            // ✅ mid hợp lệ → lưu vào result (có thể là đáp án)
            //    Nhưng có thể có k nhỏ hơn mid vẫn hợp lệ
            //    → Thu hẹp tìm kiếm về nửa TRÁI [left, mid-1]
            result = mid;
            right = mid - 1;

        } else 
        {
            // ✗ mid không đủ → cần tốc độ lớn hơn
            //    → Thu hẹp tìm kiếm về nửa PHẢI [mid+1, right]
            left = mid + 1;
        }
    }

    // ⑩ result là k nhỏ nhất thỏa mãn điều kiện
    return result;
}
};
/*
┌──────────────────────┬──────────────────────────────┐
│  Binary Search thường│  Binary Search on Answer     │
├──────────────────────┼──────────────────────────────┤
│ Tìm trên DỮ LIỆU     │ Tìm trên KHÔNG GIAN ĐÁP ÁN   │
│ Mảng phải có sẵn     │ Không cần mảng               │
│ Target cho trước     │ Tự xác định [left, right]    │
│ So sánh trực tiếp    │ Dùng hàm condition(mid)      │
│ Search a 2D Matrix   │ Koko Eating Bananas          │
│ Find in Rotated Array│ Min Ship Capacity            │
└──────────────────────┴──────────────────────────────┘ */
