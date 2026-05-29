class Solution 
{
    fun longestConsecutive(nums: IntArray): Int 
    {
        
        // ==========================================
        // BƯỚC 1: Chuyển mảng thành HashSet
        // ==========================================
        // HashSet giúp tìm kiếm 1 phần tử trong O(1)
        // Thay vì dùng vòng lặp tìm kiếm O(n)
        // Ví dụ: nums = [100, 4, 200, 1, 3, 2]
        // → numSet = {100, 4, 200, 1, 3, 2}
        val numSet = nums.toHashSet()
        
        // Biến lưu độ dài dãy liên tiếp DÀI NHẤT tìm được
        // Ban đầu = 0 vì chưa tìm được dãy nào
        var longest = 0
        
        // ==========================================
        // BƯỚC 2: Duyệt qua từng số trong HashSet
        // ==========================================
        for (num in numSet) 
        {
            
            // ------------------------------------------
            // TRICK QUAN TRỌNG:
            // Chỉ bắt đầu đếm khi "num" là số ĐẦU TIÊN
            // của 1 dãy liên tiếp
            // 
            // Cách nhận biết số đầu tiên:
            // → Không tồn tại số (num - 1) trong HashSet
            //
            // Ví dụ: numSet = {1, 2, 3, 4, 100, 200}
            // - num = 1 → không có 0 trong set → LÀ số đầu ✅
            // - num = 2 → có 1 trong set       → BỎ QUA    ✋
            // - num = 3 → có 2 trong set       → BỎ QUA    ✋
            // - num = 4 → có 3 trong set       → BỎ QUA    ✋
            // ------------------------------------------
            if (!numSet.contains(num - 1)) 
            {
                
                // Bắt đầu đếm từ chính số này
                var currentNum = num  // số hiện tại đang xét
                var streak = 1        // độ dài dãy, bắt đầu = 1
                
                // ------------------------------------------
                // BƯỚC 3: Đếm dãy liên tiếp
                // Cứ tìm xem số tiếp theo (currentNum + 1)
                // có tồn tại trong set không
                // Nếu có → tăng streak lên 1, tiếp tục tìm
                // Nếu không → dừng lại
                //
                // Ví dụ bắt đầu từ num = 1:
                // streak=1: có số 2? ✅ → currentNum=2, streak=2
                // streak=2: có số 3? ✅ → currentNum=3, streak=3
                // streak=3: có số 4? ✅ → currentNum=4, streak=4
                // streak=4: có số 5? ❌ → DỪNG, streak=4
                // ------------------------------------------
                while (numSet.contains(currentNum + 1)) {
                    currentNum++  // sang số tiếp theo
                    streak++      // tăng độ dài dãy lên 1
                }
                
                // ------------------------------------------
                // BƯỚC 4: Cập nhật kết quả
                // So sánh dãy vừa tìm với dãy dài nhất trước đó
                // Giữ lại cái nào DÀI HƠN
                //
                // Ví dụ: longest=1, streak=4
                // → maxOf(1, 4) = 4 → longest = 4 ✅
                // ------------------------------------------
                longest = maxOf(longest, streak)
            }
        }
        
        // ==========================================
        // BƯỚC 5: Trả về kết quả
        // ==========================================
        // Đây là độ dài của dãy liên tiếp dài nhất
        return longest
    }
}
/* VD NUMS = [100 , 4 , 200 , 1 , 3 , 2]: 
numSet = {100, 4, 200, 1, 3, 2}

❓ num=100 → có 99 không? ❌ → bắt đầu đếm
   └─ có 101? ❌ → streak=1, longest=1

❓ num=4   → có 3 không?  ✅ → BỎ QUA

❓ num=200 → có 199 không? ❌ → bắt đầu đếm
   └─ có 201? ❌ → streak=1, longest=1

❓ num=1   → có 0 không?  ❌ → bắt đầu đếm
   └─ có 2? ✅ → có 3? ✅ → có 4? ✅ → có 5? ❌
   └─ streak=4, longest=4 ✅

❓ num=3   → có 2 không?  ✅ → BỎ QUA
❓ num=2   → có 1 không?  ✅ → BỎ QUA

KẾT QUẢ: 4 🎯 */