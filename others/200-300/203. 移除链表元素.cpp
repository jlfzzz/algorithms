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
    ListNode *removeElements(ListNode *head, int val) {
        ListNode dummy(0, head);
        ListNode *curr = head;
        ListNode *prev = &dummy;

        while (curr) {
            if (curr->val == val) {
                ListNode *nxt = curr->next;
                prev->next = nxt;
                curr = nxt;
            } else {
                prev = curr;
                curr = curr->next;
            }
        }

        return dummy.next;
    }
};