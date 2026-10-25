class Solution {
public:
    bool hasDuplicate(vector<int>& nums) {
        sort(nums.begin() , nums.end());
        for(int i = nums.size() - 1 ; i >= 1 ; i --)
        {
            if(nums[i] == nums[i - 1])
            {
                return true;
            }
        }
        return false;
    }
};