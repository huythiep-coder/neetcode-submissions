/* HASH MAP + MIN_HEAP(cho phép truy cập vào phần tử nhỏ nhất nhanh chóng (ở đỉnh heap))
     + tìm K phần tử lớn nhất -> Min_Heap kích thước k
     + tìm K phần tử nhỏ nhất -> Max_Heap kích thước k */
 
class Solution 
{
public:
    vector<int> topKFrequent(vector<int>& nums, int k) 
    {
        unordered_map < int , int > freq_map;
        for(int num : nums)
        {
            freq_map[num] ++;
        }
        /* dùng MIN_HEAP để tìm K phần tử có tần suất cao nhất
         priority_queue : mặc định là MAX_HEAP trong C++
         Để tạo min_heap , ta cần cung cấp thêm 2 tham số , ta lưu cặp (tần suất , số) vào heap */

        using Pair = pair<int , int>;
        priority_queue <Pair , vector <Pair> , greater <Pair>> min_heap;
        // auto :yêu cầu trình biên dich tự động suy ra kiểu dữ liệu dựa trên giá trị được gán cho nó
        for(auto const& pair : freq_map)
        {
            int num = pair.first;
            int freq = pair.second;
            // đẩy cặp (tần suất , số) vào heap
            min_heap.push({freq , num});
            // nếu heap nhiều hơn k phần tử , loại bỏ phần tử có tần suất nhỏ nhất (đỉnh heap)
            if(min_heap.size() > k)
            {
                min_heap.pop();
            };
        }
        vector <int>result;
        while(!min_heap.empty())
        {
            // lấy phần tử từ đỉnh heap (cặp có tần suất nhỏ nhất trong top k)
            // pair.second chính là số cần lấy
                result.push_back(min_heap.top().second);
            // xóa phần tử đã lấy
                min_heap.pop();
        }
        // kết quả đang bị ngược (từ tần suất thấp đến cao trong top k) , nhưng đề bài ko yêu cầu thứ tự
        // nếu muốn thứ tự giảm dần , dùng REVERSE lại vector : reverse(result.begin() , result.end());
         return result;
    }
};

