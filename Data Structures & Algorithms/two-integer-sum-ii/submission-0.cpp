// Thuật toán 2 con trỏ : Dạng 2 con trỏ ngược 

class Solution 
{
public:
    vector<int> twoSum(vector<int>& numbers, int target)
    {
        int left = 0 ;
        int right = numbers.size() - 1;
        while(left < right)
        {
            int sum = numbers[left] + numbers[right];
            if(sum == target)
            {
                return {left + 1 , right + 1}; // leetcode yêu cầu chỉ số từ 1 
            }
            else if(sum < target)
            {
                left ++;
            }
            else
               right --;
        }
        return {};
    }
};
