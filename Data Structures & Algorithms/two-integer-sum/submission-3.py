# Hash Map (Two Pass)
# Time complexity : O(n)
# Space complexity : O(n)
class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        indices = {}
        #  enumerate(nums): biến đổi danh sách NUMS thành ds các ô dạng : (CHỈ SỐ , GIÁ TRỊ)
        # i , n : n hứng lấy giá trị thực sự của ptu 
        for i ,n in enumerate(nums):
            indices[n] = i
        for i , n in enumerate(nums):
            diff = target - n 
            if diff in indices and indices[diff] != i:
                return [i , indices[diff]]
        return []