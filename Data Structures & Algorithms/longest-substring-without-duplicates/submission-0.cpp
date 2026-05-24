class Solution 
{
public:
    int lengthOfLongestSubstring(string s) 
    {
        // hộp lưu trữ các kí tự động đang có trong cửa sổ
        unordered_set<char> set;
        // con trỏ trái
        int L = 0 ;
        // biến lưu độ dài chuỗi con lớn nhất
        int max_len = 0 ;
        // con trỏ R liên tục mở rộng cửa sổ về bên phải
        for(int R = 0 ; R < s.length() ; R ++)
        {
            // nếu kí tự s[R] đã tồn tại trong cửa sổ hiện tại -> thu hẹp cửa sổ từ bên trái[tăng L] cho đến khi s[R] ko còn bị trùng
            while(set.find(s[R])  != set.end())
            {
                // xóa kí tự biên trái ra khỏi set
                set.erase(s[L]);
                // dịch biên trái sang phải
                L ++;
            }
            // sau khi đảm bảo cửa sổ ko còn kí tự trùng -> thêm s[R] vào Set
            set.insert(s[R]);
            // cập nhật độ dài lớn nhất của cửa sổ(R - L + 1 chính là số ptu hiện tại)
            max_len = max(max_len , R - L + 1);
        }
        return max_len;
    }
};
