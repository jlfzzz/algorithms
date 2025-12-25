#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5e5 + 10;
const int SIGMA = 26;

struct Trie {
    int son[MAXN][SIGMA];
    int end[MAXN];
    int tot;

    Trie() { init(); }

    void init() {
        tot = 0;
        memset(son[0], 0, sizeof(son[0]));
        end[0] = 0;
    }

    int new_node() {
        ++tot;
        memset(son[tot], 0, sizeof(son[tot]));
        end[tot] = 0;
        return tot;
    }

    void insert(const string &s) {
        int p = 0;
        for (char c: s) {
            int u = c - 'a';
            if (!son[p][u])
                son[p][u] = new_node();
            p = son[p][u];
        }
        end[p]++;
    }

    int query(const string &s) {
        int p = 0;
        for (char c: s) {
            int u = c - 'a';
            if (!son[p][u])
                return 0;
            p = son[p][u];
        }
        return end[p];
    }
} trie;
