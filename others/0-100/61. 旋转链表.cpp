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
class Solution {
public:
    ListNode *rotateRight(ListNode *head, int k) {
        if (!head || !head->next) return head;

        ListNode dummy(0, head);
        int count = 1;
        ListNode *curr = head;
        while (curr->next) {
            curr = curr->next;
            count++;
        }

        int pos = k % count;
        if (pos == 0) return head;

        curr = head;
        ListNode *prev = &dummy;
        int x = count - pos;
        while (x > 0) {
            prev = curr;
            curr = curr->next;
            x--;
        }

        prev->next = nullptr;
        ListNode *ans = curr;
        while (curr->next) curr = curr->next;
        curr->next = head;
        return ans;
    }
};