class Solution:
     def minEatingSpeed(self, piles: List[int], h: int) -> int:

        # Không gian tìm kiếm [1, max(piles)]
        left  = 1
        right = max(piles)
        result = right

        while left <= right:
            mid = left + (right - left) // 2

            # Tính tổng giờ cần với tốc độ mid
            total_hours = sum(math.ceil(pile / mid) for pile in piles)

            if total_hours <= h:
                result = mid       # mid hợp lệ, thử nhỏ hơn
                right  = mid - 1
            else:
                left = mid + 1     # mid không đủ, tăng lên

        return result
        