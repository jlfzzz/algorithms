#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int ll
constexpr long long INF = 1e18;

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<int> a(n), b(m);
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    for (int i = 0; i < m; ++i)
        cin >> b[i];

    // 映射：值 -> 在a中的排名（0-indexed）
    vector<int> order(n + 1);
    for (int i = 0; i < n; ++i)
        order[a[i]] = i;

    // 每个排名在b中第一次出现的位置（初始为INF）
    vector<int> first_occ(n, INF);
    // 每个值在b中的出现位置（用于快速查找下一个出现）
    vector<set<int>> occ_by_value(n + 1);
    for (int i = 0; i < m; ++i) {
        occ_by_value[b[i]].insert(i);
        int rk = order[b[i]];
        if (first_occ[rk] > i)
            first_occ[rk] = i;
    }

    int bad_pairs = 0;
    auto check_pair = [&](int i) {
        if (i < 0 || i >= n - 1)
            return;
        if (first_occ[i] > first_occ[i + 1]) {
            bad_pairs++;
        }
    };

    auto uncheck_pair = [&](int i) {
        if (i < 0 || i >= n - 1)
            return;
        if (first_occ[i] > first_occ[i + 1]) {
            bad_pairs--;
        }
    };

    // 初始化检查所有相邻对
    for (int i = 0; i < n - 1; ++i) {
        check_pair(i);
    }

    auto output = [&]() { cout << (bad_pairs == 0 ? "YA\n" : "TIDAK\n"); };

    output();

    while (q--) {
        int s, t;
        cin >> s >> t;
        --s;
        int old_val = b[s];
        int new_val = t;

        if (old_val == new_val) {
            output();
            continue;
        }

        int old_rk = order[old_val];
        int new_rk = order[new_val];

        // 收集所有受影响的相邻对
        vector<int> affected;
        affected.push_back(old_rk - 1);
        affected.push_back(old_rk);
        affected.push_back(new_rk - 1);
        affected.push_back(new_rk);
        sort(affected.begin(), affected.end());
        affected.erase(unique(affected.begin(), affected.end()), affected.end());

        // 移除旧贡献
        for (int i: affected) {
            uncheck_pair(i);
        }

        // 更新数据结构
        // 移除 old_val 在位置 s 的影响
        occ_by_value[old_val].erase(s);
        if (occ_by_value[old_val].empty()) {
            first_occ[old_rk] = INF;
        } else {
            first_occ[old_rk] = *occ_by_value[old_val].begin();
        }

        // 添加 new_val 在位置 s 的影响
        occ_by_value[new_val].insert(s);
        first_occ[new_rk] = *occ_by_value[new_val].begin();

        // 添加新贡献
        for (int i: affected) {
            check_pair(i);
        }

        output();
        b[s] = new_val;
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
