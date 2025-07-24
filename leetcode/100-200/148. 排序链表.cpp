#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <unordered_set>
#include <cmath>   
#include <memory> 
#include <map>
#include <queue>
#include <cstring>
#include <array> 
#include <bitset>

using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// O(n) space and O(1)

class Solution {
    // 获取链表长度
    int getListLength(ListNode *head) {
        int length = 0;
        while (head) {
            length++;
            head = head->next;
        }
        return length;
    }

    // 分割链表
    // 如果链表长度 <= size，不做任何操作，返回空节点
    // 如果链表长度 > size，把链表的前 size 个节点分割出来（断开连接），并返回剩余链表的头节点
    ListNode *splitList(ListNode *head, int size) {
        // 先找到 next_head 的前一个节点
        ListNode *cur = head;
        for (int i = 0; i < size - 1 && cur; i++) {
            cur = cur->next;
        }

        // 如果链表长度 <= size
        if (cur == nullptr || cur->next == nullptr) {
            return nullptr; // 不做任何操作，返回空节点
        }

        ListNode *next_head = cur->next;
        cur->next = nullptr; // 断开 next_head 的前一个节点和 next_head 的连接
        return next_head;
    }

    // 21. 合并两个有序链表（双指针）
    // 返回合并后的链表的头节点和尾节点
    pair<ListNode *, ListNode *> mergeTwoLists(ListNode *list1, ListNode *list2) {
        ListNode dummy; // 用哨兵节点简化代码逻辑
        ListNode *cur = &dummy; // cur 指向新链表的末尾
        while (list1 && list2) {
            if (list1->val < list2->val) {
                cur->next = list1; // 把 list1 加到新链表中
                list1 = list1->next;
            } else { // 注：相等的情况加哪个节点都是可以的
                cur->next = list2; // 把 list2 加到新链表中
                list2 = list2->next;
            }
            cur = cur->next;
        }
        cur->next = list1 ? list1 : list2; // 拼接剩余链表
        while (cur->next) {
            cur = cur->next;
        }
        // 循环结束后，cur 是合并后的链表的尾节点
        return { dummy.next, cur };
    }

public:
    ListNode *sortList(ListNode *head) {
        int length = getListLength(head); // 获取链表长度
        ListNode dummy(0, head); // 用哨兵节点简化代码逻辑
        // step 为步长，即参与合并的链表长度
        for (int step = 1; step < length; step *= 2) {
            ListNode *new_list_tail = &dummy; // 新链表的末尾
            ListNode *cur = dummy.next; // 每轮循环的起始节点
            while (cur) {
                // 从 cur 开始，分割出两段长为 step 的链表，头节点分别为 head1 和 head2
                ListNode *head1 = cur;
                ListNode *head2 = splitList(head1, step);
                cur = splitList(head2, step); // 下一轮循环的起始节点
                // 合并两段长为 step 的链表
                auto [head, tail] = mergeTwoLists(head1, head2);
                // 合并后的头节点 head，插到 new_list_tail 的后面
                new_list_tail->next = head;
                new_list_tail = tail; // tail 现在是新链表的末尾
            }
        }
        return dummy.next;
    }
};

class Solution {
public:
    ListNode *sortList(ListNode *head) {
        if (!head || !head->next) {
            return head;
        }

        ListNode dummy(0, head);

        ListNode *fast = head;
        ListNode *slow = head;

        while (fast && fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode *right_start = slow->next;
        slow->next = nullptr;

        ListNode *left = sortList(head);
        ListNode *right = sortList(right_start);

        ListNode *curr = &dummy;
        while (left && right) {
            if (left->val < right->val) {
                curr->next = left;
                curr = curr->next;
                left = left->next;
            } else {
                curr->next = right;
                curr = curr->next;
                right = right->next;
            }
        }

        while (left) {
            curr->next = left;
            curr = curr->next;
            left = left->next;
        }

        while (right) {
            curr->next = right;
            curr = curr->next;
            right = right->next;
        }

        return dummy.next;
    }
};