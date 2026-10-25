// Thuật toán Hash Map (O(n))
/* 1. Khởi tạo cấu trúc tra cứu : 
        + HASH MAP : lưu giá trị và thông tin kèm
        + HASH SET : chỉ ktra giá trị có tồn tại ko?
    2.Lặp dữ liệu (duyệt element)
    3.Tìm "phần bù" (complement)
    4.Tra cứu và xử lí(ktra complement có tồn tại trong cấu trúc tra cứu ko ?)
        map.count(key) ;
*/

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // unordered_map < key , value > map;
        // #key : giá trị của số trong mảng
        // #value : index của số 
        unordered_map<int, int> seenMap;
        for(int i = 0 ; i < nums.size() ; i ++)
        {
            int current_num = nums[i];
            // tìm "phần bù"
            int complement = target - current_num;
            // seenMap.count(key) : ktra key có tồn tại trong map ?
            if(seenMap.count(complement))
            {
                // seenMap[complement] : chỉ số của "phần bù".
                // i : chỉ số hiện tại 
                return {seenMap[complement] , i};
            }
            // ko tìm thấy thì thêm SỐ HIỆN TẠI và CHỈ SỐ của nó vào map
            seenMap[current_num] = i ;
        }
        // trả về rỗng nếu ko thấy.
        return{};
    }
};
