/*
 * ====================================================================
 *  BÀI TOÁN: Largest Rectangle in Histogram
 *            Hình Chữ Nhật Lớn Nhất Trong Histogram
 *  Nguồn:    LeetCode #84 (Hard)
 * ====================================================================
 *  Input:  Mảng heights[] – chiều cao của từng cột trong histogram
 *          (mỗi cột có chiều rộng = 1)
 *  Output: Diện tích hình chữ nhật LỚN NHẤT có thể vẽ trong histogram
 *
 *  Ví dụ:
 *    heights = [2, 1, 5, 6, 2, 3]
 *
 *    Histogram:
 *          █
 *        █ █
 *        █ █   █
 *    █   █ █ █ █
 *    █ █ █ █ █ █
 *    ─────────────
 *    0 1 2 3 4 5   (index)
 *    2 1 5 6 2 3   (chiều cao)
 *
 *    Hình chữ nhật lớn nhất: rộng 2 × cao 5 = 10
 *    (dùng cột index 2 và 3, chiều cao 5)
 *
 *                ┌───┐
 *                │   │         Diện tích = 2 × 5 = 10 ✓
 *                │   │
 *    ┌───┬───────┤   ├───┬───┐
 *    │   │  10   │   │   │   │
 *    └───┴───────┴───┴───┴───┘
 *
 *  Output: 10
 * ====================================================================
 */

#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

