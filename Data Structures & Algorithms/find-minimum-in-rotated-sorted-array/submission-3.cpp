
class Solution {
public:
    int findMin(vector<int> &nums) {
        int l = 0 , r = nums.size() - 1;
        while(l < r)
        {
            int m = l + (r - l) / 2;
            if(nums[m] < nums[r])
            {
                // khả năng chính nums[m] chính là số nhỏ 
                r = m ;
            }
            else
            {
                l = m + 1;
            }
        }
        return nums[l];
    }
};


 /*   
 ## TÌM RANH GIỚI / THU HẸP ##
while(l < r)
{
        {
            int m = l + (r - l) / 2;
            if(nums[m] < nums[r])
            {
                r = m ;
            }
            else
            {
                l = m + 1;
            }
        }
        return nums[l];
}

 ## : DẤU HIỆU NHẬN BIẾT : 

-> Tìm phần tử nhỏ nhất/lớn nhất trong mảng bị xoay vòng.

->Tìm vị trí đầu tiên hoặc cuối cùng thỏa mãn một điều kiện.

-> Tìm đỉnh núi (Peak Element).

-> Không return bên trong vòng lặp. Đợi sau khi hết vòng lặp (lúc này l == r), mới return nums[l]; (hoặc nums[r])

## TÌM SỐ CỤ THỂ ##
while(l <= r)
{
        {
            int m = l + (r - l) / 2;
            if(nums[m] < nums[r])
            {
                
                r = m - 1 ;
            }
            else
            {
                l = m + 1;
            }
        }
}
## DẤU HIỆU NHẬN BIẾT :
+>  Tìm xem số X nằm ở vị trí nào; 
+>  Tìm xem một số có tồn tại không.
+> return m ngay trong vòng lặp, hoặc return -1 nếu hết vòng lặp  */
