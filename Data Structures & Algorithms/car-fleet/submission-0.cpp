/*
 * ====================================================================
 *  BÀI TOÁN: Car Fleet - Đếm Số Đoàn Xe
 *  Nguồn:    LeetCode #853 (Medium)
 * ====================================================================
 *  Bối cảnh:
 *    n chiếc xe đang chạy trên 1 làn đường đến đích (target miles).
 *    Xe phía SAU KHÔNG THỂ vượt xe phía TRƯỚC.
 *    Nếu xe sau đuổi kịp xe trước → nhập thành 1 đoàn (fleet),
 *    cùng chạy với tốc độ của xe CHẬM HƠN (xe đầu đoàn).
 *
 *  Input:
 *    target    : Vị trí đích (miles)
 *    position[]: Vị trí xuất phát của mỗi xe
 *    speed[]   : Tốc độ của mỗi xe (miles/giờ)
 *
 *  Output: Số đoàn xe (fleet) khi đến đích
 *
 *  Ví dụ:
 *    target=12, position=[10,8,0,5,3], speed=[2,4,1,1,3]
 *
 *    Hình dung trên đường:
 *    0    3  5      8  10       12(đích)
 *    ●────●──●──────●──●─────────▶
 *    xe0  xe4 xe3  xe1 xe0
 *    (v=1)(v=3)(v=1)(v=4)(v=2)
 *
 *    Thời gian mỗi xe đến đích:
 *    xe tại 10: (12-10)/2 = 1.0h   ←─ gần đích nhất
 *    xe tại  8: (12- 8)/4 = 1.0h   → đuổi kịp xe 10 → 1 đoàn
 *    xe tại  5: (12- 5)/1 = 7.0h   → không đuổi kịp → đoàn mới
 *    xe tại  3: (12- 3)/3 = 3.0h   → đuổi kịp xe 5 → nhập đoàn
 *    xe tại  0: (12- 0)/1 = 12.0h  → không đuổi kịp → đoàn mới
 *
 *    Kết quả: 3 đoàn xe ✓
 * ====================================================================
 */

#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

// ====================================================================
//  THUẬT TOÁN: SORTING + STACK (Sắp Xếp + Ngăn Xếp)
// ====================================================================
//
//  Tại sao dùng Stack?
//  ┌──────────────────────────────────────────────────────────────┐
//  │  Stack giúp so sánh xe hiện tại với "đoàn xe phía trước"   │
//  │  một cách tự nhiên và hiệu quả.                             │
//  │                                                              │
//  │  Mỗi phần tử trong stack = 1 đoàn xe độc lập               │
//  │  (lưu thời gian đoàn đó đến đích)                           │
//  │                                                              │
//  │  → stack.size() cuối cùng = số đoàn xe                      │
//  └──────────────────────────────────────────────────────────────┘
//
//  Ý tưởng then chốt:
//  ─────────────────
//  Xét 2 xe liên tiếp (xe B phía sau xe A):
//
//  time(A) = (target - pos[A]) / speed[A]  ← xe A đến đích sau bao lâu
//  time(B) = (target - pos[B]) / speed[B]  ← xe B đến đích sau bao lâu
//
//  ┌─────────────────────────────────────────────────────────────┐
//  │  time(B) > time(A):                                         │
//  │    B chậm hơn A → không đuổi kịp → B tạo ĐOÀN MỚI         │
//  │                                                             │
//  │  time(B) ≤ time(A):                                         │
//  │    B nhanh hơn hoặc bằng A → B đuổi kịp A → NHẬP VÀO      │
//  │    đoàn A, chạy với tốc độ A (time không đổi)              │
//  └─────────────────────────────────────────────────────────────┘
//
//  Tại sao so sánh TIME thay vì SPEED?
//  → Vì xe B có thể nhanh hơn A về tốc độ, nhưng xuất phát xa hơn
//    Chỉ khi time(B) ≤ time(A) thì B mới thực sự đuổi kịp A trước đích
//
// ====================================================================
//  DẤU HIỆU NHẬN BIẾT nên dùng Sorting + Stack trong bài toán này:
// ====================================================================
//
//  1. Các đối tượng có VỊ TRÍ và CẦN SẮP XẾP theo vị trí đó
//     trước khi xử lý
//
//  2. Sau khi sắp xếp, cần so sánh phần tử HIỆN TẠI với phần tử
//     GẦN NHẤT phía trước (đỉnh stack) để quyết định gộp hay tách
//
//  3. Bài toán dạng "simulation" (mô phỏng) với đối tượng chuyển
//     động, có quy tắc gộp nhóm dựa trên tốc độ/thời gian
//
//  4. Từ khóa nhận biết:
//     "fleet", "group", "merge", "catch up", "speed", "lane",
//     "đoàn", "nhập nhóm", "đuổi kịp", "tốc độ", "thời gian đến"
//
// ====================================================================
//  CÁC BÀI TOÁN TƯƠNG TỰ:
// ====================================================================
//
//  ✦ Car Fleet II (LC 1776) – phiên bản khó hơn
//  ✦ Asteroid Collision (LC 735) – va chạm, hủy nhau
//  ✦ Remove All Adjacent Duplicates (LC 1047)
//  ✦ Bài toán xếp hàng/nhóm có điều kiện gộp
// ====================================================================

