#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define int ll
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
const ll MOD2 = 4611686018427387847;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

vector<int> pow10;

int sum(int n) {
    if (n <= 0)
        return 0;
    int res = 0;
    for (int f: pow10) {
        if (f > n)
            break;
        int high = n / (f * 10);
        int cur = (n / f) % 10;
        int low = n % f;
        res += high * f * 45LL;
        res += cur * (low + 1);
        res += (cur * (cur - 1) / 2) * f;
    }
    return res;
}

// 找到第 k 位对应的数字，pos 返回在该数字内的偏移（0-based 从左）
int find(int k, int &pos) {
    int d = 1, cnt = 9, start = 1;
    while (true) {
        int block = d * cnt;
        if (k > block) {
            k -= block;
            d++;
            cnt *= 10;
            start *= 10;
        } else {
            int index = (k - 1) / d;
            pos = (k - 1) % d;
            return start + index;
        }
    }
}

// 返回数字 n 的前 pos+1 位数字和（0-based 从左）
int prefix(int n, int pos) {
    int len = 0, tmp = n;
    while (tmp) {
        tmp /= 10;
        len++;
    }
    int sum = 0;
    for (int j = 0; j <= pos; j++) {
        int power_idx = len - 1 - j;
        int d = (n / pow10[power_idx]) % 10;
        sum += d;
    }
    return sum;
}

void solve() {
    int k;
    cin >> k;
    int pos;
    int n = find(k, pos);
    int before = digit_sum(n - 1);
    int t = prefix(n, pos);
    cout << before + t << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    pow10.clear();
    long long p = 1;
    For(i, 19) {
        pow10.push_back((int) p);
        p *= 10;
    }

    int T;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
