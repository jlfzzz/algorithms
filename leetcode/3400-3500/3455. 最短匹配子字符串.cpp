#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
using ordered_set = tree<int, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>;
using ordered_map = tree<int, int, less<>, rb_tree_tag, tree_order_statistics_node_update>;
using ordered_multiset =
    tree<pair<long long, long long>, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>;

constexpr int N = int(5e5 + 5);
int INIT = [] { return 0; }();

using ll = long long;
#define i128 __int128_t
#define db long double
#define pb emplace_back
#define pf emplace_front
#define pob pop_back
#define ep emplace
#define ins insert
#define all(x) (x).begin(), (x).end()
#define all2(x, i) (x).begin() + (i), (x).end()
using pii = pair<ll, ll>;
#define ull unsigned long long
#define vi vector<int>
#define vp vector<pii>
#define vl vector<long long>
#define vvi vector<vector<int>>
#define vvp vector<vector<pii>>
#define vvl vector<vector<long long>>
#define D(i, j, k) for (int(i) = (j); (i) >= (k); (i)--)
#define SZ(a) ((int) (a).size())
#define prq priority_queue
#define fi first
#define se second
constexpr int MOD = int(1e9 + 7);
constexpr long long INF = 0x3f3f3f3f3f3f3f3f;
constexpr int inf = 0x3f3f3f3f;
#define F(i, j, k) for (int(i) = (j); (i) <= (k); (i)++)

class KMP {
public:
    static vector<int> buildLPS(const string &s) {
        int n = s.size();
        vector<int> next(n, 0);
        int i = 1;
        int len = 0;
        while (i < n) {
            while (len > 0 && s[i] != s[len]) {
                len = next[len - 1];
            }
            if (s[i] == s[len]) {
                len++;
            }
            next[i] = len;
            i++;
        }
        return next;
    }

    // KMP搜索函数 - 返回所有匹配位置
    static vector<int> search(const string &text, const string &pattern) {
        vector<int> result;
        int n = text.length();
        int m = pattern.length();

        if (m == 0) {
            result.resize(n + 1);
            iota(all(result), 0);
            return result;
        }

        vector<int> lps = buildLPS(pattern);

        int i = 0; // text的索引
        int j = 0; // pattern的索引

        while (i < n) {
            while (j > 0 && text[i] != pattern[j]) {
                j = lps[j - 1];
            }
            if (text[i] == pattern[j]) {
                j++;
            }
            if (j == m) {
                result.push_back(i - m + 1);
                j = lps[j - 1];
            }
            i++;
        }

        return result;
    }
};

class Solution {
public:
    int shortestMatchingSubstring(string s, string p) {
        vi pos;
        int n = SZ(s);
        int m = SZ(p);

        F(i, 0, m - 1) {
            if (p[i] == '*') {
                pos.pb(i);
            }
        }

        auto v1 = KMP::search(s, p.substr(0, pos[0]));
        auto v2 = KMP::search(s, p.substr(pos[0] + 1, pos[1] - pos[0] - 1));
        auto v3 = KMP::search(s, p.substr(pos[1] + 1));

        // for (int p: v1) {
        //     cout << "p1 is " << p << endl;
        // }

        // for (int p: v2) {
        //     cout << "p2 is " << p << endl;
        // }

        // for (int p: v3) {
        //     cout << "p3 is " << p << endl;
        // }

        int len1 = pos[0];
        int len2 = pos[1] - pos[0] - 1;
        int len3 = m - pos[1] - 1;

        int p2 = 0;
        int p3 = 0;

        int sz2 = SZ(v2);
        int sz3 = SZ(v3);

        int ans = inf;
        for (int p: v1) {
            while (p2 < sz2 && v2[p2] < p + len1) {
                p2++;
            }

            while (p2 < sz2 && p3 < sz3 && v3[p3] < v2[p2] + len2) {
                p3++;
            }

            if (p2 < sz2 && p3 < sz3) {
                ans = min(ans, v3[p3] + len3 - 1 - p + 1);
            }
        }

        if (ans == inf) {
            ans = -1;
        }

        return ans;
    }
};

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     Solution sol;
// }
