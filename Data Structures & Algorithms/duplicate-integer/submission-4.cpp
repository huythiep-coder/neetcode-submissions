class Solution {
public:
    bool hasDuplicate(vector<int>& nums) {
        unordered_set <int> seen;
        for(int i = 0 ; i < nums.size() ; i ++)
        {
            if(seen.count(nums[i]))
            {
                return true;
            }
            seen.insert(nums[i]);
        }
        return false;
    }
};
/*
     push_back(): thêm 1 ptu vào cuối vector
     pop_back() :  xóa ptu cuối cùng của vector
     clear() :  xóa toàn bộ phần tử trong 
     II > HASHING 
     unordered_map < int , int>mp;   lưu  : Key -> Value
     mp.count() : ktra tồn tại
     mp.erase() : xóa

     unordered_set : chỉ cần biết có hoặc không
*/