#pragma once
#include <bits/stdc++.h>
using namespace std;

/**
 * Suffix Automaton (SAM)
 *
 * Template parameters:
 *   SIGMA    - alphabet size
 *   MIN_CHAR - smallest character in the alphabet
 *
 * Example usage:
 *   SuffixAutomaton<> sam;           // default: lowercase a..z
 *   string s; cin >> s;
 *   sam.build(s);
 *   cout << sam.count_distinct_substrings() << "\n";
 *   cout << sam.contains_substring("abc") << "\n";
 */
template<int SIGMA = 26, char MIN_CHAR = 'a'>
struct SuffixAutomaton {
    struct State {
        int next[SIGMA];
        int link;
        int len;

        State(int _len = 0, int _link = -1) : link(_link), len(_len) { fill(next, next + SIGMA, -1); }
    };

    vector<State> st; // states
    vector<long long> occ; // endpos count for each state (after prepare_occurrences)
    int last; // id of the state corresponding to the whole string

    SuffixAutomaton(int max_len = 0) { init(max_len); }

    // 重新初始化，max_len 为要插入的字符串的最大长度（用于 reserve）
    void init(int max_len = 0) {
        st.clear();
        occ.clear();
        st.reserve(2 * max_len + 1);
        occ.reserve(2 * max_len + 1);

        st.emplace_back(0, -1);
        occ.push_back(0);
        last = 0;
    }

    // 插入一个字符
    void extend(char ch) {
        int c = ch - MIN_CHAR;
        if (c < 0 || c >= SIGMA) {
            assert(false && "character out of alphabet range");
        }

        int cur = (int) st.size();
        st.emplace_back(st[last].len + 1, 0);
        occ.push_back(1); // 新状态对应一个新的 endpos
        int p = last;

        for (; p != -1 && st[p].next[c] == -1; p = st[p].link) {
            st[p].next[c] = cur;
        }

        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = (int) st.size();
                st.push_back(st[q]);
                occ.push_back(0);
                st[clone].len = st[p].len + 1;

                for (; p != -1 && st[p].next[c] == q; p = st[p].link) {
                    st[p].next[c] = clone;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }

    // 用整串一次性建 SAM
    void build(const string &s) {
        if ((int) st.size() == 0) {
            init((int) s.size());
        }
        for (char ch: s)
            extend(ch);
    }

    // 判断 pattern 是否是原串的一个子串
    bool contains_substring(const string &pattern) const {
        int v = 0;
        for (char ch: pattern) {
            int c = ch - MIN_CHAR;
            if (c < 0 || c >= SIGMA)
                return false;
            if (st[v].next[c] == -1)
                return false;
            v = st[v].next[c];
        }
        return true;
    }

    // 准备各状态 endpos 出现次数（把次数沿 suffix link 往上推）
    void prepare_occurrences() {
        int sz = (int) st.size();
        int max_len = 0;
        for (int i = 0; i < sz; ++i)
            max_len = max(max_len, st[i].len);

        vector<int> cnt(max_len + 1);
        for (int i = 0; i < sz; ++i)
            cnt[st[i].len]++;
        for (int i = 1; i <= max_len; ++i)
            cnt[i] += cnt[i - 1];

        vector<int> order(sz);
        for (int i = sz - 1; i >= 0; --i) {
            order[--cnt[st[i].len]] = i;
        }

        for (int i = sz - 1; i > 0; --i) {
            int v = order[i];
            int p = st[v].link;
            if (p >= 0)
                occ[p] += occ[v];
        }
    }

    // 不同子串个数
    long long count_distinct_substrings() const {
        long long res = 0;
        int sz = (int) st.size();
        for (int v = 1; v < sz; ++v) {
            int link = st[v].link;
            res += (long long) (st[v].len - (link == -1 ? 0 : st[link].len));
        }
        return res;
    }

    // 与另一个串 t 的最长公共子串长度
    int longest_common_substring(const string &t) const {
        int v = 0;
        int l = 0;
        int best = 0;

        for (char ch: t) {
            int c = ch - MIN_CHAR;
            if (c < 0 || c >= SIGMA) {
                v = 0;
                l = 0;
                continue;
            }

            if (st[v].next[c] != -1) {
                v = st[v].next[c];
                ++l;
            } else {
                while (v != -1 && st[v].next[c] == -1) {
                    v = st[v].link;
                }
                if (v == -1) {
                    v = 0;
                    l = 0;
                    continue;
                } else {
                    l = st[v].len + 1;
                    v = st[v].next[c];
                }
            }
            best = max(best, l);
        }
        return best;
    }
};

/* ------------------ 示例 ------------------ */
// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//
//     string s; cin >> s;
//     SuffixAutomaton<> sam((int)s.size());
//     sam.build(s);
//
//     sam.prepare_occurrences();
//     cout << "distinct substrings: " << sam.count_distinct_substrings() << "\n";
//     cout << "contains \"abc\"? " << sam.contains_substring("abc") << "\n";
//
//     string t; cin >> t;
//     cout << "LCS length with t: " << sam.longest_common_substring(t) << "\n";
// }
