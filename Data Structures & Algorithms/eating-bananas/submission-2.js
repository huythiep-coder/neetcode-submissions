class Solution 
{
    /**
     * @param {number[]} piles
     * @param {number} h
     * @return {number}
     */
    minEatingSpeed(piles, h) 
    {

        // Hàm kiểm tra tốc độ k có ăn hết trong h giờ không
        const canFinish = (k) => 
        {
            let totalHours = 0;
            for (const pile of piles) 
            {
                totalHours += Math.ceil(pile / k);
            }
            return totalHours <= h;
        };

        // Binary Search trên [1, max(piles)]
        let left   = 1;
        let right  = Math.max(...piles);
        let result = right;

        while (left <= right) 
        {
            const mid = Math.floor(left + (right - left) / 2);

            if (canFinish(mid)) 
            {
                result = mid;
                right  = mid - 1;
            } else 
            {
                left = mid + 1;
            }
        }

        return result;
    }
}