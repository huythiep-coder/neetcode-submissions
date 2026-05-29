class Solution 
{
    fun minWindow(s: String, t: String): String 
    {

        // ==========================================
        // XỬ LÝ TRƯỜNG HỢP ĐẶC BIỆT
        // ==========================================
        // Nếu s hoặc t rỗng → không có kết quả → trả về ""
        // Ví dụ: s="" hoặc t="" → return ""
        if (s.isEmpty() || t.isEmpty()) return ""

        // ==========================================
        // BƯỚC 1: Đếm số lần xuất hiện của từng ký tự trong t
        // ==========================================
        // HashMap lưu dạng: ký tự → số lần cần có
        // Ví dụ: t = "ABC"
        // → need = {A:1, B:1, C:1}
        //
        // Ví dụ: t = "AABC"
        // → need = {A:2, B:1, C:1}
        val need = HashMap<Char, Int>()
        for (ch in t) 
        {
            need[ch] = (need[ch] ?: 0) + 1
            // ?: 0 nghĩa là: nếu chưa có thì lấy 0, rồi cộng 1
        }

        // ==========================================
        // BƯỚC 2: Chuẩn bị các biến cho Sliding Window
        // ==========================================

        // "window" lưu số lần xuất hiện của từng ký tự
        // trong cửa sổ hiện tại (đoạn đang xét trong s)
        val window = HashMap<Char, Int>()

        // "have"  = số ký tự đã đủ số lượng yêu cầu
        // "needs" = tổng số ký tự PHÂN BIỆT cần có trong t
        // Ví dụ: t = "AABC" → needs = 3 (cần A, B, C)
        var have  = 0
        val needs = need.size

        // Lưu kết quả tốt nhất tìm được
        // result[0] = vị trí bắt đầu
        // result[1] = vị trí kết thúc
        var result    = intArrayOf(-1, -1)
        var resultLen = Int.MAX_VALUE  // độ dài nhỏ nhất, ban đầu = vô cực

        // Con trỏ trái của cửa sổ, bắt đầu tại vị trí 0
        var left = 0

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

        for (right in s.indices) 
        {

            // Lấy ký tự tại vị trí right
            val ch = s[right]

            // Thêm ký tự này vào cửa sổ hiện tại
            window[ch] = (window[ch] ?: 0) + 1

            // Kiểm tra: ký tự này có trong t không?
            // Và số lượng trong window đã đủ so với need chưa?
            // Nếu đủ → tăng "have" lên 1
            //
            // Ví dụ: need[A]=2, window[A]=2 → đủ rồi → have++
            // Ví dụ: need[A]=2, window[A]=1 → chưa đủ → không tăng
            if (need.containsKey(ch) && window[ch] == need[ch]) 
            {
                have++
            }

            // ==========================================
            // BƯỚC 4: Khi cửa sổ đã có ĐỦ mọi ký tự của t
            // → Thử thu hẹp từ bên TRÁI để tìm cửa sổ NHỎ HƠN
            // ==========================================
            while (have == needs) 
            {

                // Tính độ dài cửa sổ hiện tại
                val currentLen = right - left + 1

                // Nếu cửa sổ này nhỏ hơn kết quả tốt nhất trước đó
                // → Cập nhật kết quả
                if (currentLen < resultLen) 
                {
                    resultLen = currentLen
                    result[0] = left   // lưu vị trí bắt đầu
                    result[1] = right  // lưu vị trí kết thúc
                }

                // Thu hẹp cửa sổ: bỏ ký tự bên TRÁI ra
                val leftChar = s[left]
                window[leftChar] = window[leftChar]!! - 1

                // Nếu bỏ đi làm số lượng ký tự đó KHÔNG ĐỦ nữa
                // → Giảm "have" xuống 1
                // → Vòng while sẽ dừng vì have < needs
                if (need.containsKey(leftChar) && window[leftChar]!! < need[leftChar]!!) 
                {
                    have--
                }

                // Dịch con trỏ trái sang phải
                left++
            }
        }

        // ==========================================
        // BƯỚC 5: Trả về kết quả
        // ==========================================
        // Nếu result[0] == -1 → không tìm được cửa sổ nào → trả về ""
        // Ngược lại → cắt chuỗi s từ result[0] đến result[1]
        return if (result[0] == -1) ""
        else s.substring(result[0], result[1] + 1)
    }
}
/* VD s = "ADOBECODEBANC", t = "ABC":
need   = {A:1, B:1, C:1} → needs = 3
window = {}
have   = 0

→ right=0 (A): window={A:1}, A đủ → have=1
→ right=1 (D): window={A:1,D:1}
→ right=2 (O): window={A:1,D:1,O:1}
→ right=3 (B): window={...,B:1}, B đủ → have=2
→ right=4 (E): window={...,E:1}
→ right=5 (C): window={...,C:1}, C đủ → have=3 ✅

have==needs → Thu hẹp từ trái:
  cửa sổ "ADOBEC" dài 6 → lưu result
  bỏ A → window[A]=0 < need[A]=1 → have=2 → dừng

→ Tiếp tục mở rộng right...
→ Cuối cùng tìm được "BANC" dài 4 ✅

KẾT QUẢ: "BANC" 🎯 */