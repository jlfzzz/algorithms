#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int ll

ll fac[20];

void init() {
    fac[0] = 1;
    for (int i = 1; i < 20; ++i) {
        fac[i] = fac[i - 1] * i;
    }
}

void dfs(int i, int ki, ll si, int K, ll S, const vector<int> &v, map<int, map<ll, int>> &res) {
    if (si > S || ki > K) {
        return;
    }
    if (i == v.size()) {
        res[ki][si]++;
        return;
    }

    dfs(i + 1, ki, si, K, S, v, res);
    dfs(i + 1, ki, si + v[i], K, S, v, res);

    if (v[i] < 20) {
        dfs(i + 1, ki + 1, si + fac[v[i]], K, S, v, res);
    }
}

void solve() {
    int N, K, S;
    cin >> N >> K >> S;

    vector<int> a(N / 2);
    vector<int> b(N - N / 2);
    for (int i = 0; i < N / 2; ++i)
        cin >> a[i];
    for (int i = 0; i < N - N / 2; ++i)
        cin >> b[i];

    // DFS计算左右两半的结果，这部分不变
    map<int, map<ll, int>> res1, res2;
    dfs(0, 0, 0, K, S, a, res1);
    dfs(0, 0, 0, K, S, b, res2);

    // 【改动部分】删除了对 res2 的预处理和前缀和优化

    ll ans = 0;
    // 遍历左半边的所有结果
    for (auto const &p1: res1) {
        int k1 = p1.first;
        for (auto const &p2: p1.second) {
            ll s1 = p2.first;
            int c1 = p2.second;

            ll target_s = S - s1;
            int rem_k = K - k1;

            if (rem_k < 0)
                continue;

            // 【改动部分】使用暴力循环代替二分查找
            // 遍历右半边所有可能的 k2 (0 到 rem_k)
            for (int k2 = 0; k2 <= rem_k; ++k2) {
                // 检查对于当前 k2，res2 中是否有记录
                if (res2.count(k2)) {
                    // 获取 k2 对应的 sum->count map
                    auto const &sum_map2 = res2.at(k2);
                    // 检查这个 map 中是否存在我们需要的 target_s
                    if (sum_map2.count(target_s)) {
                        // 如果存在，累加方案数
                        ans += (ll) c1 * sum_map2.at(target_s);
                    }
                }
            }
        }
    }

    cout << ans << '\n';
}

// void solve() {
//     int N, K, S;
//     cin >> N >> K >> S;

//     vector<int> a(N / 2);
//     vector<int> b(N - N / 2);
//     for (int i = 0; i < N / 2; ++i)
//         cin >> a[i];
//     for (int i = 0; i < N - N / 2; ++i)
//         cin >> b[i];

//     map<int, map<ll, int>> res1, res2;
//     dfs(0, 0, 0, K, S, a, res1);
//     dfs(0, 0, 0, K, S, b, res2);

//     map<ll, vector<pair<int, int>>> R;
//     for (auto const &p1: res2) {
//         for (auto const &p2: p1.second) {
//             R[p2.first].push_back({p1.first, p2.second});
//         }
//     }

//     for (auto &p: R) {
//         auto &vec = p.second;
//         sort(vec.begin(), vec.end());
//         for (size_t i = 1; i < vec.size(); ++i) {
//             vec[i].second += vec[i - 1].second;
//         }
//     }

//     ll ans = 0;
//     for (auto const &p1: res1) {
//         int k1 = p1.first;
//         for (auto const &p2: p1.second) {
//             ll s1 = p2.first;
//             int c1 = p2.second;

//             ll target_s = S - s1;
//             int rem_k = K - k1;

//             if (rem_k < 0)
//                 continue;

//             if (R.count(target_s)) {
//                 auto const &vec = R.at(target_s);
//                 auto it = upper_bound(vec.begin(), vec.end(), make_pair(rem_k, (int) 2e9));

//                 if (it != vec.begin()) {
//                     it--;
//                     ans += (ll) c1 * it->second;
//                 }
//             }
//         }
//     }

//     cout << ans << '\n';
// }

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();
    return 0;
}