// ====================================================================
//  PHÂN TÍCH VẤN ĐỀ: Tại Sao Brute Force Không Đủ Tốt?
// ====================================================================
//
//  Cách Brute Force (O(n²) hoặc O(n³)):
//    Thử tất cả cặp (i, j) → hình chữ nhật từ cột i đến cột j
//    Chiều cao = min(heights[i..j])
//    Với n = 100,000: 10 tỷ phép tính → TLE (Time Limit Exceeded)
//
//  Cần thuật toán O(n) → Monotonic Stack
//
// ====================================================================
//  THUẬT TOÁN: MONOTONIC INCREASING STACK (Ngăn Xếp Đơn Điệu Tăng)
// ====================================================================
//
//  Khác với Monotonic Decreasing Stack (Daily Temperatures):
//  ┌──────────────────────────────────────────────────────────────┐
//  │  MONOTONIC INCREASING STACK:                                 │
//  │  Từ đáy lên đỉnh: chiều cao TĂNG DẦN (hoặc không giảm)     │
//  │                                                              │
//  │  Đáy [nhỏ ... lớn] Đỉnh                                     │
//  │                                                              │
//  │  Khi gặp cột THẤP HƠN đỉnh → Pop và TÍNH DIỆN TÍCH         │
//  └──────────────────────────────────────────────────────────────┘
//
//  Ý tưởng cốt lõi:
//  ─────────────────
//  Mỗi cột i có thể là cột THẤP NHẤT của một hình chữ nhật.
//  Hình chữ nhật đó mở rộng sang TRÁI và PHẢI đến khi gặp cột
//  có chiều cao THẤP HƠN heights[i].
//
//  Với mỗi cột bị pop ra khỏi stack:
//  ┌──────────────────────────────────────────────────────────────┐
//  │  Chiều CAO  = heights[top]     (cột vừa pop ra)             │
//  │  Biên PHẢI  = i                (cột hiện tại, thấp hơn top) │
//  │  Biên TRÁI  = st.top()         (cột kế tiếp trong stack,    │
//  │               hoặc -1 nếu stack rỗng)  cũng thấp hơn top   │
//  │  Chiều RỘNG = Biên_PHẢI - Biên_TRÁI - 1                    │
//  │  DIỆN TÍCH  = Chiều CAO × Chiều RỘNG                       │
//  └──────────────────────────────────────────────────────────────┘
//
//  Stack luôn lưu INDEX, không lưu chiều cao trực tiếp
//  → Cần index để tính chiều rộng
//
// ====================================================================
//  DẤU HIỆU NHẬN BIẾT nên dùng Monotonic Stack:
// ====================================================================
//
//  1. Cần tìm VÙNG MỞ RỘNG TỐI ĐA của mỗi phần tử
//     (mở rộng trái/phải đến khi gặp phần tử nhỏ hơn/lớn hơn)
//
//  2. Mỗi phần tử đóng vai trò là MIN hoặc MAX trong một vùng
//     → Tính diện tích, tổng, đếm... dựa trên vùng đó
//
//  3. Bài liên quan đến HISTOGRAM, SKYLINE, CONTAINER, TRAP WATER
//
//  4. Từ khóa:
//     "largest rectangle", "maximum area", "histogram",
//     "extend left/right", "bounded by", "diện tích lớn nhất"
//
// ====================================================================
//  CÁC BÀI TOÁN TƯƠNG TỰ DÙNG Monotonic Stack:
// ====================================================================
//
//  ✦ Maximal Rectangle              (LC 85)  – Bản 2D của bài này
//  ✦ Trapping Rain Water            (LC 42)
//  ✦ Sum of Subarray Minimums       (LC 907)
//  ✦ Maximum Width Ramp             (LC 962)
//  ✦ Buildings With an Ocean View   (LC 1762)
// ====================================================================

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {

        int n = heights.size();
        int maxArea = 0;

        // Monotonic Increasing Stack: lưu INDEX các cột
        // Bất biến: heights[st[0]] ≤ heights[st[1]] ≤ ... ≤ heights[st.top()]
        // → Từ đáy đến đỉnh: chiều cao TĂNG DẦN
        stack<int> st;

        // ============================================================
        //  VÒNG LẶP: Duyệt đến i = n (thêm 1 lần sau mảng)
        // ============================================================
        //  Tại sao i đến n (không phải n-1)?
        //  → Sau khi duyệt hết mảng, stack vẫn còn các cột chưa xử lý
        //  → Dùng "SENTINEL" (lính canh): giả lập cột số n có chiều cao 0
        //  → Cột 0 này thấp hơn mọi cột thật → buộc pop hết stack
        //  → Đảm bảo tất cả diện tích đều được tính
        for (int i = 0; i <= n; i++) {

            // Chiều cao hiện tại:
            // - i < n : lấy heights[i] bình thường
            // - i == n: cột sentinel, chiều cao = 0 (thấp nhất có thể)
            int currentH = (i == n) ? 0 : heights[i];

            // --------------------------------------------------------
            //  BƯỚC 1: Pop và tính diện tích
            // --------------------------------------------------------
            //  Khi currentH < chiều cao đỉnh stack:
            //  → Cột i là "biên phải" của hình chữ nhật có chiều cao
            //    bằng chiều cao đỉnh stack
            //  → Dùng WHILE vì một cột thấp có thể giải phóng nhiều cột
            //
            //  Ví dụ: stack = [1(h=1), 2(h=5), 3(h=6)], gặp i=4 (h=2)
            //    → h=2 < h=6: pop 3, tính diện tích cột 3
            //    → h=2 < h=5: pop 2, tính diện tích cột 2
            //    → h=2 > h=1: dừng
            while (!st.empty() && currentH < heights[st.top()]) {

                // Lấy cột trên đỉnh stack ra (đây là cột thấp nhất
                // của hình chữ nhật cần tính)
                int topIdx = st.top();
                st.pop();

                // ── Chiều CAO của hình chữ nhật ──────────────────
                // = chiều cao của cột vừa pop ra
                // Vì đây là cột THẤP NHẤT trong vùng mở rộng
                int height = heights[topIdx];

                // ── Biên PHẢI của hình chữ nhật ──────────────────
                // = index i (cột hiện tại, là cột đầu tiên thấp hơn
                //   heights[topIdx] ở phía PHẢI)
                // Hình chữ nhật KHÔNG bao gồm cột i
                int right = i;

                // ── Biên TRÁI của hình chữ nhật ──────────────────
                // = index của phần tử ĐỈNH STACK SAU KHI POP
                //   (cột đầu tiên thấp hơn heights[topIdx] ở phía TRÁI)
                //
                // Nếu stack RỖNG sau khi pop → không có cột nào thấp hơn
                // ở phía trái → biên trái là -1 (trước cả cột 0)
                int left = st.empty() ? -1 : st.top();

                // ── Chiều RỘNG ───────────────────────────────────
                // = số cột từ (left+1) đến (right-1) tính cả 2 đầu
                // = right - left - 1
                //
                // Giải thích công thức:
                //   Các cột hợp lệ: left+1, left+2, ..., right-1
                //   Số cột = (right-1) - (left+1) + 1 = right - left - 1
                int width = right - left - 1;

                // ── Tính và cập nhật diện tích lớn nhất ──────────
                int area = height * width;
                maxArea = max(maxArea, area);
            }

            // --------------------------------------------------------
            //  BƯỚC 2: Push index hiện tại vào stack
            // --------------------------------------------------------
            //  Cột i chưa tìm được biên phải → đưa vào stack chờ
            //  Sau khi push, bất biến tăng dần được duy trì:
            //  (vì ta đã pop hết các cột có chiều cao ≥ currentH)
            //
            //  Lưu ý: Khi i == n, ta push n vào stack nhưng không ảnh
            //  hưởng gì (vòng lặp kết thúc ngay sau đó)
            st.push(i);
        }

        return maxArea;
    }
};

