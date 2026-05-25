// TƯ DUY - SLIDING WINDOW
class Solution 
{
   public:
    int characterReplacement(string s, int k) 
    {
        // ① Mảng đếm số lần xuất hiện của từng ký tự trong cửa sổ hiện tại
        //    freq['A'] = số lần 'A' xuất hiện, freq['B'] = số lần 'B', ...
        int freq[26] = {0};
        // ② Con trỏ trái của cửa sổ
        int left = 0;  
        // ③ Số lần xuất hiện của ký tự NHIỀU NHẤT trong cửa sổ
        int maxFreq = 0;  
        // ④ Kết quả: độ dài cửa sổ hợp lệ dài nhất
        int maxLen = 0;   

        // ⑤ Con trỏ phải quét từ đầu đến cuối chuỗi
        for (int right = 0; right < s.size(); right++) 
        {
            // ⑥ Thêm ký tự s[right] vào cửa sổ, tăng đếm lên 1
            // mẹo chuyển kí tự thành chỉ số : 'A' - 'A' = 0 , 'B' - 'A' = 1 , 'C' - 'A' = 2 , ...
            freq[s[right] - 'A']++; 

            // ⑦ Cập nhật maxFreq: ký tự nào xuất hiện nhiều nhất trong cửa sổ?
            //    s[right]-'A' chuyển 'A'->0, 'B'->1, ..., 'Z'->25
            maxFreq = max(maxFreq, freq[s[right] - 'A']);

            // ⑧ Kiểm tra cửa sổ có hợp lệ không?
            //    windowSize = right - left + 1
            //    Nếu > k → cửa sổ KHÔNG hợp lệ → thu nhỏ lại
            int windowSize = right - left + 1;
            // Công thức trái tim của bài : Số ký tự cần thay = windowSize - maxFreq
            if (windowSize - maxFreq > k) 
            {
                // ⑨ Thu nhỏ cửa sổ: loại bỏ ký tự s[left] ra khỏi cửa sổ
                freq[s[left] - 'A']--;

                // ⑩ Dịch con trỏ trái sang phải 1 bước
                left++;
            }

            // ⑪ Sau bước trên, cửa sổ luôn có kích thước hợp lệ (hoặc vừa được fix)
            //    Cập nhật kết quả = max của windowSize hiện tại
            maxLen = max(maxLen, right - left + 1);
        }

        return maxLen;  // ⑫ Trả về độ dài dài nhất tìm được
    }
};

/* Minh họa với "AABABBA" , k = 1

                                                               Minh họa chạy tay với "AABABBA",
 +> right = 0 : cửa sổ = [A]     freq = {A : 1} maxFreq = 1 size = 1 thay = 0 ✓ 
 maxLen = 1 
 +> right = 1: cửa sổ = [AA]     freq = {A : 2} maxFreq = 2 size = 2 thay = 0 ✓ 
 maxLen = 2 
 +> right = 2: cửa sổ = [AAB]    freq = {A : 2, B : 1} maxFreq = 2 size = 3 thay = 1 ✓ 
 maxLen = 3 
 +> right = 3 : cửa sổ = [AABA]  freq = {A : 3, B : 1} maxFreq = 3 size = 4 thay = 1 ✓ 
 maxLen = 4 
 +> right = 4 : cửa sổ = [AABAB]  freq = {A : 3, B : 2} maxFreq = 3 size = 5 thay = 2 ✗
         → thu nhỏ : loại A[0],left = 1,cửa sổ = [ABAB] size = 4 thay = 1 ✓ 
 maxLen = 4 
 +> right = 5 : cửa sổ = [ABABB]  freq = {A : 2, B : 3} maxFreq = 3 size = 5 thay = 2 ✗
         → thu nhỏ : loại A[1],left = 2,cửa sổ = [BABB] size = 4 thay = 1 ✓ 
 maxLen = 4 
 +> right = 6 : cửa sổ = [BABBA]  freq = {A : 2, B : 3} maxFreq = 3 size = 5 thay = 2 ✗
         → thu nhỏ : loại B[2],left = 3,cửa sổ = [ABBA] size = 4 thay = 1 ✓ 
 maxLen = 4

 Kết quả : 4 ✅

 Độ phức tạp

⏱ Time : O(n) — mỗi ký tự chỉ vào /ra cửa sổ đúng 1 lần
💾 Space : O(1) — mảng freq cố định 26 ô  */
