/*
 * ====================================================================
 *  BÀI TOÁN: Min Stack - Ngăn Xếp Có Chức Năng Lấy Giá Trị Nhỏ Nhất
 * ====================================================================
 *  Yêu cầu: Thiết kế một Stack hỗ trợ 4 thao tác, TẤT CẢ O(1):
 *
 *    push(val)  → Thêm val vào đỉnh stack
 *    pop()      → Xóa phần tử trên đỉnh stack
 *    top()      → Xem giá trị trên đỉnh stack (không xóa)
 *    getMin()   → Lấy giá trị NHỎ NHẤT hiện có trong stack
 *
 *  Thách thức: 3 thao tác đầu thì stack bình thường làm được O(1),
 *              nhưng getMin() thông thường phải duyệt hết → O(n).
 *              Bài yêu cầu getMin() cũng phải là O(1)!
 * ====================================================================
 */
// ====================================================================
//  THUẬT TOÁN: TWO STACKS (Hai Ngăn Xếp Song Song)
// ====================================================================
//
//  Ý tưởng cốt lõi:
//  ┌─────────────────────────────────────────────────────────────┐
//  │  Dùng 2 stack chạy song song với nhau:                      │
//  │                                                             │
//  │  mainStack : Lưu TẤT CẢ giá trị (stack bình thường)        │
//  │  minStack  : Mỗi vị trí lưu MIN tại thời điểm đó           │
//  │                                                             │
//  │  → minStack.top() LUÔN là giá trị nhỏ nhất hiện tại        │
//  │  → getMin() chỉ cần đọc đỉnh minStack → O(1) ✓             │
//  └─────────────────────────────────────────────────────────────┘
//
// ====================================================================
//  DẤU HIỆU NHẬN BIẾT nên dùng Two Stacks / Stack Phụ:
// ====================================================================
//
//  1. Bài yêu cầu O(1) cho cả CẬP NHẬT lẫn TRUY VẤN trạng thái
//     (min, max, sum, count…) của toàn bộ stack
//     → Stack thường không thể query O(1) sau mỗi pop
//
//  2. Bài cần "nhớ lại" trạng thái cũ khi pop
//     → Sau khi pop, bạn cần biết min/max TRƯỚC ĐÓ là gì
//     → Stack phụ lưu lịch sử trạng thái theo từng bước
//
//  3. Từ khóa nhận biết trong đề:
//     "O(1) time", "constant time", "get minimum/maximum",
//     "track running min/max", "restore previous state"
//
// ====================================================================
//  CÁC TRƯỜNG HỢP ỨNG DỤNG TƯƠNG TỰ:
// ====================================================================
//
//  ✦ Max Stack      : Theo dõi max thay vì min
//  ✦ Monotonic Stack: Stack đơn điệu (tăng/giảm dần)
//  ✦ Stock Span     : Tính số ngày giá cổ phiếu ≤ ngày hiện tại
//  ✦ Next Greater   : Tìm phần tử lớn hơn gần nhất bên phải
//  ✦ Undo với state : Lưu toàn bộ trạng thái sau mỗi hành động
// ====================================================================

class MinStack 
{
private:
    // Stack chính: lưu TẤT CẢ giá trị được push vào
    // Đây là stack "bình thường", xử lý push/pop/top
    stack<int> mainStack;

    // Stack phụ (minStack): lưu GIÁ TRỊ NHỎ NHẤT tại MỖI THỜI ĐIỂM
    //
    //  Ý nghĩa: minStack[i] = "Nếu tôi gọi getMin() khi mainStack có
    //           đúng i phần tử, câu trả lời sẽ là bao nhiêu?"
    //
    //  → minStack luôn "đồng hành" với mainStack:
    //    push một cái thì push cả hai, pop một cái thì pop cả hai
    stack<int> minStack;

public:

    // ----------------------------------------------------------------
    //  Constructor: Khởi tạo MinStack rỗng
    // ----------------------------------------------------------------
    MinStack() 
    {
        // stack<int> tự khởi tạo rỗng, không cần thêm gì
    }

    // ----------------------------------------------------------------
    //  push(val): Thêm val vào stack – O(1)
    // ----------------------------------------------------------------
    //
    //  Thao tác trên mainStack: push val bình thường
    //  Thao tác trên minStack : push min(val, min_hiện_tại)
    //
    //  Tại sao push min(val, top) vào minStack?
    //  → Vì minStack[i] = "min của tất cả phần tử từ đáy đến vị trí i"
    //  → Nếu val nhỏ hơn min cũ thì val là min mới
    //  → Nếu val lớn hơn thì min vẫn là min cũ (giữ nguyên)
    void push(int val) 
    {
        // Bước 1: Push val vào stack chính (luôn làm)
        mainStack.push(val);

        // Bước 2: Cập nhật minStack
        if (minStack.empty()) 
        {
            // Stack rỗng → val là phần tử đầu tiên → val chính là min
            minStack.push(val);
        } else 
        {
            // Stack có sẵn → min mới = min giữa val và min hiện tại
            // min(val, minStack.top()) đảm bảo minStack luôn lưu đúng
            minStack.push(min(val, minStack.top()));
        }
    }

