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
    ListNode *mergeNodes(ListNode *head) {
        ListNode *curr = head->next;

        ListNode dummy(0);
        ListNode *ans = &dummy;

        while (curr) {
            int sum = 0;
            while (curr->next->val != 0) {
                sum += curr->val;
                curr = curr->next;
            }
            sum += curr->val;
            ans->next = new ListNode(sum);
            ans = ans->next;

            curr = curr->next->next;
        }

        return dummy.next;
    }
};