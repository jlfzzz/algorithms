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
public:
    ListNode *oddEvenList(ListNode *head) {
        if (!head || !head->next || !head->next->next) {
            return head;
        }

        ListNode *odd = head;
        ListNode *even = head->next;
        ListNode *first_even = even;
        ListNode *last_odd = nullptr;

        while (1) {
            int flag = 0;

            if (odd && odd->next) {
                odd->next = odd->next->next;
                last_odd = odd;
                odd = odd->next;
                flag = 1;
            }

            if (even && even->next) {
                even->next = even->next->next;
                even = even->next;
                flag = 1;
            }

            if (!flag) {
                break;
            }
            //ListNode *odd_nxt = odd->next->next;
        }
        if (last_odd->next) {
            last_odd = last_odd->next;
        }
        last_odd->next = first_even;
        return head;
    }

};

class Solution {
public:
    ListNode *oddEvenList(ListNode *head) {
        if (head == nullptr) {
            return head;
        }
        ListNode *evenHead = head->next;
        ListNode *odd = head;
        ListNode *even = evenHead;
        while (even != nullptr && even->next != nullptr) {
            odd->next = even->next;
            odd = odd->next;
            even->next = odd->next;
            even = even->next;
        }
        odd->next = evenHead;
        return head;
    }
};