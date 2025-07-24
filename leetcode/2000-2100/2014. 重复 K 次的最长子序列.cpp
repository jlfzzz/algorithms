#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    string longestSubsequenceRepeatedK(string s, int k) {
        vector<int> cnt(26);
        for (char c : s) {
            cnt[c - 'a']++;
        }

        string a;
        for (int i = 25; i >= 0; i--) { // 倒序，这样我们可以优先枚举字典序大的排列
            a.insert(a.end(), cnt[i] / k, 'a' + i);
        }

        auto check = [&](string &s1)->bool {
            int m = s1.size();
            int i = 0;
            int cnt = 0;
            for (char c : s) {
                if (c == s1[i]) {
                    i++;
                }
                if (i == m) {
                    cnt++;
                    i = 0;
                }
            }
            return cnt >= k;
            };
        string ans;
        string path;
        int m = a.size();
        vector<bool> vis(a.size(), false);
        auto dfs = [&](this auto &&dfs, int i, int limit)->void {
            if (i == limit) {
                if ((path.size() > ans.size() || (path.size() == ans.size() && path > ans)) && check(path)) {
                    ans = path;
                }
                return;
            }

            for (int j = 0; j < m; j++) {
                if (!vis[j]) {
                    path += a[j];
                    vis[j] = true;
                    dfs(i + 1, limit);
                    path.pop_back();
                    vis[j] = false;
                }
            }
            };
        for (int i = m - 1; i >= 0; i--) {
            if (ans != "") {
                break;
            }
            dfs(0, i + 1);
        }
        return ans;
    }
};