/*
 * ====================================================================
 *  BÀI TOÁN: Daily Temperatures - Nhiệt Độ Ngày Ấm Hơn Tiếp Theo
 *  Nguồn:    LeetCode #739 (Medium)
 * ====================================================================
 *  Input:  Mảng temperatures[], temperatures[i] = nhiệt độ ngày thứ i
 *  Output: Mảng answer[], answer[i] = số ngày phải chờ để có ngày
 *          ấm hơn. Nếu không có ngày nào ấm hơn → answer[i] = 0
 *
 *  Ví dụ:
 *    temperatures = [73, 74, 75, 71, 69, 72, 76, 73]
 *    answer       = [ 1,  1,  4,  2,  1,  1,  0,  0]
 *
 *    Giải thích:
 *    Ngày 0 (73°): Ngày 1 (74°) ấm hơn → chờ 1 ngày
 *    Ngày 1 (74°): Ngày 2 (75°) ấm hơn → chờ 1 ngày
 *    Ngày 2 (75°): Ngày 6 (76°) ấm hơn → chờ 4 ngày
 *    Ngày 6 (76°): Không có ngày nào ấm hơn → 0
 *    Ngày 7 (73°): Không có ngày nào ấm hơn → 0
 * ====================================================================
 */

#include <stack>
#include <vector>
using namespace std;

