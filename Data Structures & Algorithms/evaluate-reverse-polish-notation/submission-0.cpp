/*
 * ====================================================================
 *  BÀI TOÁN: Evaluate Reverse Polish Notation
 *            Tính Giá Trị Biểu Thức Ký Pháp Nghịch Đảo Ba Lan
 *  Nguồn:    LeetCode #150 (Medium)
 * ====================================================================
 *  Input:  Mảng chuỗi tokens[] biểu diễn một biểu thức toán học
 *          theo dạng RPN (Reverse Polish Notation)
 *  Output: Giá trị nguyên của biểu thức đó
 *
 *  Toán tử hợp lệ: "+" | "-" | "*" | "/"
 *  Phép chia:      Làm tròn về phía 0 (truncate toward zero)
 *                  Ví dụ: 7/2 = 3, -7/2 = -3  (không phải -4)
 *
 *  Ví dụ 1:
 *    tokens = ["2","1","+","3","*"]
 *    → ((2 + 1) * 3) = 9
 *
 *  Ví dụ 2:
 *    tokens = ["4","13","5","/","+"]
 *    → (4 + (13 / 5)) = (4 + 2) = 6
 *
 *  Ví dụ 3:
 *    tokens = ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]
 *    → ((10 * (6 / ((9 + 3) * -11))) + 17) + 5 = 22
 * ====================================================================
 */

#include <stack>
#include <vector>
#include <string>
using namespace std;

// ====================================================================
//  RPN LÀ GÌ? (Reverse Polish Notation - Ký Pháp Nghịch Đảo Ba Lan)
// ====================================================================
//
//  Biểu thức thông thường (Infix):  3 + 4  → toán tử NẰM GIỮA
//  Biểu thức RPN (Postfix):         3 4 +  → toán tử Ở SAU
//
//  So sánh thêm:
//  ┌──────────────────────────────────────────────────────────┐
//  │  Infix  (thông thường): (3 + 4) * 2 = 14               │
//  │  Prefix (Polish):       * + 3 4 2   = 14               │
//  │  Postfix (RPN):         3 4 + 2 *   = 14               │
//  └──────────────────────────────────────────────────────────┘
//
//  Ưu điểm của RPN:
//  → Không cần dấu ngoặc để xác định thứ tự phép tính
//  → Máy tính (calculator) và compiler dùng RPN nội bộ
//  → Dễ tính với Stack (chỉ đọc 1 lần từ trái sang phải)
//
// ====================================================================
//  THUẬT TOÁN: STACK – Tính Biểu Thức Hậu Tố (Postfix Evaluation)
// ====================================================================
//
//  NGUYÊN TẮC hoạt động (chỉ 2 quy tắc):
//  ┌──────────────────────────────────────────────────────────┐
//  │  QUY TẮC 1 – Gặp SỐ:      Push vào stack               │
//  │  QUY TẮC 2 – Gặp TOÁN TỬ: Pop 2 số, tính, push kết quả │
//  └──────────────────────────────────────────────────────────┘
//
//  Sau khi duyệt hết tokens: Stack còn đúng 1 phần tử = đáp án
//
// ====================================================================
//  DẤU HIỆU NHẬN BIẾT nên dùng Stack để xử lý biểu thức:
// ====================================================================
//
//  1. Bài liên quan đến TÍNH GIÁ TRỊ biểu thức (evaluate expression)
//     → Stack là công cụ chuẩn để xử lý biểu thức toán học
//
//  2. Dữ liệu đầu vào ở dạng POSTFIX / RPN
//     → Nhận ra: số và toán tử xen kẽ, toán tử đứng SAU các toán hạng
//
//  3. Cần xử lý toán hạng theo thứ tự "cái đến sau xử lý trước"
//     → Đây là đặc tính LIFO của Stack
//
//  4. Từ khóa nhận biết:
//     "evaluate", "expression", "postfix", "RPN",
//     "operator", "operand", "tokens", "calculate"
//
// ====================================================================
//  CÁC BÀI TOÁN TƯƠNG TỰ DÙNG STACK XỬ LÝ BIỂU THỨC:
// ====================================================================
//
//  ✦ Basic Calculator I, II, III (LC 224, 227, 772)
//  ✦ Infix to Postfix conversion (chuyển đổi dạng biểu thức)
//  ✦ Expression Tree (cây biểu thức)
//  ✦ Decode String: "3[a2[c]]" → "accaccacc"
//  ✦ Remove Duplicate Letters / Parentheses
// ====================================================================

