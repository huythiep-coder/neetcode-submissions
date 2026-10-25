//  THUẬT TOÁN SORTING(sắp xếp)

class Solution
{
public:
    bool isAnagram(string s, string t)
    {
        // nếu độ dài khác nhau -> ko thể là đảo chữ
        if(s.length() != t.length())
        {
            return false;
        }
        // sắp xếp các kí tự trong 2 chuỗi
        sort(s.begin() , s.end());
        sort(t.begin() , t.end());
        return s == t;
    }
};