// ====================================================================
//  THUẬT TOÁN: MONOTONIC STACK (Ngăn Xếp Đơn Điệu)
// ====================================================================
//
//  Monotonic Stack là gì?
//  ┌──────────────────────────────────────────────────────────────┐
//  │  Là Stack bình thường nhưng có thêm RÀNG BUỘC:              │
//  │  Các phần tử trong stack LUÔN được sắp xếp                  │
//  │  theo một chiều nhất định (tăng dần HOẶC giảm dần)          │
//  │                                                              │
//  │  Bài này dùng: MONOTONIC DECREASING STACK                   │
//  │  → Từ đáy lên đỉnh: GIÁ TRỊ LUÔN GIẢM DẦN                 │
//  │                                                              │
//  │  Đáy [lớn ... nhỏ] Đỉnh                                     │
//  │       75  72  69   ← các index, giá trị nhiệt độ giảm dần   │
//  └──────────────────────────────────────────────────────────────┘
//
//  Stack lưu INDEX (chỉ số), không lưu giá trị nhiệt độ trực tiếp
//  Lý do: Cần INDEX để tính khoảng cách ngày (answer[i] = j - i)
//
// ====================================================================
//  Ý TƯỞNG CỐT LÕI:
// ====================================================================
//
//  Khi gặp nhiệt độ temperatures[i]:
//
//  WHILE (stack KHÔNG rỗng VÀ temperatures[i] > temperatures[đỉnh]):
//      → Tìm thấy "ngày ấm hơn" cho ngày ở đỉnh stack!
//      → answer[đỉnh] = i - đỉnh   (số ngày phải chờ)
//      → Pop đỉnh ra
//
//  PUSH i vào stack (chờ tìm ngày ấm hơn trong tương lai)
//
//  Trực giác: Stack giữ các ngày "chưa tìm được ngày ấm hơn",
//  được sắp theo nhiệt độ giảm dần.
//  Khi gặp nhiệt độ mới cao hơn → giải quyết hàng loạt ngày cùng lúc!
//
// ====================================================================
//  DẤU HIỆU NHẬN BIẾT nên dùng Monotonic Stack:
// ====================================================================
//
//  1. Bài hỏi về PHẦN TỬ LỚN HƠN / NHỎ HƠN GẦN NHẤT
//     → "Next Greater Element", "Next Smaller Element"
//     → "Previous Greater", "Previous Smaller"
//
//  2. Cần tìm mối quan hệ giữa phần tử HIỆN TẠI và phần tử
//     GẦN NHẤT thỏa điều kiện trong mảng (bên trái hoặc bên phải)
//
//  3. Bài có từ khóa:
//     "ngày ấm hơn tiếp theo", "phần tử lớn hơn tiếp theo",
//     "khoảng cách đến phần tử thỏa mãn",
//     "next greater/smaller", "span", "stock price"
//
//  4. Cần O(n) thay vì O(n²) khi so sánh mọi cặp phần tử
//
// ====================================================================
//  CÁC BÀI TOÁN TƯƠNG TỰ DÙNG MONOTONIC STACK:
// ====================================================================
//
//  ✦ Next Greater Element I & II     (LC 496, 503)
//  ✦ Largest Rectangle in Histogram  (LC 84)
//  ✦ Trapping Rain Water             (LC 42)
//  ✦ Stock Span Problem
//  ✦ Remove K Digits                 (LC 402)
//  ✦ Sum of Subarray Minimums        (LC 907)
// ====================================================================

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {

        int n = temperatures.size();

        // Mảng kết quả, khởi tạo toàn 0
        // answer[i] = 0 có nghĩa: không có ngày nào ấm hơn (mặc định)
        // Các ngày cuối không tìm được ngày ấm hơn sẽ giữ nguyên 0
        vector<int> answer(n, 0);

        // Monotonic Decreasing Stack lưu INDEX của các ngày
        // Bất biến (invariant): temperatures[stack[0]] ≥ temperatures[stack[1]] ≥ ...
        //                       Từ đáy đến đỉnh: nhiệt độ KHÔNG TĂNG
        stack<int> st; // st lưu chỉ số i, không lưu temperatures[i]

        // Duyệt từng ngày từ trái sang phải
        for (int i = 0; i < n; i++) {

            // --------------------------------------------------------
            //  BƯỚC 1: Kiểm tra và giải quyết các ngày trong stack
            // --------------------------------------------------------
            //  Trong khi stack không rỗng VÀ ngày hiện tại (i)
            //  có nhiệt độ CAO HƠN ngày ở đỉnh stack:
            //
            //  → Ngày i chính là "ngày ấm hơn đầu tiên" của ngày đỉnh stack
            //  → Tính answer và pop ngày đó ra
            //  → Tiếp tục kiểm tra phần tử kế tiếp (vòng lặp while)
            //
            //  Vì sao dùng WHILE thay vì IF?
            //  → Một ngày mới có thể giải quyết NHIỀU ngày cùng lúc
            //  → Ví dụ: stack=[75,72,69], gặp ngày 80°
            //    → giải quyết 69° (pop), rồi 72° (pop), rồi 75° (pop)
            while (!st.empty() && temperatures[i] > temperatures[st.top()]) {

                int prevDay = st.top(); // Index của ngày chưa tìm được ngày ấm hơn
                st.pop();

                // Số ngày phải chờ = index hiện tại - index ngày đó
                // Ví dụ: ngày 2 (75°) chờ đến ngày 6 (76°) → answer[2] = 6-2 = 4
                answer[prevDay] = i - prevDay;
            }

            // --------------------------------------------------------
            //  BƯỚC 2: Push index hiện tại vào stack
            // --------------------------------------------------------
            //  Ngày i chưa tìm được ngày ấm hơn → đưa vào stack chờ
            //
            //  Sau khi push, bất biến của stack được duy trì:
            //  temperatures[st.bottom()] ≥ ... ≥ temperatures[st.top()]
            //  (vì ta đã pop hết các ngày có nhiệt độ ≤ temperatures[i])
            st.push(i);
        }

        // ============================================================
        //  SAU KHI DUYỆT HẾT:
        // ============================================================
        //  Các index còn lại trong stack = những ngày KHÔNG CÓ
        //  ngày ấm hơn trong tương lai → answer[i] giữ nguyên = 0
        //  (đã khởi tạo 0 từ đầu nên không cần xử lý thêm)
        return answer;
    }
};

