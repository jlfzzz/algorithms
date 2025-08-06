#include <bits/stdc++.h>
#include <unordered_map>
#include <vector>
using namespace std;
using ll = long long;
#define i128 __int128_t
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
const ll MOD2 = 4611686018427387847;

void init() {}

void solve2() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> b(n);
    For(i, n) cin >> a[i];
    For(i, n) cin >> b[i];

    int ans = 0;
    unordered_map<int, int> cnt;
    a.push_back(-1);
    b.push_back(-2);

    for (int i = n - 1; i >= 0; i--) {
        int x = a[i];
        int y = b[i];
        if (x == y or x == a[i + 1] or y == b[i + 1]) {
            cout << i + 1 << '\n';
            return;
        }

        cnt[a[i + 1]]--;
        cnt[b[i + 1]]--;

        if (cnt[x] > 0 or cnt[y] > 0) {
            cout << i + 1 << '\n';
            return;
        }
        cnt[x]++;
        cnt[y]++;
        cnt[a[i + 1]]++;
        cnt[b[i + 1]]++;
    }
    cout << 0 << '\n';
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> b(n);
    For(i, n) cin >> a[i];
    For(i, n) cin >> b[i];

    int ans = 0;
    unordered_map<int, int> cnt1;
    unordered_map<int, int> cnt2;
    if (a[n - 1] == b[n - 1]) {
        cout << n << '\n';
        return;
    }

    cnt1[a[n - 1]]++;
    cnt2[b[n - 1]]++;
    bool flag = false;

    for (int i = n - 2; i >= 0; i--) {
        int x = a[i];
        int y = b[i];
        if ((flag and cnt1.contains(y)) or (flag and cnt2.contains(x)) or (!flag and cnt2.contains(y)) or
            (!flag and cnt1.contains(x)) or x == y) {
            ans = i + 1;
            break;
        }

        int nxt_x = a[i + 1];
        int nxt_y = b[i + 1];

        if (flag) {
            cnt1[nxt_y]--;
            cnt2[nxt_x]--;

            if ((cnt2.contains(y) and cnt2[y] > 0) or (cnt1.contains(x) and cnt1[x] > 0)) {
                ans = i + 1;
                break;
            }
            cnt1[nxt_y]++;
            cnt2[nxt_x]++;
            cnt1[x]++;
            cnt2[y]++;
        } else {
            cnt1[nxt_x]--;
            cnt2[nxt_y]--;

            if ((cnt1.contains(y) and cnt1[y] > 0) or (cnt2.contains(x) and cnt2[x] > 0)) {
                ans = i + 1;
                break;
            }
            cnt1[nxt_x]++;
            cnt2[nxt_y]++;
            cnt2[x]++;
            cnt1[y]++;
        }

        flag ^= 1;
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    cin >> T;
    while (T--)
        solve2();
    return 0;
}
