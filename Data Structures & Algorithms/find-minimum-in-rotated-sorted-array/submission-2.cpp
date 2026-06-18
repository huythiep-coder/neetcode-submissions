// mục đích là thu hẹp phạm vi để tìm điểm đặc biệt / tìm ranh giới
class Solution {
public:
    int findMin(vector<int> &nums) {
        int l = 0 , r = nums.size() - 1;
        while(l < r)
        {
            int m = l + (r - l) / 2;
            if(nums[m] < nums[r])
            {
                // khả năng chính nums[m] chính là số nhỏ 
                r = m ;
            }
            else
            {
                l = m + 1;
            }
        }
        return nums[l];
    }
};

