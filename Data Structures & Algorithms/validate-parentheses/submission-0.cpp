/*
 * ====================================================================
 *  Input : Chuỗi s chứa các ký tự: '(' ')' '{' '}' '[' ']'
 *  Output: true  -> chuỗi HỢP LỆ
 *          false -> chuỗi KHÔNG HỢP LỆ
 *
 *  Ví dụ:
 *    "()[]{}"  -> true   (mỗi cặp đúng thứ tự, đúng loại)
 *    "([{}])"  -> true   (lồng nhau nhưng vẫn đúng)
 *    "(]"      -> false  (sai loại ngoặc)
 *    "([)]"    -> false  (sai thứ tự đóng)
 *    "((("     -> false  (mở mà không đóng)
 * ====================================================================
 */

// ====================================================================
//  THUẬT TOÁN ÁP DỤNG: STACK (Ngăn Xếp)
// ====================================================================
//
//  Stack là gì?
//  ┌─────────────────────────────────────────────────────────────┐
//  │  Stack hoạt động theo nguyên tắc LIFO:                      │
//  │  LAST IN - FIRST OUT (Vào sau – Ra trước)                   │
//  │                                                             │
//  │  Hình dung như chồng đĩa:                                   │
//  │   push '{' →  [ { ]                                         │
//  │   push '[' →  [ { | [ ]    ← top (phần tử trên cùng)        │
//  │   pop     →  [ { ]         (lấy '[' ra trước)               │
//  └─────────────────────────────────────────────────────────────┘
//
//  Các thao tác cơ bản của Stack trong C++:
//    stack<char> st;   → Khai báo stack rỗng
//    st.push(c);       → Đẩy ký tự c lên đỉnh stack
//    st.top();         → Xem ký tự trên đỉnh (không xóa)
//    st.pop();         → Xóa ký tự trên đỉnh
//    st.empty();       → Kiểm tra stack rỗng (true/false)
//
// ====================================================================
//  DẤU HIỆU NHẬN BIẾT nên dùng Stack:
// ====================================================================
//
//  1. Bài toán có cấu trúc LỒNG NHAU (nested structure)
//     Ví dụ: "({[]})" - [] nằm trong {}, {} nằm trong ()
//     → Cái mở SAU phải được đóng TRƯỚC (LIFO!)
//
//  2. Bài toán cần MATCHING / PAIRING (cặp đôi)
//     Ví dụ: dấu ngoặc, thẻ HTML <div>...</div>, quotes ""
//
//  3. Cần "nhớ lại" phần tử GẦN NHẤT để đối chiếu
//     → Stack luôn cho bạn truy cập ngay phần tử gần nhất
//
//  4. Từ khóa nhận biết trong đề bài:
//     "hợp lệ", "cân bằng", "đúng thứ tự", "khớp cặp",
//     "balanced", "matching", "valid", "nested"
//
// ====================================================================
//  CÁC TRƯỜNG HỢP ỨNG DỤNG THỰC TẾ:
// ====================================================================
//
//  ✦ Code Editor/Compiler: Kiểm tra ngoặc hợp lệ trong code
//  ✦ Biểu thức toán học: Tính "3 * (2 + 4)" đúng thứ tự
//  ✦ HTML Parser: Kiểm tra tag <div><p></p></div> có đóng đúng không
//  ✦ Undo/Redo: Lưu lịch sử hành động để hoàn tác
//  ✦ Trình duyệt web: Nút "Back" quay lại trang trước
//  ✦ Đệ quy (Recursion): Call Stack của máy tính
// ====================================================================

