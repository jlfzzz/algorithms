#include <algorithm>
#include <cstring>
#include <iostream>


using namespace std;

const int N = 100010;

struct SuffixArray {
    int n, m;
    char s[N];
    int sa[N], rk[N], oldrk[N], id[N], cnt[N], height[N];

    void build(const string &str) {
        n = str.length();
        m = 300;

        for (int i = 1; i <= n; ++i)
            s[i] = str[i - 1];

        memset(cnt, 0, sizeof(cnt));
        memset(rk, 0, sizeof(rk));

        get_sa();
        get_height();
    }

private:
    void get_sa() {
        for (int i = 1; i <= n; ++i)
            ++cnt[rk[i] = s[i]];
        for (int i = 1; i <= m; ++i)
            cnt[i] += cnt[i - 1];
        for (int i = n; i >= 1; --i)
            sa[cnt[rk[i]]--] = i;

        for (int w = 1; w < n; w <<= 1) {
            int p = 0;
            for (int i = n; i > n - w; --i)
                id[++p] = i;
            for (int i = 1; i <= n; ++i) {
                if (sa[i] > w)
                    id[++p] = sa[i] - w;
            }

            memset(cnt, 0, sizeof(cnt));
            for (int i = 1; i <= n; ++i)
                ++cnt[rk[id[i]]];
            for (int i = 1; i <= m; ++i)
                cnt[i] += cnt[i - 1];
            for (int i = n; i >= 1; --i)
                sa[cnt[rk[id[i]]]--] = id[i];

            memcpy(oldrk, rk, sizeof(rk));
            p = 0;
            for (int i = 1; i <= n; ++i) {
                if (oldrk[sa[i]] == oldrk[sa[i - 1]] && oldrk[sa[i] + w] == oldrk[sa[i - 1] + w]) {
                    rk[sa[i]] = p;
                } else {
                    rk[sa[i]] = ++p;
                }
            }

            if (p == n)
                break;
            m = p;
        }
    }

    void get_height() {
        int k = 0;
        for (int i = 1; i <= n; ++i) {
            if (rk[i] == 1) {
                height[rk[i]] = 0;
                continue;
            }
            if (k)
                k--;
            int j = sa[rk[i] - 1];
            while (i + k <= n && j + k <= n && s[i + k] == s[j + k])
                k++;
            height[rk[i]] = k;
        }
    }
} sa;

