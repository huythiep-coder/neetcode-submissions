// KĨ THUẬT TWO POINTERS

class Solution {
   public:
    bool isPalindrome(string s) {
        int left = 0;
        int right = s.length() - 1;
        while (left < right) {
// ko có left < right -> left và right truy cập vượt phạm vi -> 🐧
            while (left < right && !isalnum(s[left])) left++;
            while (left < right && !isalnum(s[right])) right--;
            if (tolower(s[left]) != tolower(s[right])) return false;
            left ++;
            right --;
        }
        return true;
    }
};

/*
+> Dạng cùng chiều : Nhanh - Chậm
+> Dạng cửa sổ trượt
+> Dạng 2 mảng độc lập / Trộn mảng
+> Dạng phân hoạch / Đổi chỗ vùng dữ liệu
*/