class Solution {
public:
    int evalRPN(vector<string>& tokens) {

        // Stack lưu các TOÁN HẠNG (số nguyên) đang chờ được tính
        // Khi gặp toán tử, lấy 2 số từ stack ra để thực hiện phép tính
        stack<long long> st;
        // Dùng long long để tránh tràn số (overflow) khi nhân số lớn

        // Duyệt từng token trong mảng từ trái sang phải
        for (const string& token : tokens) {

            // --------------------------------------------------------
            //  TRƯỜNG HỢP A: Token là TOÁN TỬ (+, -, *, /)
            // --------------------------------------------------------
            if (token == "+" || token == "-" ||
                token == "*" || token == "/") {

                // ★ LƯU Ý QUAN TRỌNG VỀ THỨ TỰ POP ★
                // ─────────────────────────────────────────────────
                //  Pop lần 1 → b (toán hạng BÊN PHẢI / số đến SAU)
                //  Pop lần 2 → a (toán hạng BÊN TRÁI / số đến TRƯỚC)
                //
                //  Tại sao? Vì Stack là LIFO:
                //  Trong "3 4 -", 4 được push SAU nên 4 ở TRÊN stack
                //  → pop ra 4 trước (b=4), rồi mới lấy 3 (a=3)
                //  → Kết quả: a - b = 3 - 4 = -1  ✓
                //
                //  Nếu làm ngược (b-a): 4-3 = 1  ✗ (SAI!)
                //  ─────────────────────────────────────────────────
                long long b = st.top(); st.pop(); // Toán hạng PHẢI
                long long a = st.top(); st.pop(); // Toán hạng TRÁI

                long long result = 0;

                if (token == "+") {
                    result = a + b;              // Cộng
                }
                else if (token == "-") {
                    result = a - b;              // Trừ: TRÁI - PHẢI
                }
                else if (token == "*") {
                    result = a * b;              // Nhân
                }
                else { // token == "/"
                    // Chia nguyên, làm tròn VỀ PHÍA 0
                    // Trong C++, phép chia số nguyên đã tự làm tròn về 0
                    // Ví dụ:  7/2  =  3 (không phải  3.5)
                    // Ví dụ: -7/2  = -3 (không phải -3.5 hay -4)
                    result = a / b;
                }

                // Đẩy kết quả vừa tính trở lại stack
                // Kết quả này có thể là toán hạng cho phép tính tiếp theo
                st.push(result);
            }

            // --------------------------------------------------------
            //  TRƯỜNG HỢP B: Token là SỐ (nguyên, có thể âm)
            // --------------------------------------------------------
            //  Chuyển chuỗi thành số nguyên và đẩy vào stack
            //  stoll() = string to long long (xử lý được số âm)
            //  Ví dụ: "-11" → -11, "42" → 42
            else {
                st.push(stoll(token));
            }
        }

        // ============================================================
        //  KẾT QUẢ CUỐI CÙNG
        // ============================================================
        //  Sau khi xử lý hết tokens, stack chỉ còn đúng 1 phần tử
        //  Đó chính là giá trị của toàn bộ biểu thức
        //
        //  Tại sao chắc chắn còn đúng 1? Vì biểu thức RPN hợp lệ
        //  luôn tiêu thụ đúng số toán hạng cho mỗi toán tử
        return (int)st.top();
    }
};

/*
 * ====================================================================
 *  MINH HỌA TỪNG BƯỚC (Trace Examples)
 * ====================================================================
 *
 *  ── Ví dụ 1: tokens = ["2","1","+","3","*"] ──────────────────────
 *  Biểu thức Infix tương đương: (2 + 1) * 3 = 9
 *
 *  Bước │ Token │ Hành động               │ Stack (đáy → đỉnh)
 *  ─────┼───────┼─────────────────────────┼─────────────────────
 *    1  │ "2"   │ Số → push 2             │ [2]
 *    2  │ "1"   │ Số → push 1             │ [2, 1]
 *    3  │ "+"   │ Pop b=1, a=2 → 2+1=3    │ [3]
 *       │       │ Push 3                  │
 *    4  │ "3"   │ Số → push 3             │ [3, 3]
 *    5  │ "*"   │ Pop b=3, a=3 → 3*3=9    │ [9]
 *       │       │ Push 9                  │
 *  Kết quả: st.top() = 9 ✓
 *
 *  ── Ví dụ 2: tokens = ["4","13","5","/","+"] ─────────────────────
 *  Biểu thức Infix tương đương: 4 + (13 / 5) = 6
 *
 *  Bước │ Token │ Hành động               │ Stack
 *  ─────┼───────┼─────────────────────────┼─────────────────────
 *    1  │ "4"   │ Số → push 4             │ [4]
 *    2  │ "13"  │ Số → push 13            │ [4, 13]
 *    3  │ "5"   │ Số → push 5             │ [4, 13, 5]
 *    4  │ "/"   │ Pop b=5, a=13 → 13/5=2  │ [4, 2]
 *       │       │ Push 2                  │
 *    5  │ "+"   │ Pop b=2, a=4 → 4+2=6    │ [6]
 *       │       │ Push 6                  │
 *  Kết quả: st.top() = 6 ✓
 *
 *  ── Ví dụ minh họa thứ tự pop (QUAN TRỌNG) ───────────────────────
 *  tokens = ["7","2","-"]   → nên ra 7-2=5 (không phải 2-7=-5)
 *
 *  Bước │ Token │ Hành động               │ Stack
 *  ─────┼───────┼─────────────────────────┼─────────────────────
 *    1  │ "7"   │ push 7                  │ [7]
 *    2  │ "2"   │ push 2                  │ [7, 2]
 *    3  │ "-"   │ Pop b=2 (đỉnh)          │
 *       │       │ Pop a=7 (dưới)          │
 *       │       │ a - b = 7 - 2 = 5       │ [5]
 *  Kết quả: 5 ✓   (nếu làm b-a sẽ ra -5 ✗)
 *
 * ====================================================================
 *  CẤU TRÚC TỔNG QUÁT ĐỂ ÁP DỤNG THUẬT TOÁN NÀY
 * ====================================================================
 *
 *  for (mỗi token) {
 *      if (token là toán tử) {
 *          b = st.top(); st.pop();   // Toán hạng PHẢI (pop trước)
 *          a = st.top(); st.pop();   // Toán hạng TRÁI (pop sau)
 *          st.push(a OP b);          // Push kết quả
 *      } else {
 *          st.push(chuyển token thành số);
 *      }
 *  }
 *  return st.top();
 *
 * ====================================================================
 *  ĐỘ PHỨC TẠP (Complexity)
 * ====================================================================
 *
 *  ⏱ Thời gian: O(n) — duyệt mỗi token đúng 1 lần
 *  💾 Bộ nhớ:   O(n) — stack chứa tối đa n/2 số (khi toán hạng nhiều)
 * ====================================================================
 */