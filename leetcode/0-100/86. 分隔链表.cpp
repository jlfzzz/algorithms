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
    ListNode *partition(ListNode *head, int x) {
        ListNode dummy(0);
        ListNode *new_list_curr = &dummy;

        ListNode *curr = head;
        while (curr) {
            if (curr->val < x) {
                ListNode *node = new ListNode(curr->val);
                new_list_curr->next = node;
                new_list_curr = node;
            }
            curr = curr->next;
        }

        curr = head;
        while (curr) {
            if (curr->val >= x) {
                ListNode *node = new ListNode(curr->val);
                new_list_curr->next = node;
                new_list_curr = node;
            }
            curr = curr->next;
        }

        return dummy.next;
    }
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
    ListNode *partition(ListNode *head, int x) {
        ListNode dummy(0, head);
        ListNode *left = &dummy;
        ListNode *curr = head;
        ListNode *prev = left;

        while (curr) {
            if (curr->val < x) {
                if (prev == left) {
                    // Already in the 'less than x' partition and correctly placed.
                    // Just advance all relevant pointers.
                    left = curr;
                    prev = curr;
                    curr = curr->next;
                    continue;
                }
                ListNode *nxt = curr->next;
                prev->next = nxt;

                ListNode *left_nxt = left->next;
                left->next = curr;
                curr->next = left_nxt;
                left = curr;

                curr = nxt;
            } else {
                prev = curr;
                curr = curr->next;
            }
        }

        return dummy.next;
    }
};