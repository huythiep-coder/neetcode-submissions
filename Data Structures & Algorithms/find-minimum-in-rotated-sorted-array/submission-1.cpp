// Tìm kiếm nhị phân (Binary Search) cải tiến để giải bài toán: Tìm phần tử nhỏ nhất trong một mảng đã từng được sắp xếp tăng dần nhưng bị xoay vòng (Rotated Sorted Array).
class Solution {
public:
    int findMin(vector<int> &nums) {
        // Tạm thời giả định phần tử đầu tiên là số nhỏ nhất để làm mốc so sánh.
        int res = nums[0];
        int l = 0;
        int r = nums.size() - 1;
        while(l <= r)
        {
            //nếu dãy số được sắp xếp tăng dần -> ptu bên trái chắc chắn nhỏ nhất
            if(nums[l] < nums[r])
            {
                res = min(res , nums[l]);
                break;
            }
            int m = l + (r - l) / 2;
            res = min(res,nums[m]);
            // nửa trái tăng dần đều
            if(nums[m] >= nums[l])
            {
                l = m + 1;
            }
            // nữa trái bất thường
            else
            {
                r = m - 1;
            }
        }
        return res;
    }
};
