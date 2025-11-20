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
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() { (void) MOD; }
struct info {
    int a, b, c, id;
};
struct info2 {
    int t, c;
};
struct cmp {
    bool operator()(const info2 &x, const info2 &y) const { return x.t > y.t; }
};

void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> A(n), B(n), C(n);
    For(i, n) { cin >> A[i] >> B[i] >> C[i]; }

    deque<int> q;
    priority_queue<info2, vector<info2>, cmp> pq;
    vector<int> ans(n);

    int cur = 0;
    int i = 0;
    int t = 0;

    while (i < n || !q.empty()) {
        int nextA = (i < n ? A[i] : inf);
        int nextL = (!pq.empty() ? pq.top().t : inf);

        if (q.empty()) {
            int nxt = min(nextA, nextL);
            if (nxt == inf)
                break;
            t = nxt;
            if (nextL <= nextA) {
                while (!pq.empty() && pq.top().t == t) {
                    cur -= pq.top().c;
                    pq.pop();
                }
            } else {
                q.push_back(i);
                i++;
                while (!q.empty() && cur + C[q.front()] <= k) {
                    int id = q.front();
                    q.pop_front();
                    ans[id] = t;
                    cur += C[id];
                    pq.push({t + B[id], C[id]});
                }
            }
        } else {
            if (cur + C[q.front()] <= k) {
                while (!q.empty() && cur + C[q.front()] <= k) {
                    int id = q.front();
                    q.pop_front();
                    ans[id] = t;
                    cur += C[id];
                    pq.push({t + B[id], C[id]});
                }
            } else {
                int nxt = min(nextA, nextL);
                if (nxt == inf)
                    break;
                t = nxt;
                if (nextL <= nextA) {
                    while (!pq.empty() && pq.top().t == t) {
                        cur -= pq.top().c;
                        pq.pop();
                    }
                } else {
                    q.push_back(i);
                    i++;
                }
            }
        }
    }

    For(j, n) cout << ans[j] << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    // cin >> T;
    while (T--)
        solve();
    return 0;
}
