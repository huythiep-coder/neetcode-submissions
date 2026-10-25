// DÙNG BẢNG ĐẾM TẦN SUẤT 
class Solution 
{
public:
    bool isAnagram(string s, string t) 
    {
        // nếu độ dài khác nhau -> false
        if(s.length() != t.length())
        {
            return false;
        }
        // tạo mảng tần suất cho 26 chữ cái
        int count[26] = {0};
        // đếm tần suất cho chuỗi s
        for(char c : s)
        {
            // trong C++ , mỗi kí tự dc coi như 1 số nguyên(mã ASCII)
            // c - 'a' sẽ cho ra chỉ số kí tự trong mảng(0-25)
            count[c - 'a'] ++;
        }
        // giảm đếm với chuỗi t và kiểm tra , so sánh với chuỗi 
        for(char c : t)
        {
            count [c - 'a'] --;
            // nếu bộ đếm trở nên âm -> kí tự này xuất hiện trong t nhiều lần hơn trong s 
            if(count[c -'a'] < 0)
            {
                return false;
            }
        }
        return true;
    }
};
