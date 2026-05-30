// Thuật toán Hash Set(0(n))
class Solution {
public:
    bool hasDuplicate(vector<int>& nums) {
        unordered_set<int> seen;
        /* for-each :
         for (int i = 0 ; i < nums.size() ; i ++)
        {
            int x = nums[i];
        }
        */

        for(int x : nums)
        {
            // nếu tìm thấy giá trị x tồn tại trong mảng
            if(seen.count(x))
            {
                return true;
            }
            // nếu ko tìm thấy thì lưu vào
            seen.insert(x);
        }
        return false;
    }
};