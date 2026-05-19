// VÉT CẠN (BRUTE FORCE)

class Solution
{
public:
    int maxArea(vector<int>& heights) 
    {
        int max_area = 0 ;
        int n = heights.size();
        for(int i = 0 ; i < n - 1 ; ++i)
        {
            for(int j = i + 1 ; j < n ; ++j)
            {
                // do đề bài yêu cầu chiều cao bị giới hạn bởi cột thấp hơn
                int h = min(heights[i] , heights[j]);
                // chiều rộng = khoảng cách giữa 2 cột
                int width = j - i;
                int current_area = h * width;
                // cập nhật kỉ 
                max_area = max(max_area , current_area);
            }
        }
        return max_area;
    }
};
