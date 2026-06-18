class Solution {
public:
    int findMin(vector<int> &nums) {
        // std::min_element : tìm số nhỏ nhất trong 1 danh sách
        return *min_element(nums.begin() , nums.end());
    }
};
