class Solution 
{
    public int longestConsecutive(int[] nums) 
    {
        // Bước 1: Cho tất cả số vào HashSet để tìm kiếm O(1)
        HashSet<Integer> numSet = new HashSet<>();
        for (int num : nums) 
        {
            numSet.add(num);
        }

        int longest = 0;

        // Bước 2: Duyệt từng số
        for (int num : numSet) 
        {
            // Chỉ bắt đầu đếm nếu đây là số ĐẦU của dãy
            // (tức là không có số num-1 trong set)
            if (!numSet.contains(num - 1)) 
            {
                int currentNum = num;
                int streak = 1;

                // Đếm dãy liên tiếp từ num trở đi
                while (numSet.contains(currentNum + 1)) 
                
                {
                    currentNum++;
                    streak++;
                }

                longest = Math.max(longest, streak);
            }
        }

        return longest;
    }
}
/*    VD : NUMS = [100 , 4 , 200 , 1 , 3 , 2]:
numSet = {100, 4, 200, 1, 3, 2}

- Gặp 100 → không có 99 → bắt đầu đếm: 100, 101? ❌ → streak = 1
- Gặp 4   → có 3 rồi    → bỏ qua ✋
- Gặp 200 → không có 199 → bắt đầu đếm: 200, 201? ❌ → streak = 1
- Gặp 1   → không có 0  → bắt đầu đếm: 1→2→3→4→5? ❌ → streak = 4 ✅
- Gặp 3   → có 2 rồi    → bỏ qua ✋
- Gặp 2   → có 1 rồi    → bỏ qua ✋

Kết quả: 4 */