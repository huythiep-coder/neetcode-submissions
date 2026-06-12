class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        prevMap = {} # Khởi tạo một Hash Map trống
        
        for i, n in enumerate(nums):
            diff = target - n # Tính số còn thiếu để đạt được target
            
            # Nếu số còn thiếu đã xuất hiện trong những số trước đó
            if diff in prevMap:
                # Trả về vị trí của số còn thiếu và vị trí của số hiện tại
                return [prevMap[diff], i]
            
            # NẾU CHƯA THẤY: Lưu số hiện tại và vị trí của nó vào Map để dùng cho các số sau
            prevMap[n] = i 