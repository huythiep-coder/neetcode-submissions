/*  SLIDING WINDOW
     nếu window hiện tại hợp lệ -> mở rộng
     nếu ko hợp lệ -> thu nhỏ
    + liên tiếp
    +subarray / substring : mảng(chuỗi) liên tiếp
    + tối ưu trên đoạn : dài nhất , ngắn nhất ,...*/
/*
   TEMPLATE CODE :
     left = 0 ;
     for right
     {
        thêm phần tử 
        while(window invalid)
        {
            bỏ bên trái
            left ++
        }
        cập nhật answer
     } */ 
     
class Solution 
{
public:
    int maxProfit(vector<int>& prices) 
    {
      // con trỏ trái : ngày mua
        int left = 0 ;
      // con trỏ phải : ngày bán
        int right = 1 ;
        int max_p = 0 ;
      // trượt con trỏ R cho đến khi đi hết mảng
        while(right < prices.size())
        {
          // giá mua < giá bán -> trường hợp có lợi nhuận
          if(prices[left] < prices[right])
          {
            int current_profit = prices[right] - prices[left];
            // cập nhật lợi nhuận lớn nhất
            max_p = max(max_p , current_profit);
          }
          // trường hợp lỗ hoặc hòa vốn -> tìm mức giá thấp hơn để mua vào
          else
          {
            // trượt con trỏ L đến vị trí R hiện tại để làm điểm mua mới
            left = right;
          }
          // luôn dịch chuyển con trỏ phải để thăm dò
          right ++;
        }
        return max_p;
    }
};
