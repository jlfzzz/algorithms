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
    ListNode *insertionSortList(ListNode *head) {
        ListNode dummy(-1000000, head);
        ListNode *prev = &dummy;
        ListNode *curr = head;

        while (curr) {
            if (curr->val < prev->val) {
                ListNode *temp = &dummy;
                while (curr->val > temp->next->val) {
                    temp = temp->next;
                }

                ListNode *nxt = curr->next;
                prev->next = nxt;

                curr->next = temp->next;
                temp->next = curr;

                curr = nxt;
            } else {
                prev = curr;
                curr = curr->next;
            }
        }

        return dummy.next;

    }
};