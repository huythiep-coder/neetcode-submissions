/* THUẬT TOÁN HASH MAP
 + Đếm tần suất (đếm số lần xuất hiện của 1 thứ gì đó ( kí tự , số , chuỗi , đối tượng , ...))
     -> key : phần tử cần đếm , value : số lần nó xuất hiện 

 + Phân Nhóm ( gom các phần tử chung có đặc tính nào đó cùng 1 nhóm )
     -> key :" dấu hiệu nhận biết " của các đặc tính đó , value : danh sách chứa các phần tử gốc thuộc nhóm đó.

 + Kiểm Tra Sự Tồn Tại / Tìm Kiếm Nhanh ( kiểm tra xem ptu từng xuất hiện , cần tím kiếm thông tin liên quan tới 1 phần tử 1 cách nhanh chóng (1))
     -> key : phần tử bạn thấy , value : có thể là index , true , sự tồn tại của key , ...

 + Caching / Ghi Nhớ Kết Quả ( bài toán đệ quy , quy hoạch động , )
     -> key : tham số đầu vào của hàm , value : kết quả tính toán 
*/
class Solution 
{
public: 
    vector<vector<string>> groupAnagrams(vector<string>& strs) 
    {
        // dùng unordered_map để nhóm các anagram.
        // key : chuỗi đã được sắp xếp ( dấu hiệu nhận biết)
        // value : vector chứa các chuỗi anagram gốc
        unordered_map < string , vector <string>> anagram_map;
        // duyệt qua từng chuỗi trong vector đầu vào
        // tạo 1 tham chiếu mà ko thể thay đổi nó ( hiệu năng cao và an toàn)
        for(const string& original_str : strs)
        {
            // tạo 1 bản sao của chuỗi để sắp xếp , ko làm thay đổi chuỗi gốc
            string sorted_str = original_str;
            // sắp xếp chuỗi để tạo ra key
            sort(sorted_str.begin() , sorted_str.end());
            // thêm chuỗi gốc vào nhóm tương ứng với key đã sắp xếp
            // nếu key chưa tồn tại , map sẽ tự động tạo 1 vector rỗng cho nó
            anagram_map[sorted_str].push_back(original_str);
        }
        // tạo vector kết quả để chứa nhóm anagram
        vector < vector < string >> result;
        // chuyển các nhóm từ map vào vector kết quả
        // duyệt qua từng cặp key - value trong map
        for(auto const& pair : anagram_map)
        {
            // phải.second chính là value ( là 1 vector <string>)
            result.push_back(pair.second);
        }
        return result;
    }
};
