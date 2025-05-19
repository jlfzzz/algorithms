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

class Solution {
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        ListNode *head1 = reverse(l1);
        ListNode *head2 = reverse(l2);

        ListNode *next = nullptr;
        int carry = 0;

        while (carry || head1 || head2) {
            int sum = carry;
            if (head1) {
                sum += head1->val;
                head1 = head1->next;
            }

            if (head2) {
                sum += head2->val;
                head2 = head2->next;
            }

            carry = sum / 10;
            sum = sum % 10;

            ListNode *curr = new ListNode(sum, next);
            next = curr;
        }
        return next;
    }

    static ListNode *reverse(ListNode *head) {
        ListNode *prev = nullptr;
        ListNode *curr = head;

        while (curr) {
            ListNode *next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }
};