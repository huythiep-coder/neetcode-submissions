class Solution 
{
public:
    string minWindow(string s, string t)
    {
        // ==========================================
        // XỬ LÝ TRƯỜNG HỢP ĐẶC BIỆT
        // ==========================================
        // Nếu s hoặc t rỗng → không có kết quả → trả về ""
        if (s.empty() || t.empty()) return "";

        // ==========================================
        // BƯỚC 1: Đếm số lần xuất hiện của từng ký tự trong t
        // ==========================================
        // unordered_map lưu dạng: ký tự → số lần cần có
        // Ví dụ: t = "ABC"
        // → need = {A:1, B:1, C:1}
        //
        // Ví dụ: t = "AABC"
        // → need = {A:2, B:1, C:1}
        unordered_map<char, int> need;
        for (char ch : t) 
        {
            need[ch]++;
            // Nếu chưa có key này → tự tạo = 0, rồi cộng 1
        }

        // ==========================================
        // BƯỚC 2: Chuẩn bị các biến cho Sliding Window
        // ==========================================

        // "window" lưu số lần xuất hiện của từng ký tự
        // trong cửa sổ hiện tại (đoạn đang xét trong s)
        unordered_map<char, int> window;

        // "have"  = số ký tự đã ĐỦ số lượng yêu cầu
        // "needs" = tổng số ký tự PHÂN BIỆT cần có trong t
        // Ví dụ: t = "AABC" → needs = 3 (cần A, B, C)
        int have  = 0;
        int needs = need.size();

        // Lưu vị trí bắt đầu và độ dài cửa sổ tốt nhất
        int start     = 0;           // vị trí bắt đầu kết quả
        int minLen    = INT_MAX;     // độ dài nhỏ nhất, ban đầu = vô cực
        // INT_MAX là số nguyên LỚN NHẤT trong C++

        // Con trỏ trái của cửa sổ, bắt đầu tại vị trí 0
        int left = 0;

        // ==========================================
        // BƯỚC 3: Dịch chuyển con trỏ PHẢI qua từng ký tự
        // ==========================================
        // Cửa sổ sẽ trông như thế này:
        //
        //   s = A B C D E F G H
        //       ↑           ↑
        //      left        right
        //      (trái)      (phải)
        //
        // → Mở rộng right sang phải để tìm đủ ký tự
        // → Thu hẹp left sang phải để tìm cửa sổ nhỏ nhất

        for (int right = 0; right < s.size(); right++) 
        {

            // Lấy ký tự tại vị trí right
            char ch = s[right];

            // Thêm ký tự này vào cửa sổ hiện tại
            window[ch]++;

            // Kiểm tra: ký tự này có trong t không?
            // Và số lượng trong window đã đủ so với need chưa?
            // Nếu đủ → tăng "have" lên 1
            //
            // Ví dụ: need[A]=2, window[A]=2 → đủ rồi → have++
            // Ví dụ: need[A]=2, window[A]=1 → chưa đủ → không tăng
            if (need.count(ch) && window[ch] == need[ch]) 
            {
                have++;
                // need.count(ch) kiểm tra ch có trong need không
            }

            // ==========================================
            // BƯỚC 4: Khi cửa sổ đã có ĐỦ mọi ký tự của t
            // → Thử thu hẹp từ bên TRÁI để tìm cửa sổ NHỎ HƠN
            // ==========================================
            while (have == needs) 
            {

                // Tính độ dài cửa sổ hiện tại
                int currentLen = right - left + 1;

                // Nếu cửa sổ này nhỏ hơn kết quả tốt nhất trước đó
                // → Cập nhật kết quả
                if (currentLen < minLen) 
                {
                    minLen = currentLen;
                    start  = left;  // lưu vị trí bắt đầu
                }

                // Thu hẹp cửa sổ: bỏ ký tự bên TRÁI ra
                char leftChar = s[left];
                window[leftChar]--;

                // Nếu bỏ đi làm số lượng ký tự đó KHÔNG ĐỦ nữa
                // → Giảm "have" xuống 1
                // → Vòng while sẽ dừng vì have < needs
                if (need.count(leftChar) && window[leftChar] < need[leftChar]) 
                {
                    have--;
                }

                // Dịch con trỏ trái sang phải
                left++;
            }
        }

        // ==========================================
        // BƯỚC 5: Trả về kết quả
        // ==========================================
        // Nếu minLen vẫn = INT_MAX → không tìm được → trả về ""
        // Ngược lại → cắt chuỗi s từ vị trí start, độ dài minLen
        return minLen == INT_MAX ? "" : s.substr(start, minLen);
        // substr(vị_trí_bắt_đầu, độ_dài)
    }
};