class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {

        int n = position.size();

        // ============================================================
        //  BƯỚC 1: Tạo mảng cặp (position, speed) và sắp xếp
        // ============================================================
        //  Ghép vị trí và tốc độ thành từng cặp để dễ xử lý
        //  Sau đó sắp xếp GIẢM DẦN theo vị trí
        //  → Xe GẦN ĐÍCH NHẤT xử lý trước (index 0 sau khi sort)
        //
        //  Tại sao sắp xếp giảm dần?
        //  → Xe phía TRƯỚC quyết định đoàn: xe sau chỉ có thể
        //    đuổi kịp xe trước, không thể vượt qua
        //  → Xử lý từ xe gần đích → xa đích để biết "phía trước có gì"
        vector<pair<int,int>> cars(n);
        for (int i = 0; i < n; i++) {
            cars[i] = {position[i], speed[i]};
        }

        // Sắp xếp theo position GIẢM DẦN (xe gần đích nhất ở đầu)
        sort(cars.begin(), cars.end(), [](const pair<int,int>& a,
                                          const pair<int,int>& b) {
            return a.first > b.first; // Vị trí lớn hơn → gần đích hơn
        });

        // ============================================================
        //  BƯỚC 2: Tính thời gian đến đích và dùng Stack
        // ============================================================
        //  Stack lưu THỜI GIAN đến đích của từng ĐOÀN XE độc lập
        //  → Mỗi phần tử trong stack = 1 đoàn xe
        //  → Đỉnh stack = đoàn xe ngay phía trước xe đang xét
        stack<double> st;

        for (int i = 0; i < n; i++) {

            // Tính thời gian xe này đến đích nếu không bị cản
            // Công thức: time = quãng đường còn lại / tốc độ
            double time = (double)(target - cars[i].first) / cars[i].second;

            // --------------------------------------------------------
            //  TRƯỜNG HỢP A: Stack rỗng → xe đầu tiên → đoàn mới
            // --------------------------------------------------------
            if (st.empty()) {
                st.push(time);
            }

            // --------------------------------------------------------
            //  TRƯỜNG HỢP B: time > st.top()
            //  → Xe này CHẬM HƠN đoàn phía trước
            //  → Sẽ KHÔNG đuổi kịp đoàn đó trước khi đến đích
            //  → Tạo thành ĐOÀN XE MỚI → Push vào stack
            // --------------------------------------------------------
            //
            //  Ví dụ:
            //  Đoàn trước: time = 1.0h  (đến đích nhanh)
            //  Xe hiện tại: time = 7.0h (đến đích chậm hơn)
            //  → Đoàn trước đến đích trước xe này → xe này là đoàn mới
            else if (time > st.top()) {
                st.push(time); // Đoàn mới, push thời gian của xe này
            }

            // --------------------------------------------------------
            //  TRƯỜNG HỢP C: time <= st.top()
            //  → Xe này NHANH HƠN hoặc BẰNG đoàn phía trước
            //  → Sẽ đuổi kịp và NHẬP VÀO đoàn phía trước
            //  → KHÔNG tạo đoàn mới → KHÔNG push vào stack
            // --------------------------------------------------------
            //
            //  Ví dụ:
            //  Đoàn trước: time = 1.0h
            //  Xe hiện tại: time = 1.0h (hoặc < 1.0h)
            //  → Xe này đuổi kịp hoặc đến cùng lúc → cùng đoàn
            //
            //  Sau khi nhập đoàn, xe này chạy tốc độ của đoàn trước
            //  → Thời gian đến đích của đoàn là st.top() (không đổi)
            //  → Không làm gì cả (chỉ bỏ qua xe này)
            else {
                // Không push → xe này sáp nhập vào đoàn phía trước
                // stack giữ nguyên → st.top() vẫn là thời gian đoàn trước
            }
        }

