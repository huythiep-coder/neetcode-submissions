/* Serialization / Deserialization bằng Length-Prefix Encoding
 “Mã hóa dữ liệu bằng cách gắn độ dài trước mỗi phần dữ liệu.” */

/* FORM THUẬT TOÁN :
        for each data
        {
            output += length(data)
            output += separator (kí hiệu ngăn cách)
            output += data        
        }
    while chưa hết chuỗi
    {
        đọc length
        bỏ qua separator
        lấy đúng length kí tự
        cập nhật và đọc vị trí
    }
*/
// DẤU HIỆU : chứa kí tự đặc biệt ; cần decode chính xác 100 % ; dữ liệu độ dài ko cố định ; dữ liệu đi liên tục , cần biết block kthuc ở đâu ,...

class Solution 
{
public:

    string encode(vector<string>& strs) 
    {
        // chuỗi kq cuối cùng
        string result = "";
        // duyệt từng chuõi trong mảng
        for(string s : strs)
        {
            //Ý TƯỞNG :  "hello" -> 5#hello vì 5 là độ dài , # là kí hiệu ngăn cách , hello là dữ liệu thật

            // to_string đổi số -> string
            result += to_string(s.length());
            // thêm dấu #
            result += '#';
            // thêm nội dung chuỗi
            result += s;
        }
        return result;
    }

    vector<string> decode(string s) 
    {
        // vector lưu kq
        vector<string> result;
        /* i = vị trí hiện tại đang đọc
        ví dụ : 5#hello4#abc  ; ban đầu i = 0 */
        int i = 0 ;
        // lặp tới hết chuỗi
        while(i < s.length())
        {
            // j dùng để tìm '#'
            /* ví dụ : 5#hello   i đang ở số 5 */
            int j = i ;
            // di chuyển j tới dấu #
            while(s[j] != '#')
            {
                j ++;
            }
            // i = 0 , j = 1 ; substring từ i -> j -1 là : "5"

            // lấy phần độ dài
            string length = s.substr(i , j - i);
            // đổi "5" -> 5
            int len = stoi(length);
            /* sau dấu # là dữ liệu thật ; ví dụ : 5#hello  < j dữ liệu bắt đầu từ j + 1 */
            string word = s.substr(j + 1 , len);
            // thêm vào kq
            result.push_back(word);
            /* cập nhật i để nhẩy tới chuỗi tiếp theo :
            ví dụ : 5#hello 
                - 1 kí tự cho 5 
                - 1 kí tự cho #
                - 5 kí tự cho hello
            => nhảy qua toàn bộ */
            i = j + 1 + len;
        }
        return result;
    }
};
