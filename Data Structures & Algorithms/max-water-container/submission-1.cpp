// 2 CON TRỎ - "TƯ DUY THAM LAM VÀ LOẠI TRỪ "
class Solution 
{
public:
    int maxArea(vector<int>& heights) 
    {
     int max_area = 0 ;
     int left = 0 ;
     int right = heights.size() - 1;
     while(left < right)
     {
        // đề bài : chiều cao bị giới hạn bởi cột thấp 
        int h = min(heights[left] , heights[right]);
        // chiều rộng là khoảng cách giữa 2 con trỏ
        int width = right - left;
        // cập nhật kỉ lục 
        max_area = max(max_area , h * width);
        // MỤC TIÊU : tìm được chiều cao bù chiều rộng bị giảm
        // nếu bên trái thấp hơn -> giữ lại cột phải và di chuyển cột trái vào trong
        if(heights[left] < heights[right])
        {
            left ++;
        }
        // nếu bên phải thấp hơn hoặc bằng bên trái -> di chuyển cột phải vào trong
        else
        {
            right --;
        }
     }   
     return max_area;
    }
};