class Solution 
{
public:
    bool isValid(string s) 
    {

        // Bước 1: Khai báo Stack
        // Stack này sẽ lưu các dấu MỞ đang chờ được đóng
        stack<char> st;

        // Bước 2: Bảng ánh xạ dấu ĐÓNG -> dấu MỞ tương ứng
        // Mục đích: Tra cứu nhanh xem dấu đóng cần khớp với dấu mở nào
        //
        //   Dấu đóng ')' cần khớp với dấu mở '('
        //   Dấu đóng ']' cần khớp với dấu mở '['
        //   Dấu đóng '}' cần khớp với dấu mở '{'
        unordered_map<char, char> match = 
        {
            {')', '('},
            {']', '['},
            {'}', '{'}
        };

        // Bước 3: Duyệt từng ký tự trong chuỗi
        for (char c : s) 
        {

            // --------------------------------------------------------
            //  TRƯỜNG HỢP A: c là dấu MỞ → Push vào stack
            // --------------------------------------------------------
            //  Nhận biết: c KHÔNG xuất hiện trong bảng match (chỉ có
            //             dấu đóng mới có trong bảng match)
            //
            //  Hành động: Đẩy vào stack để "nhớ" lại
            //  Lý do:     Chưa biết khi nào gặp dấu đóng tương ứng,
            //             cần lưu lại để đối chiếu về sau
            if (c == '(' || c == '[' || c == '{') 
            {
                st.push(c);
            }

            // --------------------------------------------------------
            //  TRƯỜNG HỢP B: c là dấu ĐÓNG → Kiểm tra với stack
            // --------------------------------------------------------
            else 
            {

                // Kiểm tra 1: Stack có rỗng không?
                // Nếu RỖNG → Không có dấu mở nào để khớp → SAI
                //
                //  Ví dụ lỗi:  s = "]"
                //  Diễn giải:  Gặp ']' nhưng stack rỗng, không có '[' nào
                //              cả → trả về false ngay
                if (st.empty()) 
                {
                    return false;
                }

                // Lấy dấu mở gần nhất ra khỏi stack
                char topChar = st.top(); // Xem phần tử trên cùng
                st.pop();               // Xóa phần tử đó ra khỏi stack

                // Kiểm tra 2: Dấu mở gần nhất có khớp dấu đóng hiện tại?
                // match[c] = dấu mở cần thiết để ghép cặp với dấu đóng c
                //
                // Nếu KHÔNG khớp → Sai loại hoặc sai thứ tự → SAI
                //
                //  Ví dụ lỗi:  s = "([)]"
                //  Diễn giải:  Đến ')': topChar='[', match[')']='('
                //              '[' != '(' → trả về false
                if (topChar != match[c]) 
                {
                    return false;
                }
            }
        }

        // ============================================================
        //  Bước 4: Kết luận sau khi duyệt hết chuỗi
        // ============================================================
        //
        //  stack RỖNG   → Mọi dấu mở đã được đóng đúng → TRUE ✓
        //  stack KHÔNG RỖNG → Còn dấu mở chưa đóng    → FALSE ✗
        //
        //  Ví dụ lỗi:  s = "(("
        //  Diễn giải:  Duyệt xong, stack còn ['(', '('] → false
        return st.empty();
    }
};

/*
 * ====================================================================
 *  MINH HỌA TỪNG BƯỚC (Trace Example)
 * ====================================================================
 *
 *  Ví dụ: s = "({[]})"
 *
 *  Bước │ c   │ Hành động         │ Stack (đáy→đỉnh)
 *  ─────┼─────┼───────────────────┼──────────────────────
 *    1  │ '(' │ Dấu mở → push     │ [ ( ]
 *    2  │ '{' │ Dấu mở → push     │ [ ( { ]
 *    3  │ '[' │ Dấu mở → push     │ [ ( { [ ]
 *    4  │ ']' │ top='[' match → ✓ │ [ ( { ]    (pop '[')
 *    5  │ '}' │ top='{' match → ✓ │ [ ( ]      (pop '{')
 *    6  │ ')' │ top='(' match → ✓ │ [ ]        (pop '(')
 *
 *  Kết thúc: Stack rỗng → return TRUE ✓
 *
 * ────────────────────────────────────────────────────────────────────
 *
 *  Ví dụ: s = "([)]"
 *
 *  Bước │ c   │ Hành động              │ Stack
 *  ─────┼─────┼────────────────────────┼──────────────────
 *    1  │ '(' │ Dấu mở → push          │ [ ( ]
 *    2  │ '[' │ Dấu mở → push          │ [ ( [ ]
 *    3  │ ')' │ top='[', match[')']='(' │
 *       │     │ '[' != '(' → SAI!       │ → return FALSE ✗
 *
 * ====================================================================
 *  ĐỘ PHỨC TẠP (Complexity)
 * ====================================================================
 *
 *  ⏱ Thời gian (Time):  O(n) — duyệt mỗi ký tự đúng 1 lần
 *  💾 Bộ nhớ (Space):   O(n) — trường hợp xấu nhất stack chứa n/2 phần tử
 *                              (khi toàn bộ nửa đầu là dấu mở)
 * ====================================================================
 */