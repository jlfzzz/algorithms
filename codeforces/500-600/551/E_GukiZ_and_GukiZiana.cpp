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

void init() {}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    For(i, n) cin >> a[i];

    int b_size = (int) sqrt(n);
    if (b_size == 0)
        b_size = 1;
    int blocks = (n + b_size - 1) / b_size;
    vector<int> diff(blocks, 0);

    // 优化后的数据结构：按值排序的vector
    vector<vector<pii>> blocks_sorted(blocks);

    For(i, n) { blocks_sorted[i / b_size].emplace_back(a[i], i); }
    For(i, blocks) { sort(blocks_sorted[i].begin(), blocks_sorted[i].end()); }

    // 重构块的辅助函数
    auto rebuild_block = [&](int bid) {
        // 1. 将懒惰标记应用到原始数组 a
        for (int i = bid * b_size; i < (bid + 1) * b_size && i < n; ++i) {
            a[i] += diff[bid];
        }
        diff[bid] = 0;

        // 2. 清空并重建排序后的vector
        blocks_sorted[bid].clear();
        for (int i = bid * b_size; i < (bid + 1) * b_size && i < n; ++i) {
            blocks_sorted[bid].emplace_back(a[i], i);
        }
        sort(blocks_sorted[bid].begin(), blocks_sorted[bid].end());
    };

    For(i, q) {
        int type;
        cin >> type;
        if (type == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            l--, r--;

            int l_bid = l / b_size;
            int r_bid = r / b_size;

            if (l_bid == r_bid) {
                rebuild_block(l_bid);
                for (int j = l; j <= r; j++)
                    a[j] += x;
                rebuild_block(l_bid);
            } else {
                rebuild_block(l_bid);
                for (int j = l; j < (l_bid + 1) * b_size; j++)
                    a[j] += x;
                rebuild_block(l_bid);

                for (int j = l_bid + 1; j < r_bid; j++)
                    diff[j] += x;

                rebuild_block(r_bid);
                for (int j = r_bid * b_size; j <= r; j++)
                    a[j] += x;
                rebuild_block(r_bid);
            }
        } else {
            int y;
            cin >> y;

            int first = -1, last = -1;

            for (int bid = 0; bid < blocks; ++bid) {
                int target_val = y - diff[bid];
                auto &block = blocks_sorted[bid];

                auto it_low = lower_bound(block.begin(), block.end(), make_pair(target_val, -1LL));
                auto it_high = upper_bound(block.begin(), block.end(), make_pair(target_val, n + 1LL));

                if (it_low != it_high) {
                    int block_min_idx = n, block_max_idx = -1;
                    for (auto it = it_low; it != it_high; ++it) {
                        block_min_idx = min(block_min_idx, it->second);
                        block_max_idx = max(block_max_idx, it->second);
                    }

                    if (first == -1)
                        first = block_min_idx;
                    else
                        first = min(first, block_min_idx);
                    last = max(last, block_max_idx);
                }
            }

            if (first != -1) {
                cout << last - first << '\n';
            } else {
                cout << -1 << '\n';
            }
        }
    }
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
