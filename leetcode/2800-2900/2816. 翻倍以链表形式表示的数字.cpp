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

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
    // 206. 反转链表
    ListNode *reverseList(ListNode *head) {
        ListNode *pre = nullptr, *cur = head;
        while (cur) {
            auto nxt = cur->next;
            cur->next = pre;
            pre = cur;
            cur = nxt;
        }
        return pre;
    }

    // 2. 两数相加：自己和自己相加
    // 题解 https://leetcode.cn/problems/add-two-numbers/solution/dong-hua-jian-ji-xie-fa-cong-di-gui-dao-oe0di/
    ListNode *double_(ListNode *l1) {
        ListNode dummy; // 哨兵节点，作为新链表的头节点的前一个节点
        auto cur = &dummy;
        int carry = 0; // 进位
        while (l1) {
            carry += l1->val * 2; // 节点值和进位加在一起
            cur->next = new ListNode(carry % 10); // 每个节点保存一个数位
            carry /= 10; // 新的进位
            cur = cur->next; // 下一个节点
            l1 = l1->next; // 下一个节点
        }
        if (carry) {
            cur->next = new ListNode(carry);
        }
        return dummy.next;
    }

public:
    ListNode *doubleIt(ListNode *head) {
        head = reverseList(head);
        auto res = double_(head);
        return reverseList(res);
    }
};