/*
 * ====================================================================
 *  MINH HỌA TỪNG BƯỚC (Trace Example)
 * ====================================================================
 *  temperatures = [73, 74, 75, 71, 69, 72, 76, 73]
 *  Index:          [0,  1,  2,  3,  4,  5,  6,  7]
 *
 *  Trạng thái stack hiển thị dạng: [đáy ... đỉnh]
 *  (số trong ngoặc là nhiệt độ tương ứng, để dễ hình dung)
 *
 *  i │ T[i]│ So sánh với đỉnh stack    │ Stack (index)  │ answer[]
 *  ──┼─────┼───────────────────────────┼────────────────┼──────────────────────
 *  0 │  73 │ Stack rỗng → chỉ push     │ [0(73)]        │ [0,0,0,0,0,0,0,0]
 *  ──┼─────┼───────────────────────────┼────────────────┼──────────────────────
 *  1 │  74 │ 74>73 → pop 0, ans[0]=1-0 │ []             │ [1,0,0,0,0,0,0,0]
 *    │     │ Stack rỗng → push 1        │ [1(74)]        │
 *  ──┼─────┼───────────────────────────┼────────────────┼──────────────────────
 *  2 │  75 │ 75>74 → pop 1, ans[1]=2-1 │ []             │ [1,1,0,0,0,0,0,0]
 *    │     │ Stack rỗng → push 2        │ [2(75)]        │
 *  ──┼─────┼───────────────────────────┼────────────────┼──────────────────────
 *  3 │  71 │ 71<75 → không pop, push 3 │ [2(75),3(71)]  │ [1,1,0,0,0,0,0,0]
 *  ──┼─────┼───────────────────────────┼────────────────┼──────────────────────
 *  4 │  69 │ 69<71 → không pop, push 4 │ [2,3,4(69)]    │ [1,1,0,0,0,0,0,0]
 *  ──┼─────┼───────────────────────────┼────────────────┼──────────────────────
 *  5 │  72 │ 72>69 → pop 4, ans[4]=5-4 │ [2,3(71)]      │ [1,1,0,0,1,0,0,0]
 *    │     │ 72>71 → pop 3, ans[3]=5-3 │ [2(75)]        │ [1,1,0,2,1,0,0,0]
 *    │     │ 72<75 → DỪNG, push 5      │ [2(75),5(72)]  │
 *  ──┼─────┼───────────────────────────┼────────────────┼──────────────────────
 *  6 │  76 │ 76>72 → pop 5, ans[5]=6-5 │ [2(75)]        │ [1,1,0,2,1,1,0,0]
 *    │     │ 76>75 → pop 2, ans[2]=6-2 │ []             │ [1,1,4,2,1,1,0,0]
 *    │     │ Stack rỗng → push 6        │ [6(76)]        │
 *  ──┼─────┼───────────────────────────┼────────────────┼──────────────────────
 *  7 │  73 │ 73<76 → không pop, push 7 │ [6(76),7(73)]  │ [1,1,4,2,1,1,0,0]
 *  ──┴─────┴───────────────────────────┴────────────────┴──────────────────────
 *
 *  Stack còn [6, 7] → không tìm được ngày ấm hơn → answer giữ 0
 *
 *  Kết quả: [1, 1, 4, 2, 1, 1, 0, 0] ✓
 *
 * ====================================================================
 *  TẠI SAO MONOTONIC STACK TỐT HƠN BRUTE FORCE?
 * ====================================================================
 *
 *  Brute Force (2 vòng lặp lồng nhau):
 *  for i: for j>i: if temp[j]>temp[i]: answer[i]=j-i; break
 *  → Độ phức tạp: O(n²)   Với n=100,000: 10 tỷ phép tính → TLE!
 *
 *  Monotonic Stack:
 *  Mỗi index được push vào stack đúng 1 lần và pop ra đúng 1 lần
 *  → Tổng thao tác stack = 2n
 *  → Độ phức tạp: O(n)   Với n=100,000: 200,000 phép tính → ✓
 *
 * ====================================================================
 *  KHUNG CODE TỔNG QUÁT CHO BÀI "NEXT GREATER ELEMENT"
 * ====================================================================
 *
 *  // Tìm "phần tử lớn hơn tiếp theo" cho mỗi phần tử:
 *  stack<int> st;          // Stack đơn điệu giảm (lưu index)
 *  vector<int> ans(n, -1); // -1 nếu không có phần tử lớn hơn
 *
 *  for (int i = 0; i < n; i++) {
 *      while (!st.empty() && arr[i] > arr[st.top()]) {
 *          ans[st.top()] = arr[i]; // Hoặc = i - st.top() (khoảng cách)
 *          st.pop();
 *      }
 *      st.push(i);
 *  }
 *  // Còn lại trong stack → không có phần tử lớn hơn → ans = -1 (mặc định)
 *
 * ====================================================================
 *  ĐỘ PHỨC TẠP (Complexity)
 * ====================================================================
 *
 *  ⏱ Thời gian: O(n) — mỗi index push và pop đúng 1 lần
 *  💾 Bộ nhớ:   O(n) — stack chứa tối đa n phần tử (mảng giảm dần)
 * ====================================================================
 */
