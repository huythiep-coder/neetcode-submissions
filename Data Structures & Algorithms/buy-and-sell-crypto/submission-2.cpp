/* DYNAMIC PROGRAMMING (DP)
    +Nếu 1 trạng thái tính đi tính lại nhiều lần 
    +Đáp án lớn được build từ đáp án nhỏ
    + đề bài hỏi : max/min , số cách , tối ưu , longest , shortest,...
    => DP    */
/*TEMPLATE CODE 
     vector < int> dp(n);
     dp[0] = base;
     for(int i = 1 ; i < n ; i ++)
     {
       dp[i] = transition;
     }  */
     
class Solution 
{
public:
    int maxProfit(vector<int>& prices) 
    {
        /* dpHold : lợi nhuận tốt nhất nếu hiện tại đang giữ cổ phiếu . 
        Ban đầu : chx mua gì , nếu mua ngày đầu : profit = -prices[0]; */
        int dpHold = -prices[0];
        // dpSold : lợi nhuận tốt nhất nếu hiện tại ko giữ cổ phiếu . Ban đầu chx làm gì : profit = 0 
        int dpSold = 0 ;
        // duyệt ngay từ ngày thứ 2
        for(int i = 1 ; i < prices.size() ; i ++)
        {
            // nếu hnay bán : profit = tiền đang giữ + giá bán hnay
            dpSold = max(dpSold , dpHold + prices[i]);
            // nếu hnay mua : profit = - prices[i] vì bài chỉ cho mua 1 lần
            dpHold = max(dpHold , -prices[i]);
        }
        return dpSold;
    }
};
