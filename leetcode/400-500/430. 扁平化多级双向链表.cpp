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
#include <stack>
#include <set>
#include <random>

using namespace std;

// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};


class Solution {
public:
    Node *helper(Node *head) {
        if (!head) {
            return head;
        }

        Node *nxt = head->next;
        Node *curr = head;
        Node *prev = nullptr;

        while (curr) {
            if (curr->child) {
                Node *child = curr->child;
                Node *curr_nxt = curr->next;

                child->prev = curr;
                curr->next = child;
                curr->child = nullptr;

                Node *tail = helper(child);

                tail->next = curr_nxt;
                if (curr_nxt)
                    curr_nxt->prev = tail;
                prev = tail;
                curr = curr_nxt;
            } else {
                prev = curr;
                curr = curr->next;
            }
        }

        return prev;
    }

    Node *flatten(Node *head) {
        if (!head) {
            return head;
        }
        helper(head);
        return head;
    }
};