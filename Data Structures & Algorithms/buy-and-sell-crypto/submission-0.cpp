/* THUẬT TOÁN PREFIX MINIMUM + GREEDY
 PREFIX MINIUM :  minPrice = giá nhó nhất từ đầu tới i ;
 GREEDY : giả sử bán hôm nay , dùng giá thấp nhất trước đó để maximize profit */

/* CẤU TRÚC TƯ DUY CHUNG : 
  minValue = INF;
  answer = 0 ;
  for each element
  {
     cập nhật minValue
     tính lời nếu chọn current làm điểm bán
     cập nhật answer
  }   */

class Solution 
{
public:
    int maxProfit(vector<int>& prices) 
    {
        // lưu giá nhỏ nhất từng gặp
        int minPrice = INT_MAX;
        // lưu lợi nhuận lớn nhất
        int maxProfit = 0  ;
        // duyệt từng ngày
        for(int price : prices)
        {
            // nếu giá hiện tại nhỏ hơn minPrice => tìm đc ngày mua tốt hơn
           if(price < minPrice)
           {
            minPrice = price;
           }
           // nếu bán hôm nay : profit = giá hôm qua - giá mua thấp nhất trước đó
           int profit = price - minPrice;
           // nếu profit tốt hơn đáp án cũ -> cập 
           if(profit > maxProfit)
           {
            maxProfit = profit;
           }
        }
        return maxProfit;
    }
};
