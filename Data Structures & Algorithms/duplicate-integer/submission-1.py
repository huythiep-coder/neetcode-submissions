# SORTING 
# TIME COMPLEXITY : 0(nlogn)
# SPACE COMPLEXITY : 0(1) or O(n) phụ thuộc vào thuật toán sắp 
class Solution:
    def hasDuplicate(self, nums: List[int]) -> bool:
        nums.sort()
        for i in range(1 , len(nums)):
            if(nums[i] == nums[i - 1]):
                return True
        return False
