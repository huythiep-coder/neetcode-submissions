// 
class Solution
 {
public:
    vector<vector<int>> threeSum(vector<int>& nums)
     {
        vector<vector<int>> result;
        int n = nums.size();
        if (n < 3) 
        {
            return result;
        }
        // sắp xếp lại mảng
        sort(nums.begin(), nums.end());
        // chừa chỗ cho 2 phần từ (left và right)
        for (int i = 0; i < n - 2; ++i)
         {
            // tối ưu hóa : số đầu > 0 -> ko có tổng = 0 
            if (nums[i] > 0)
            {
                break;
            }
            // tối ưu : bỏ qua các số nums[i] trùng lặp để tránh bộ ba trùng lặp
            if (i > 0 && nums[i] == nums[i - 1])
            {
                continue;
            }
            int left = i + 1;
            int right = n - 1;
            while (left < right)
            {
                int sum = nums[i] + nums[left] + nums[right]; // Tính tổng 3 số luôn cho dễ
                if (sum == 0)
                 {
                    // đẩy vào sau vector result
                    result.push_back({nums[i], nums[left], nums[right]});
                    // Tối ưu : bỏ qua các số left và right trùng lặp 
                    while (left < right && nums[left] == nums[left + 1]) 
                    {
                        left++;
                    }
                    while (left < right && nums[right] == nums[right - 1])
                    {
                        right--;
                    }
                    left++;
                    right--;
                } else if (sum < 0)
                {
                    left++;
                } else 
                { 
                    right--;
                }
            }
        }
        return result;
    }
};
