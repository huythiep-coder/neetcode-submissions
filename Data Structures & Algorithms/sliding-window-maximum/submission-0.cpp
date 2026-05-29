class Solution
{
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) 
    {

        // ==========================================
        // XỬ LÝ TRƯỜNG HỢP ĐẶC BIỆT
        // ==========================================
        // Nếu mảng rỗng → trả về mảng rỗng
        if (nums.empty()) return {};

        // ==========================================
        // BƯỚC 1: Chuẩn bị
        // ==========================================
        // "result" lưu giá trị MAX của từng cửa sổ
        // Ví dụ: nums=[1,3,-1,-3,5,3,6,7], k=3
        // → result sẽ là [3,3,5,5,6,7]
        vector<int> result;

        // "dq" là Deque (hàng đợi 2 đầu)
        // Lưu CHỈ SỐ (index) của các phần tử
        // Luôn giữ thứ tự GIẢM DẦN theo GIÁ TRỊ
        // → Phần tử ở ĐẦU deque luôn là MAX của cửa sổ hiện tại
        //
        // Hình dung deque như 1 hàng có 2 cửa:
        //
        //   [front] ← ← ← ← ← ← [back]
        //   (đầu)                 (đuôi)
        //   (MAX)              (mới thêm)
        deque<int> dq;  // lưu index, không phải giá trị

        // ==========================================
        // BƯỚC 2: Duyệt qua từng phần tử trong mảng
        // ==========================================
        for (int right = 0; right < nums.size(); right++) 
        {

            // ------------------------------------------
            // XỬ LÝ ĐUÔI DEQUE:
            // Bỏ các phần tử NHỎ HƠN nums[right] ra khỏi đuôi
            // Vì chúng không bao giờ là MAX nữa
            //
            // Ví dụ: dq=[5,3,1], thêm 4 vào
            // → 1 < 4 → bỏ 1
            // → 3 < 4 → bỏ 3
            // → 5 > 4 → dừng
            // → dq=[5,4]
            // ------------------------------------------
            while (!dq.empty() && nums[dq.back()] < nums[right]) 
            {
                dq.pop_back();  // bỏ phần tử ở đuôi
            }

            // Thêm index hiện tại vào đuôi deque
            dq.push_back(right);

            // ------------------------------------------
            // XỬ LÝ ĐẦU DEQUE:
            // Kiểm tra phần tử ở ĐẦU deque có còn
            // nằm trong cửa sổ [right-k+1 ... right] không?
            // Nếu không → bỏ ra khỏi đầu
            //
            // Ví dụ: k=3, right=5
            // → Cửa sổ hợp lệ: index từ 3 đến 5
            // → Nếu dq.front() = 2 → nằm ngoài cửa sổ → bỏ
            // ------------------------------------------
            if (dq.front() < right - k + 1) 
            {
                dq.pop_front();  // bỏ phần tử ở đầu
            }

            // ------------------------------------------
            // LƯU KẾT QUẢ:
            // Chỉ bắt đầu lưu khi cửa sổ đã đủ k phần tử
            // Cửa sổ đủ k phần tử khi right >= k - 1
            //
            // Ví dụ: k=3
            // → right=0,1: cửa sổ chưa đủ 3 phần tử → chưa lưu
            // → right=2  : cửa sổ đủ 3 phần tử → bắt đầu lưu
            //
            // nums[dq.front()] = giá trị MAX của cửa sổ hiện tại
            // (vì đầu deque luôn là index của phần tử lớn nhất)
            // ------------------------------------------
            if (right >= k - 1) 
            {
                result.push_back(nums[dq.front()]);
            }
        }

        // ==========================================
        // BƯỚC 3: Trả về mảng kết quả
        // ==========================================
        return result;
    }
};