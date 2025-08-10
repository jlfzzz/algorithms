#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
const ll MOD2 = 4611686018427387847;
#define int ll
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    std::vector<int> b(n);

    for (int i = 0; i < n; ++i)
        std::cin >> a[i];
    for (int i = 0; i < n; ++i)
        std::cin >> b[i];
    std::vector<std::pair<int, int>> operations;

    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (a[i] == b[i]) {
            cnt++;
        }
    }
    if (cnt > 1 || (cnt == 1 && n % 2 == 0)) {
        std::cout << -1 << '\n';
        return;
    }

    if (cnt == 1 && n % 2 != 0) {
        int pos = -1;
        for (int i = 0; i < n; ++i) {
            if (a[i] == b[i]) {
                pos = i;
                break;
            }
        }
        if (pos != n / 2) {
            // Store the operation instead of printing it
            operations.emplace_back(pos + 1, n / 2 + 1);
            std::swap(a[pos], a[n / 2]);
            std::swap(b[pos], b[n / 2]);
        }
    }

    unordered_map<int, pii> mp;
    map<pii, int> pair_to_i;
    for (int i = 0; i < n; i++) {
        mp[i] = {a[i], b[i]};
        pair_to_i[{a[i], b[i]}] = i;
    }

    for (auto &[k, v]: pair_to_i) {
        if (!pair_to_i.contains({k.second, k.first})) {
            cout << -1 << '\n';
            return;
        }
    }

    for (int i = 0; i < n / 2; i++) {
        // 当前在 i 位置的配对
        pii current_pair = {a[i], b[i]};
        // 我们需要的、应该在 n-1-i 位置的配对
        pii reverse_pair = {b[i], a[i]};

        // 找到这个反向配对现在在哪
        int pos_of_reverse = pair_to_i[reverse_pair];
        // 它的目标位置
        int target_pos = n - 1 - i;

        // 如果它不在正确的目标位置上
        if (pos_of_reverse != target_pos) {
            // 记下原来在目标位置的那个配对，因为它马上要被移动了
            pii pair_at_target = {a[target_pos], b[target_pos]};

            // 1. 记录操作（索引要 +1）
            operations.emplace_back(pos_of_reverse + 1, target_pos + 1);

            // 2. 真正地交换数组元素
            std::swap(a[pos_of_reverse], a[target_pos]);
            std::swap(b[pos_of_reverse], b[target_pos]);

            // 3. 更新 map，告诉 map 这两个配对的新家在哪
            pair_to_i[reverse_pair] = target_pos;
            pair_to_i[pair_at_target] = pos_of_reverse;
        }
    }

    // --- Final Output Section ---
    // 1. Print the total number of operations
    std::cout << operations.size() << '\n';

    // 2. Print each stored operation on a new line
    for (const auto &op: operations) {
        std::cout << op.first << ' ' << op.second << '\n';
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