        // ============================================================
        //  BƯỚC 3: Số đoàn xe = số phần tử trong stack
        // ============================================================
        //  Mỗi phần tử trong stack đại diện cho 1 đoàn xe độc lập
        //  đến đích với thời gian khác nhau
        return (int)st.size();
    }
};

/*
 * ====================================================================
 *  MINH HỌA TỪNG BƯỚC (Trace Example)
 * ====================================================================
 *  target=12, position=[10,8,0,5,3], speed=[2,4,1,1,3]
 *
 *  SAU KHI SẮP XẾP theo position giảm dần:
 *  ┌───────┬──────────┬───────┬──────────────────────────┐
 *  │ Index │ Position │ Speed │ Time = (12-pos)/speed    │
 *  ├───────┼──────────┼───────┼──────────────────────────┤
 *  │   0   │    10    │   2   │ (12-10)/2 = 1.0h         │
 *  │   1   │     8    │   4   │ (12- 8)/4 = 1.0h         │
 *  │   2   │     5    │   1   │ (12- 5)/1 = 7.0h         │
 *  │   3   │     3    │   3   │ (12- 3)/3 = 3.0h         │
 *  │   4   │     0    │   1   │ (12- 0)/1 = 12.0h        │
 *  └───────┴──────────┴───────┴──────────────────────────┘
 *
 *  Bước │ time  │ st.top() │ So sánh     │ Hành động      │ Stack
 *  ─────┼───────┼──────────┼─────────────┼────────────────┼──────────────
 *    0  │  1.0  │  rỗng    │ -           │ push 1.0       │ [1.0]
 *  ─────┼───────┼──────────┼─────────────┼────────────────┼──────────────
 *    1  │  1.0  │  1.0     │ 1.0 ≤ 1.0  │ bỏ qua         │ [1.0]
 *       │       │          │ → đuổi kịp  │ (nhập đoàn 0)  │
 *  ─────┼───────┼──────────┼─────────────┼────────────────┼──────────────
 *    2  │  7.0  │  1.0     │ 7.0 > 1.0  │ push 7.0       │ [1.0, 7.0]
 *       │       │          │ → đoàn mới  │                │
 *  ─────┼───────┼──────────┼─────────────┼────────────────┼──────────────
 *    3  │  3.0  │  7.0     │ 3.0 ≤ 7.0  │ bỏ qua         │ [1.0, 7.0]
 *       │       │          │ → đuổi kịp  │ (nhập đoàn 2)  │
 *  ─────┼───────┼──────────┼─────────────┼────────────────┼──────────────
 *    4  │ 12.0  │  7.0     │ 12.0 > 7.0 │ push 12.0      │ [1.0,7.0,12.0]
 *       │       │          │ → đoàn mới  │                │
 *  ─────┴───────┴──────────┴─────────────┴────────────────┴──────────────
 *
 *  stack.size() = 3 → Có 3 đoàn xe ✓
 *
 *  Hình dung các đoàn xe đến đích:
 *  ┌──────────────┬───────────────────────────┬──────────────┐
 *  │   Đoàn 1     │   Đoàn 2                  │   Đoàn 3    │
 *  │  xe(10) +    │   xe(5) + xe(3)           │   xe(0)     │
 *  │  xe(8)       │   (3 đuổi kịp 5)          │             │
 *  │  time = 1.0h │   time = 7.0h             │ time = 12h  │
 *  └──────────────┴───────────────────────────┴──────────────┘
 *
 * ====================================================================
 *  VÌ SAO KHÔNG CẦN STACK MÀ CHỈ CẦN ĐẾM?
 * ====================================================================
 *  (Tối ưu hóa: chỉ cần biến maxTime thay vì stack)
 *
 *  int count = 0;
 *  double maxTime = 0;
 *  for (int i = 0; i < n; i++) {
 *      double time = (double)(target - cars[i].first) / cars[i].second;
 *      if (time > maxTime) {   // Đoàn mới
 *          count++;
 *          maxTime = time;
 *      }
 *      // time <= maxTime → nhập đoàn trước, bỏ qua
 *  }
 *  return count;
 *
 *  Tuy nhiên, dùng Stack giúp hiểu rõ cấu trúc và dễ mở rộng
 *  sang bài Car Fleet II (cần biết từng đoàn gặp nhau ở đâu)
 *
 * ====================================================================
 *  ĐỘ PHỨC TẠP (Complexity)
 * ====================================================================
 *
 *  ⏱ Thời gian: O(n log n) — do bước sắp xếp (sort)
 *               Sau sort: O(n) để duyệt và xử lý stack
 *  💾 Bộ nhớ:   O(n) — mảng cars[] và stack chứa tối đa n phần tử
 * ====================================================================
 */