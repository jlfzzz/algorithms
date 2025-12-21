#include <bits/stdc++.h>
using namespace std;
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


class Solution {
public:
    string generateString(string str1, string str2) {
        int n = str1.size();
        int m = str2.size();
        int len = n + m - 1;

        string ans(len, ' ');
        vector<bool> fixed(len, false);

        D(i, n - 1, 0) {
            if (str1[i] == 'T') {
                F(j, i, i + m - 1) {
                    if (ans[j] != ' ' && ans[j] != str2[j - i]) {
                        return "";
                    }
                    ans[j] = str2[j - i];
                    fixed[j] = true;
                }
            }
        }

        F(i, 0, len - 1) {
            if (ans[i] == ' ') {
                ans[i] = 'a';
            }
        }

        int i = 0;
        while (i < n) {
            if (str1[i] == 'F') {
                bool same = true;
                F(j, 0, m - 1) {
                    if (ans[i + j] != str2[j]) {
                        same = false;
                        break;
                    }
                }

                if (same) {
                    int k = i + m - 1;
                    while (k >= i) {
                        if (!fixed[k] && ans[k] < 'z') {
                            break;
                        }
                        k--;
                    }

                    if (k < i)
                        return "";

                    ans[k]++;

                    F(p, k + 1, len - 1) {
                        if (!fixed[p])
                            ans[p] = 'a';
                    }

                    int next_i = k - m + 1;
                    if (next_i < 0)
                        next_i = 0;
                    i = next_i - 1;
                }
            }
            i++;
        }

        return ans;
    }
};
