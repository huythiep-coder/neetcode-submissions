/* PREFIX MINIUM
   khi duyệt tới i : giữ giá trị nhỏ nhất từ đầu tới i
   + maximize current - previous
   + cần min/max trước current
   + điều kiện : i < j
   */
/* TEMPLATE CODE :
    minValue = INF;
    for each x
    {
      minValue = min(minValue , x);
      ans = max (ans , x - minValue);
    }
*/

class Solution 
{
public:
    int maxProfit(vector<int>& prices) 
    {
        int minPrice = INT_MAX;
        int ans = 0 ;
        for(int price : prices)
        {
            minPrice = min(minPrice , price);
            ans = max(ans , price - minPrice);
        }
        return ans;
    }
};
