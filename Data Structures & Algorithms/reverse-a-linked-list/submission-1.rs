// Definition for singly-linked list.
// #[derive(PartialEq, Eq, Clone, Debug)]
// pub struct ListNode {
//     pub val: i32,
//     pub next: Option<Box<ListNode>>,
// }
impl Solution {
    pub fn reverse_list(head: Option<Box<ListNode>>) -> Option<Box<ListNode>> {
        fn helper(head: Option<Box<ListNode>>, prev: Option<Box<ListNode>>) -> Option<Box<ListNode>> {
            match head {
                None => prev,
                Some(mut node) => {
                    let next = node.next.take();
                    node.next = prev;
                    helper(next, Some(node))
                }
            }
        }
        helper(head, None)
    }
}