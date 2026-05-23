// THUẬT TOÁN BRUTE FORCE
// lượng nước tại cột i = min(max[left] , max[right]) - height[i];
class Solution {
public:
    int trap(vector<int>& height) 
    {
        if(height.empty())
        {
            return 0;
        }
        int n = height.size();
        int res = 0 ;
        for(int i = 0 ; i < n ; i ++)
        {
            int leftMax = height[i];
            int rightMax = height[i];
            // so sánh các cột bên trái i với chính nó
            for(int j = 0 ; j < i ; j ++)
            {
                leftMax = max(leftMax , height[j]);
            }
            // so sánh các cột bên phải i với chính nó
            for(int j = i + 1 ; j < n ; j ++)
            {
                rightMax = max(rightMax , height[j]);
            }
          res += min(leftMax , rightMax) - height[i];
        }
        return res;
    }
};
