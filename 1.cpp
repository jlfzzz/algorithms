#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
const char nl = '\n';

using pii = pair<ll, ll>;
#define pb push_back
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
constexpr int inf = 0x3f3f3f3f / 2;

void solve() {
    ll n;
    cin >> n;
    vector<int> allTime;
    vector<pii> people(n + 1);

    struct Info {
        int l, r, f, id;
    };

    for (int i = 1; i <= n; i++) {
        int s, t;
        cin >> s >> t;
        allTime.pb(s);
        allTime.pb(t);

        people[i] = {s, t};
    }
    int m;
    cin >> m;
    vector<Info> activities(m + 1);
    for (int i = 1; i <= m; i++) {
        int x, y, f;
        cin >> x >> y >> f;

        allTime.pb(x);
        allTime.pb(y);
        activities[i] = {x, y, f, i};
    }

    sort(all(allTime));
    allTime.erase(unique(all(allTime)), allTime.end());

    // for (int x: allTime) {
    //     cout << x << '\n';
    // }

    auto getId = [&](int pos) { return lower_bound(all(allTime), pos) - allTime.begin() + 1; };

    struct Node {
        int mx;
    };

    map<int, set<int>> left;

    // cout << activities.size() << '\n';

    for (int j = 1; j <= m; j++) {
        auto &[x, y, f, id] = activities[j];
        int i = getId(y);
        // cout << i << '\n';
        left[i].insert(f);
    }


    int N = allTime.size();
    vector<Node> tree(4 * N + 100);

    auto merge = [&](Node &a, Node &b) -> Node { return {max(a.mx, b.mx)}; };

    auto build = [&](auto &&bd, int o, int l, int r) -> void {
        if (l == r) {
            auto it = left.find(l);
            if (it == left.end()) {
                tree[o] = {-inf};
            } else {
                // cout << "l is " << l << "val is " << *it->second.rbegin() << '\n';
                tree[o] = {*it->second.rbegin()};
            }
            return;
        }

        int m = (l + r) / 2;
        bd(bd, o * 2, l, m);
        bd(bd, o * 2 + 1, m + 1, r);
        tree[o] = merge(tree[o * 2], tree[o * 2 + 1]);
    };

    build(build, 1, 1, N);

    auto update = [&](auto &&upd, int o, int l, int r, int pos, int val) -> void {
        if (l == r) {
            auto it = left.find(l);
            if (it != left.end()) {
                auto &st = it->second;
                st.erase(val);

                if (st.empty()) {
                    tree[o] = {-inf};
                } else {
                    tree[o] = {*st.rbegin()};
                }
            }
            return;
        }

        int m = (l + r) / 2;
        if (pos <= m) {
            upd(upd, o * 2, l, m, pos, val);
        } else {
            upd(upd, o * 2 + 1, m + 1, r, pos, val);
        }
        tree[o] = merge(tree[o * 2], tree[o * 2 + 1]);
    };

    auto query = [&](auto &&q, int o, int l, int r, int ql, int qr) -> int {
        if (ql > r || qr < l) {
            return -inf;
        }

        if (ql >= l && qr <= r) {
            return tree[o].mx;
        }

        int m = (l + r) / 2;
        return max(q(q, o * 2, l, m, ql, qr), q(q, o * 2 + 1, m + 1, r, ql, qr));
    };

    vector<vector<pii>> ev1(N + 1);
    vector<vector<Info>> ev2(N + 1);

    for (int i = 1; i <= n; i++) {
        auto &[s, t] = people[i];

        int j = getId(s);
        int k = getId(t);

        ev1[j].eb(k, i);
    }

    for (int i = 1; i <= m; i++) {
        auto &[x, y, f, id] = activities[i];

        int j = getId(x);
        int k = getId(y);

        ev2[j].pb({x, k, f, id});
    }

    vector<int> ans(n + 1);
    for (int i = 1; i <= N; i++) {
        for (auto &[r, id]: ev1[i]) {
            int mx = query(query, 1, 1, N, i, r);
            ans[id] = mx;
        }

        for (auto &[x, y, f, id]: ev2[i]) {
            update(update, 1, 1, N, y, f);
        }
    }

    int sum = 0;
    for (int i = 1; i <= n; i++) {
        cout << "i is" << i << " ans[i] is " << ans[i] << '\n';
        if (ans[i] != -inf) {
            sum += ans[i];
        }
    }

    cout << sum << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
