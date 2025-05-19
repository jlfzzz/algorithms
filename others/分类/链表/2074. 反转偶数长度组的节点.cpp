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
    ListNode *reverseEvenLengthGroups(ListNode *head) {
        if (!head) return nullptr; // Handle empty list case

        ListNode dummy(0, head); // Dummy node before head to simplify linking
        ListNode *groupPrev = &dummy; // Pointer to the node *before* the current group starts
        int currLen = 1; // Initialize the desired group length

        while (groupPrev->next) { // Loop as long as there's a potential start for a group
            ListNode *groupHead = groupPrev->next; // The first node of the current potential group
            ListNode *tailFinder = groupHead;      // Pointer used to find the end of the group
            int actualLen = 0;                   // To store the actual length of the current group

            // Determine the actual length of the current group (up to currLen or end of list)
            for (int i = 0; i < currLen && tailFinder; ++i) {
                actualLen++;
                tailFinder = tailFinder->next; // tailFinder ends up pointing to the node *after* the group
            }

            // Check if the *actual* length of this group is even
            if (actualLen % 2 == 0) {
                // Reverse the nodes in this group
                ListNode *curr = groupHead;
                ListNode *prev = tailFinder; // Initialize prev to the node *after* the segment being reversed
                ListNode *next = nullptr;

                // Standard in-place reversal of 'actualLen' nodes
                for (int i = 0; i < actualLen; ++i) {
                    next = curr->next;
                    curr->next = prev;
                    prev = curr;
                    curr = next;
                }
                // After reversal:
                // 'prev' is the new head of the reversed segment.
                // 'groupHead' (the original head) is now the tail of the reversed segment.

                // Link the node before the group to the new head of the reversed segment
                groupPrev->next = prev;
                // The new tail's (original groupHead's) next pointer should already be correct
                // because 'prev' was initialized to 'tailFinder'.

                // For the next iteration, the node before the *next* group is the
                // *tail* of the segment we just reversed (which is the original groupHead).
                groupPrev = groupHead;

            } else {
                // If the actual length is odd, no reversal is needed.
                // We just need to advance groupPrev to the last node of this odd-length group.
                // Iterate actualLen - 1 steps from groupHead to find the last node.
                ListNode *lastNodeOfOddGroup = groupHead;
                for (int i = 0; i < actualLen - 1 && lastNodeOfOddGroup; ++i) {
                    lastNodeOfOddGroup = lastNodeOfOddGroup->next;
                }

                // Update groupPrev if we successfully found the last node
                if (lastNodeOfOddGroup) {
                    groupPrev = lastNodeOfOddGroup;
                } else {
                    // This case implies actualLen might be 0 or 1, or list ended.
                    // If actualLen is 1, loop runs 0 times, lastNodeOfOddGroup is groupHead.
                    // groupPrev is correctly updated to groupHead.
                    // If groupPrev->next was null initially, loop wouldn't run.
                    // So, this branch handles the tail correctly.
                }
            }

            currLen++; // Increment the target length for the next group
        }

        return dummy.next; // Return the potentially modified head of the list
    }

    // User's original reverseNode function is not needed for this approach.
    // ListNode *reverseNode(ListNode *head, int k) { ... }
};