/*
 * ====================================================================
 *  MINH HỌA TỪNG BƯỚC - Trace Example
 * ====================================================================
 *  heights = [2, 1, 5, 6, 2, 3]
 *  Index:     0  1  2  3  4  5
 *
 *  Cột SENTINEL: index 6, chiều cao 0 (để xả hết stack)
 *
 *  ─── Trực quan histogram: ───────────────────────────────────────
 *            [3]
 *        [2] [3]  [5]
 *        [2] [3]  [5]  [6]
 *  [2]   [2] [3]  [5]  [6]  [2]  [3]
 *   0     1   2    3    4    5    6(sentinel=0)
 *
 *  ─── Bảng trace: ────────────────────────────────────────────────
 *
 *  i │ curH │ Thao tác trên Stack                    │ Stack  │ maxArea
 *  ──┼──────┼────────────────────────────────────────┼────────┼────────
 *  0 │  2   │ Stack rỗng → push 0                    │ [0]    │ 0
 *  ──┼──────┼────────────────────────────────────────┼────────┼────────
 *  1 │  1   │ 1 < h[0]=2 → POP top=0:               │        │
 *    │      │   h=2, right=1, left=-1, w=1-(-1)-1=1 │        │
 *    │      │   area = 2×1 = 2                       │ []     │ 2
 *    │      │ Stack rỗng → push 1                    │ [1]    │
 *  ──┼──────┼────────────────────────────────────────┼────────┼────────
 *  2 │  5   │ 5 > h[1]=1 → push 2                   │ [1,2]  │ 2
 *  ──┼──────┼────────────────────────────────────────┼────────┼────────
 *  3 │  6   │ 6 > h[2]=5 → push 3                   │[1,2,3] │ 2
 *  ──┼──────┼────────────────────────────────────────┼────────┼────────
 *  4 │  2   │ 2 < h[3]=6 → POP top=3:               │        │
 *    │      │   h=6, right=4, left=2, w=4-2-1=1     │        │
 *    │      │   area = 6×1 = 6                       │ [1,2]  │ 6
 *    │      │ 2 < h[2]=5 → POP top=2:               │        │
 *    │      │   h=5, right=4, left=1, w=4-1-1=2     │        │
 *    │      │   area = 5×2 = 10  ← MAX!             │ [1]    │ 10
 *    │      │ 2 > h[1]=1 → push 4                   │ [1,4]  │
 *  ──┼──────┼────────────────────────────────────────┼────────┼────────
 *  5 │  3   │ 3 > h[4]=2 → push 5                   │[1,4,5] │ 10
 *  ──┼──────┼────────────────────────────────────────┼────────┼────────
 *  6 │  0   │ 0 < h[5]=3 → POP top=5:               │        │
 *  (sentinel)│  h=3, right=6, left=4, w=6-4-1=1    │        │
 *    │      │   area = 3×1 = 3                       │ [1,4]  │ 10
 *    │      │ 0 < h[4]=2 → POP top=4:               │        │
 *    │      │   h=2, right=6, left=1, w=6-1-1=4     │        │
 *    │      │   area = 2×4 = 8                       │ [1]    │ 10
 *    │      │ 0 < h[1]=1 → POP top=1:               │        │
 *    │      │   h=1, right=6, left=-1, w=6-(-1)-1=6 │        │
 *    │      │   area = 1×6 = 6                       │ []     │ 10
 *    │      │ Stack rỗng → push 6 (kết thúc)        │ [6]    │
 *  ──┴──────┴────────────────────────────────────────┴────────┴────────
 *
 *  Kết quả: maxArea = 10 ✓
 *
 * ====================================================================
 *  HÌNH ẢNH MINH HỌA CÁC HÌNH CHỮ NHẬT ĐÃ TÍNH
 * ====================================================================
 *
 *  Khi pop index 2 (h=5, w=2, area=10):
 *  heights = [2, 1,|5, 6,|2, 3]
 *                  └─────┘
 *                  rộng=2, cao=5 → 10  ← LỚN NHẤT
 *
 *  Khi pop index 3 (h=6, w=1, area=6):
 *  heights = [2, 1, 5,|6,|2, 3]
 *                     └─┘
 *                     rộng=1, cao=6 → 6
 *
 *  Khi pop index 1 (h=1, w=6, area=6):
 *  heights = [|2, 1, 5, 6, 2, 3|]
 *             └─────────────────┘
 *             rộng=6, cao=1 → 6
 *
 * ====================================================================
 *  TẠI SAO CÔNG THỨC width = right - left - 1 ĐÚNG?
 * ====================================================================
 *
 *  Sau khi pop topIdx:
 *    left  = đỉnh stack còn lại = index cột THẤP HƠN gần nhất bên TRÁI
 *    right = i = index cột THẤP HƠN gần nhất bên PHẢI
 *
 *  Các cột CÓ THỂ bao gồm trong hình chữ nhật:
 *    left+1, left+2, ..., topIdx, ..., right-1
 *    (không bao gồm left và right vì chúng thấp hơn)
 *
 *  Số cột = (right - 1) - (left + 1) + 1 = right - left - 1  ✓
 *
 *  Ví dụ: pop index 2 (h=5), left=1, right=4
 *    Cột hợp lệ: 2, 3 (là left+1=2 đến right-1=3)
 *    Số cột = 4 - 1 - 1 = 2 ✓
 *
 * ====================================================================
 *  ĐỘ PHỨC TẠP (Complexity)
 * ====================================================================
 *
 *  ⏱ Thời gian: O(n) — mỗi index được push và pop đúng 1 lần
 *               Dù có vòng while lồng nhau, tổng pop ≤ n lần
 *
 *  💾 Bộ nhớ:   O(n) — stack chứa tối đa n+1 phần tử
 *               (trường hợp xấu nhất: mảng tăng dần như [1,2,3,4,5])
 *
 * ====================================================================
 *  SO SÁNH CÁC THUẬT TOÁN MONOTONIC STACK TRONG SERIES BÀI NÀY
 * ====================================================================
 *
 *  Bài                  │ Loại Stack  │ Pop khi nào?    │ Tính gì khi pop?
 *  ─────────────────────┼─────────────┼─────────────────┼──────────────────
 *  Daily Temperatures   │ Decreasing  │ curH > top      │ Số ngày chờ (i-top)
 *  Car Fleet            │ Decreasing  │ time > top      │ Đếm đoàn xe
 *  Largest Rectangle    │ Increasing  │ curH < top      │ Diện tích = h×w
 *  Trapping Rain Water  │ Decreasing  │ curH > top      │ Thể tích nước
 * ====================================================================
 */