    // ----------------------------------------------------------------
    //  pop(): Xóa phần tử trên đỉnh – O(1)
    // ----------------------------------------------------------------
    //
    //  QUAN TRỌNG: Pop CẢ HAI stack cùng lúc!
    //
    //  Tại sao phải pop minStack?
    //  → Vì mỗi vị trí trong minStack tương ứng với 1 vị trí mainStack
    //  → Khi xóa phần tử khỏi mainStack, trạng thái min quay về
    //    trạng thái trước đó → minStack.top() TỰ ĐỘNG đúng sau khi pop
    //
    //  Ví dụ:
    //    Trước pop: mainStack=[5,3,7], minStack=[5,3,3]
    //    Sau  pop:  mainStack=[5,3],   minStack=[5,3]
    //    → getMin() = minStack.top() = 3 ✓ (min đúng là 3)
    void pop() 
    {
        mainStack.pop(); // Xóa phần tử chính
        minStack.pop();  // Xóa trạng thái min tương ứng
    }

    // ----------------------------------------------------------------
    //  top(): Trả về phần tử trên đỉnh – O(1)
    // ----------------------------------------------------------------
    //  Chỉ đọc đỉnh mainStack, không ảnh hưởng gì đến minStack
    int top() 
    {
        return mainStack.top();
    }

    // ----------------------------------------------------------------
    //  getMin(): Trả về phần tử NHỎ NHẤT trong stack – O(1) ✓
    // ----------------------------------------------------------------
    //
    //  Đây chính là lý do tồn tại của minStack!
    //  minStack.top() LUÔN LUÔN là giá trị nhỏ nhất hiện tại
    //  → Không cần duyệt, không cần tính toán → O(1)
    int getMin() 
    {
        return minStack.top();
    }
};

/*
 * ====================================================================
 *  MINH HỌA TỪNG BƯỚC (Trace Example)
 * ====================================================================
 *
 *  Các thao tác lần lượt:
 *  push(5) → push(3) → push(7) → push(2) → getMin()
 *          → pop()   → getMin() → pop()  → getMin()
 *
 *  Thao tác   │ mainStack      │ minStack       │ Ghi chú
 *  ───────────┼────────────────┼────────────────┼──────────────────────
 *  push(5)    │ [5]            │ [5]            │ min(5, ∅) = 5
 *  push(3)    │ [5, 3]         │ [5, 3]         │ min(3, 5) = 3
 *  push(7)    │ [5, 3, 7]      │ [5, 3, 3]      │ min(7, 3) = 3 (giữ 3)
 *  push(2)    │ [5, 3, 7, 2]   │ [5, 3, 3, 2]   │ min(2, 3) = 2
 *  getMin()   │ [5, 3, 7, 2]   │ [5, 3, 3, 2]   │ → 2 ✓
 *  pop()      │ [5, 3, 7]      │ [5, 3, 3]      │ xóa 2, xóa 2
 *  getMin()   │ [5, 3, 7]      │ [5, 3, 3]      │ → 3 ✓ (tự khôi phục!)
 *  pop()      │ [5, 3]         │ [5, 3]         │ xóa 7, xóa 3
 *  getMin()   │ [5, 3]         │ [5, 3]         │ → 3 ✓
 *
 *  ★ Điểm mấu chốt: Sau khi pop 7, min tự động khôi phục về 3
 *    mà không cần tính lại! Đây chính là sức mạnh của Two Stacks.
 *
 * ====================================================================
 *  SO SÁNH CÁC CÁCH TIẾP CẬN
 * ====================================================================
 *
 *  Cách 1 – Duyệt toàn bộ stack mỗi lần getMin():
 *    push/pop/top: O(1)   |   getMin: O(n)   ← KHÔNG ĐẠT YÊU CẦU
 *
 *  Cách 2 – Lưu 1 biến min duy nhất:
 *    push/top: O(1)   |   pop: O(n) để cập nhật lại   ← KHÔNG ĐẠT
 *    (Khi pop phần tử min, không biết min mới là bao nhiêu!)
 *
 *  Cách 3 – TWO STACKS (cách này):
 *    push/pop/top/getMin: TẤT CẢ O(1)   ← ĐẠT YÊU CẦU ✓
 *
 * ====================================================================
 *  ĐỘ PHỨC TẠP (Complexity)
 * ====================================================================
 *
 *  ⏱ Thời gian: O(1) cho tất cả 4 thao tác
 *  💾 Bộ nhớ:   O(n) — lưu thêm 1 stack phụ cùng kích thước
 * ====================================================================
 */