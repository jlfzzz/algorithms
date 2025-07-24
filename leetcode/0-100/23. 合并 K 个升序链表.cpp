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

using namespace std;



struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        // 定义比较器 lambda 表达式
        auto cmp = [](const ListNode *a, const ListNode *b) -> bool {
            // 创建最小堆，所以值小的优先级高
            return a->val > b->val;
            };

        // 声明优先队列（最小堆），存储 ListNode 指针
        // 使用 decltype(cmp) 来获取 lambda 表达式的类型
        priority_queue<ListNode *, vector<ListNode *>, decltype(cmp)> pq(cmp);

        // 将每个链表的头节点（如果非空）加入优先队列
        for (ListNode *head : lists) {
            if (head != nullptr) {
                pq.push(head);
            }
        }

        // 创建一个哑节点（dummy node）作为合并后链表的头节点的前驱
        ListNode dummyHead(0);
        ListNode *curr = &dummyHead; // curr 指针用于构建新链表

        // 当优先队列不为空时，持续取出最小节点
        while (!pq.empty()) {
            // 取出当前所有链表头节点中值最小的节点
            ListNode *smallestNode = pq.top();
            pq.pop();

            // 将最小节点连接到结果链表
            curr->next = smallestNode;
            curr = curr->next; // 移动 curr 指针

            // 如果这个最小节点后面还有节点，将其下一个节点加入优先队列
            if (smallestNode->next != nullptr) {
                pq.push(smallestNode->next);
            }
        }

        // 哑节点的下一个节点就是合并后链表的真正头节点
        return dummyHead.next;
    }
};

class Solution {
    // 21. 合并两个有序链表
    ListNode *mergeTwoLists(ListNode *list1, ListNode *list2) {
        ListNode dummy{}; // 用哨兵节点简化代码逻辑
        auto cur = &dummy; // cur 指向新链表的末尾
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
        return dummy.next;
    }

    // 合并从 lists[i] 到 lists[j-1] 的链表
    ListNode *mergeKLists(vector<ListNode *> &lists, int i, int j) {
        int m = j - i;
        if (m == 0) {
            return nullptr; // 注意输入的 lists 可能是空的
        }
        if (m == 1) {
            return lists[i]; // 无需合并，直接返回
        }
        auto left = mergeKLists(lists, i, i + m / 2); // 合并左半部分
        auto right = mergeKLists(lists, i + m / 2, j); // 合并右半部分
        return mergeTwoLists(left, right); // 最后把左半和右半合并
    }

public:
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        return mergeKLists(lists, 0, lists.size());
    }
};
