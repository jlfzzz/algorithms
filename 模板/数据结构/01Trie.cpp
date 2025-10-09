#include "bits/stdc++.h"
using namespace std;
using ll = long long;

struct TrieNode {
    int count;
    array<unique_ptr<TrieNode>, 2> nxt;

    TrieNode() : count(0), nxt{nullptr, nullptr} {}
};

struct Trie {
    unique_ptr<TrieNode> root;

    Trie() : root(make_unique<TrieNode>()) {}

    void insert(int x) const {
        TrieNode *curr = root.get();
        curr->count++;
        for (int i = 30; i >= 0; i--) {
            int bit = (x >> i) & 1;
            if (!curr->nxt[bit]) {
                curr->nxt[bit] = make_unique<TrieNode>();
            }
            curr = curr->nxt[bit].get();
            curr->count++;
        }
    }

    int get_max(int x) const {
        TrieNode *curr = root.get();
        int ans = 0;
        if (!curr || curr->count == 0)
            return ans;

        for (int i = 30; i >= 0; i--) {
            int bit = (x >> i) & 1;
            int t = 1 - bit;
            if (curr->nxt[t] && curr->nxt[t]->count > 0) {
                ans |= (1 << i);
                curr = curr->nxt[t].get();
            } else if (curr->nxt[bit] && curr->nxt[bit]->count > 0) {
                curr = curr->nxt[bit].get();
            } else {
                break;
            }
        }
        return ans;
    }

    int get_min(int x) const {
        TrieNode *curr = root.get();
        int ans = 0;
        if (!curr || curr->count == 0)
            return ans;

        for (int i = 30; i >= 0; i--) {
            int bit = (x >> i) & 1;
            if (curr->nxt[bit] && curr->nxt[bit]->count > 0) {
                curr = curr->nxt[bit].get();
            } else if (curr->nxt[1 - bit] && curr->nxt[1 - bit]->count > 0) {
                ans |= (1 << i);
                curr = curr->nxt[1 - bit].get();
            } else {
                break;
            }
        }
        return ans;
    }

    void erase(int x) const {
        TrieNode *curr = root.get();
        curr->count--;
        for (int i = 30; i >= 0; i--) {
            int bit = (x >> i) & 1;
            curr = curr->nxt[bit].get();
            curr->count--;
        }
    }
};
