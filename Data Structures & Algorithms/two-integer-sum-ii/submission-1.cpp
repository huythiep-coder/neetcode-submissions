// Giải bằng thuật toán HASH MAP (kém tối ưu hơn 2 con trỏ)
class Solution
 {
public:
    vector<int> twoSum(vector<int>& numbers, int target)
 {
        unordered_map <int , int> seen;
        for(int i = 0 ; i < numbers.size() ; i ++)
        {
            int current = numbers[i];
            // tìm phần bù
            int com = target - current;
            if(seen.count(com))
            {
                // trả về chỉ số của nó (đã lưu trong map) và chỉ số hiện 
                return {seen[com] + 1 , i + 1};
            }
            // ghi số hiện tại và chỉ số của nó dùng cho các lần lặp sau
            seen[current] = i ;
        }
    }
};

// Tra cứu : dùng phần bù  (complement) để tìm trong map
// Ghi nhớ : Lưu số hiện tại (current_num) vào map