// TƯ DUY CỐT LÕI : Tất cả hoán vị đều có cùng bộ kí tự với cùng tần suất
class Solution 
{
   public:
    bool checkInclusion(string s1, string s2) 
    {
        // ① Nếu s1 dài hơn s2 → không thể chứa hoán vị → false ngay
        if (s1.size() > s2.size()) return false;

        // ② Tạo 2 mảng đếm tần suất ký tự (26 chữ cái a-z)
        //    count1: đếm ký tự của s1 (cố định, không đổi)
        //    count2: đếm ký tự của cửa sổ hiện tại trong s2
        int count1[26] = {0};
        int count2[26] = {0};

        int n1 = s1.size();  // ③ Kích thước cửa sổ = độ dài s1
        int n2 = s2.size();

        // ④ Đếm tần suất từng ký tự trong s1
        //    Đồng thời khởi tạo cửa sổ đầu tiên trong s2 (n1 ký tự đầu)
        for (int i = 0; i < n1; i++) 
        {
            count1[s1[i] - 'a']++;  // vd: 'a'-'a'=0, 'b'-'a'=1, 'z'-'a'=25
            count2[s2[i] - 'a']++;
        }

        // ⑤ Hàm kiểm tra 2 mảng đếm có giống nhau không
        //    Nếu count1 == count2 → cửa sổ hiện tại là hoán vị của s1
        auto isMatch = [&]() 
        {
            for (int i = 0; i < 26; i++)
                if (count1[i] != count2[i]) return false;
            return true;
        };

        // ⑥ Kiểm tra cửa sổ đầu tiên (n1 ký tự đầu của s2)
        if (isMatch()) return true;

        // ⑦ Trượt cửa sổ từ vị trí n1 đến hết s2
        //    right = ký tự MỚI đưa vào cửa sổ (bên phải)
        //    left  = ký tự BỊ LOẠI khỏi cửa sổ (bên trái)
        for (int right = n1; right < n2; right++) 
        {
            // ⑧ Thêm ký tự mới vào cửa sổ (mở rộng bên phải)
            count2[s2[right] - 'a']++;

            // ⑨ Xác định ký tự bên trái bị loại ra
            //    Khi right = n1   → left = 0
            //    Khi right = n1+1 → left = 1  ...
            int left = right - n1;
            count2[s2[left] - 'a']--;  // ⑩ Loại ký tự cũ ra khỏi cửa sổ

            // ⑪ Kiểm tra cửa sổ mới có là hoán vị không
            if (isMatch()) return true;
        }

        // ⑫ Duyệt hết s2 mà không tìm thấy → false
        return false;
    }
};
/* Minh họa trực quan với s1 = "ab" , s2 = "eidbaoo"

count1 (s1="ab"):  {a:1, b:1, others:0}  ← CỐ ĐỊNH

Bước 0 - Cửa sổ khởi tạo:
s2: [e i] d b a o o o
count2: {e:1, i:1}  ≠ count1  ✗

Bước 1 - right=2, loại s2[0]='e', thêm s2[2]='d':
s2:  e [i d] b a o o o
count2: {i:1, d:1}  ≠ count1  ✗

Bước 2 - right=3, loại s2[1]='i', thêm s2[3]='b':
s2:  e  i [d b] a o o o
count2: {d:1, b:1}  ≠ count1  ✗

Bước 3 - right=4, loại s2[2]='d', thêm s2[4]='a':
s2:  e  i  d [b a] o o o
count2: {b:1, a:1}  = count1 {a:1,b:1}  ✓ → TRUE!
Độ phức tạp

⏱ Time: O(n1 + n2) — duyệt s1 một lần + duyệt s2 một lần
💾 Space: O(1) — 2 mảng cố định 26 ô, không phụ thuộc độ dài chuỗi */