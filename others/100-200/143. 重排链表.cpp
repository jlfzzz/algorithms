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
    void reorderList(ListNode *head) {
        ListNode *fast = head;
        ListNode *slow = head;

        while (fast && fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode *prev = nullptr;
        ListNode *curr = slow->next;

        while (curr) {
            ListNode *nxt = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nxt;
        }
        slow->next = nullptr;

        ListNode *reversed_start = prev;
        curr = head;

        while (reversed_start) {
            ListNode *nxt = curr->next;
            ListNode *reverse_nxt = reversed_start->next;

            curr->next = reversed_start;
            reversed_start->next = nxt;
            curr = nxt;
            reversed_start = reverse_nxt;
        }

    }
};