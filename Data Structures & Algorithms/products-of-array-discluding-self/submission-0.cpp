/* THUẬT TOÁN : PREFIX SUM (MẢNG TIỀN TỐ)
           Ý tưởng: Thay vì tính đi tính lại nhiều lần, hãy tính trước và lưu lại kết quả tích lũy để tra cứu trong O(1) 
Bài toán gốc: Tính tổng từ i đến j → O(n) mỗi lần hỏi
Dùng Prefix:  Tính trước 1 lần    → O(1) mỗi lần hỏi

   /#/ HIỂU PREFIX SUM QUA VÍ DỤ TỔNG /#/
           nums = [3, 1, 4, 1, 5]

prefix[0] =  0            (chưa có gì)
prefix[1] =  3            (= 3)
prefix[2] =  3+1 = 4
prefix[3] =  3+1+4 = 8
prefix[4] =  3+1+4+1 = 9
prefix[5] =  3+1+4+1+5 = 14

Hỏi: tổng từ index 1 đến 3?
→ prefix[4] - prefix[1] = 9 - 3 = 6  ✅ (1+4+1=6)
→ Không cần duyệt lại, chỉ trừ 2 số!


   /#/ MỞ RỘNG SANG TÍCH (PREFIX PRODUCT) /#/
      thay phép + bằng phép x , logic hoàn toàn tương tự
nums = [1, 2, 3, 4]

prefix[0] = 1             (chưa có gì → tích = 1)
prefix[1] = 1             (= 1)
prefix[2] = 1×2 = 2
prefix[3] = 1×2×3 = 6
prefix[4] = 1×2×3×4 = 24

Hỏi: tích từ index 0 đến 2?
→ prefix[3] / prefix[0] = 6 / 1 = 6  (nhưng bị cấm chia!)

    /#/ VẤN ĐỀ : BỊ CẤM CHIA -> DÙNG PREFIX + SUFFIX KẾT HỢP /#/

output[i] = (tích tất cả bên TRÁI i) × (tích tất cả bên PHẢI i)
          =     PREFIX[i]             ×      SUFFIX[i]
          nums   =  [ 1,   2,   3,   4]

          ←────── quét trái sang phải ──────→
PREFIX =  [ 1,   1,   2,   6]
            ↑    ↑    ↑    ↑
            1   ×1   ×2   ×3   (mỗi ô = tích tất cả phần tử TRƯỚC nó)

          ←────── quét phải sang trái ──────→
SUFFIX =  [24,  12,   4,   1]
            ↑    ↑    ↑    ↑
           ×4   ×3   ×4    1   (mỗi ô = tích tất cả phần tử SAU nó)

output =  PREFIX × SUFFIX
       =  [1×24, 1×12, 2×4, 6×1]
       =  [ 24,   12,   8,   6]  ✅ */

