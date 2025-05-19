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
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};


class Solution {
public:
    Node *copyRandomList(Node *head) {
        //Node dummy(0);
        Node *old_curr = head;
        unordered_map<Node *, Node *> map;

        while (old_curr) {
            map[old_curr] = new Node(old_curr->val);
            old_curr = old_curr->next;
        }

        old_curr = head;
        while (old_curr) {
            map[old_curr]->next = map[old_curr->next];
            map[old_curr]->random = map[old_curr->random];
            old_curr = old_curr->next;
        }

        return map[head];
    }
};