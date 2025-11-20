#include "bits/stdc++.h"
using namespace std;
using ll = long long;

struct Node {
    int ch[2];
    int cnt;
};

struct Trie {
    static constexpr int MAXN = 100000 + 5;
    static constexpr int MAXNODE = MAXN * 32;
    Node d[MAXNODE];
    int tot;

    void clear() {
        tot = 1;
        d[1].ch[0] = d[1].ch[1] = 0;
        d[1].cnt = 0;
    }

    void insert(int x) {
        int u = 1;
        d[u].cnt++;
        for (int i = 30; i >= 0; i--) {
            int bit = (x >> i) & 1;
            if (!d[u].ch[bit]) {
                ++tot;
                d[tot].ch[0] = d[tot].ch[1] = 0;
                d[tot].cnt = 0;
                d[u].ch[bit] = tot;
            }
            u = d[u].ch[bit];
            d[u].cnt++;
        }
    }

    void erase(int x) {
        int u = 1;
        d[u].cnt--;
        for (int i = 30; i >= 0; i--) {
            int bit = (x >> i) & 1;
            u = d[u].ch[bit];
            d[u].cnt--;
        }
    }

    int getMin(int x) const {
        if (d[1].cnt == 0) {
            return (1 << 30);
        }
        int u = 1;
        int res = 0;
        for (int i = 30; i >= 0; i--) {
            int bit = (x >> i) & 1;
            int same = d[u].ch[bit];
            int diff = d[u].ch[bit ^ 1];
            if (same && d[same].cnt > 0) {
                u = same;
            } else if (diff && d[diff].cnt > 0) {
                res |= (1 << i);
                u = diff;
            } else {
                break;
            }
        }
        return res;
    }

    int getMax(int x) const {
        if (d[1].cnt == 0) {
            return 0;
        }
        int u = 1;
        int res = 0;
        for (int i = 30; i >= 0; i--) {
            int bit = (x >> i) & 1;
            int diff = d[u].ch[bit ^ 1];
            int same = d[u].ch[bit];
            if (diff && d[diff].cnt > 0) {
                res |= (1 << i);
                u = diff;
            } else if (same && d[same].cnt > 0) {
                u = same;
            } else {
                break;
            }
        }
        return res;
    }
};

Trie trie;
