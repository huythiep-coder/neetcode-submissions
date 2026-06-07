# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next


class Solution:
    # nhận vào head(cột mốc / người đầu tiên của danh sách)
    def reverseList(self, head: Optional[ListNode]) -> Optional[ListNode]:
        # nếu danh sách ban đầu rỗng -> trả về None
        if not head:
            return None
            # tạm thời tạo 1 biến để đánh dấu người đứng đầu mới
        newHead = head
            # nếu phía sau danh sách chx hết , cần làm tiếp .Nếu ko còn thì nó chính là chuỗi đã đảo ngược
        if head.next:
                #  tạo bước đệ quy
            newHead = self.reverseList(head.next)
                #  đảo chiều mũi tên liên kết
            head.next.next = head
                # cắt đuôi
        head.next = None
            # trả về danh sách đảo ngược hoàn toàn
        return newHead