class Solution 
{
public:
   vector<int> productExceptSelf(vector<int>& nums) 
   {
    int n = nums.size();

    // ════════════════════════════════════════════════
    // PHẦN 1: KHỞI TẠO
    // ════════════════════════════════════════════════

    // ① Mảng output[n] ban đầu tất cả = 1
    //    Lý do để 1: vì ta sẽ NHÂN dần vào
    //    (Giống như prefix tổng để 0 vì ta sẽ CỘNG dần vào)
    vector<int> output(n, 1);

    // ════════════════════════════════════════════════
    // PHẦN 2: QUÉT TRÁI → PHẢI (xây PREFIX)
    // Mục tiêu: output[i] = tích của nums[0..i-1]
    // ════════════════════════════════════════════════

    // ② Biến prefix = tích tích lũy, bắt đầu = 1
    //    Ý nghĩa: "tích của tất cả phần tử đã đi qua"
    //    Khởi đầu = 1 vì chưa đi qua phần tử nào (tích rỗng = 1)
    int prefix = 1;

    for (int i = 0; i < n; i++) 
    {
        // ③ Lưu prefix vào output[i]
        //    Tại thời điểm này, prefix = tích của nums[0]...nums[i-1]
        //    → Đúng là "tích tất cả bên TRÁI i"
        //
        //    Ví dụ với nums=[1,2,3,4]:
        //    i=0: prefix=1  → output[0]=1  (bên trái i=0 không có gì → 1)
        //    i=1: prefix=1  → output[1]=1  (bên trái i=1 là nums[0]=1)
        //    i=2: prefix=2  → output[2]=2  (bên trái i=2 là 1×2=2)
        //    i=3: prefix=6  → output[3]=6  (bên trái i=3 là 1×2×3=6)
        output[i] = prefix;

        // ④ Cập nhật prefix: "đi thêm 1 bước, nuốt thêm nums[i]"
        //    Sau dòng này, prefix = tích của nums[0]...nums[i]
        //    → Sẵn sàng cho vòng lặp tiếp theo (i+1)
        prefix *= nums[i];
    }

    // Sau Phần 2: output = [1, 1, 2, 6]
    //                         ↑  ↑  ↑  ↑
    //                    prefix tại mỗi vị trí

    // ════════════════════════════════════════════════
    // PHẦN 3: QUÉT PHẢI → TRÁI (nhân thêm SUFFIX)
    // Mục tiêu: output[i] *= tích của nums[i+1..n-1]
    // ════════════════════════════════════════════════

    // ⑤ Biến suffix = tích tích lũy từ phải, bắt đầu = 1
    //    Lý do giống prefix: bên phải phần tử cuối không có gì → = 1
    int suffix = 1;

    for (int i = n - 1; i >= 0; i--) 
    {
        // ⑥ Nhân output[i] với suffix
        //    output[i] đang chứa: tích bên TRÁI (từ Phần 2)
        //    suffix đang chứa:    tích bên PHẢI
        //    Sau dòng này: output[i] = tích_trái × tích_phải = ĐÁP ÁN!
        //
        //    Ví dụ với nums=[1,2,3,4]:
        //    i=3: output[3]=6,  suffix=1  → output[3]=6×1=6
        //    i=2: output[2]=2,  suffix=4  → output[2]=2×4=8
        //    i=1: output[1]=1,  suffix=12 → output[1]=1×12=12
        //    i=0: output[0]=1,  suffix=24 → output[0]=1×24=24
        output[i] *= suffix;

        // ⑦ Cập nhật suffix: "đi thêm 1 bước ngược, nuốt thêm nums[i]"
        //    Sau dòng này, suffix = tích của nums[i]...nums[n-1]
        //    → Sẵn sàng cho vòng lặp tiếp theo (i-1)
        suffix *= nums[i];
    }

    // Sau Phần 3: output = [24, 12, 8, 6] ✅
    return output;
   }
};

/*  BẢNG TRẠNG THÁI BIẾN - CHẠY TAY[1 , 2 , 3 ,4]
════════════════════════════════════════════════════════
PHẦN 2 — Quét trái → phải
════════════════════════════════════════════════════════
  i  │ prefix (trước) │ output[i] = prefix │ prefix (sau)
 ────┼─────────────────┼────────────────────┼─────────────
  0  │        1        │    output[0] = 1   │   1×1 = 1
  1  │        1        │    output[1] = 1   │   1×2 = 2
  2  │        2        │    output[2] = 2   │   2×3 = 6
  3  │        6        │    output[3] = 6   │   6×4 = 24

output sau phần 2 = [1, 1, 2, 6]

════════════════════════════════════════════════════════
PHẦN 3 — Quét phải → trái
════════════════════════════════════════════════════════
  i  │ suffix (trước) │ output[i] *= suffix │ suffix (sau)
 ────┼─────────────────┼─────────────────────┼─────────────
  3  │        1        │   6  × 1 =  6       │   1×4 = 4
  2  │        4        │   2  × 4 =  8       │   4×3 = 12
  1  │       12        │   1  × 12 = 12      │  12×2 = 24
  0  │       24        │   1  × 24 = 24      │  24×1 = 24

output sau phần 3 = [24, 12, 8, 6] ✅

🔢 Tổng đoạn con (Range Sum Query)
✖️  Tích đoạn con (Range Product)
🔢 Subarray Sum Equals K
📊 Minimum Size Subarray Sum
🧮 Count of Range Sum
→ Bất kỳ bài nào cần "kết quả tích lũy từ đầu đến i"
  đều có thể nghĩ đến Prefix! */