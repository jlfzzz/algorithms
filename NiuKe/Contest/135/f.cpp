#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>


// 保持你的 using 和 define
using namespace std;
using ll = long long;
#define i128 __int128_t
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
const ll MOD2 = 4611686018427387847;
#define int ll // main 等函数的返回类型仍为 long long
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

// 辅助函数，用于打印 __int128_t 类型的整数
void print_i128(i128 n) {
    if (n == 0) {
        cout << "0";
        return;
    }
    string s = "";
    while (n > 0) {
        s += (n % 10) + '0';
        n /= 10;
    }
    reverse(s.begin(), s.end());
    cout << s;
}


void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    For(i, n) cin >> a[i];
    vector<pair<i128, ll>> ans(q); // 修改 ans 类型以存储 i128
    int block_size = sqrt(n);
    if (block_size == 0)
        block_size = 1;

    auto tmp_a = a;
    ranges::sort(tmp_a);
    tmp_a.erase(ranges::unique(tmp_a).begin(), tmp_a.end());

    vector<int> index_to_val(n);
    vector<int> id_to_weight(tmp_a.size());
    for (int i = 0; i < n; i++) {
        index_to_val[i] = ranges::lower_bound(tmp_a, a[i]) - tmp_a.begin();
    }
    for (size_t id = 0; id < tmp_a.size(); ++id) {
        id_to_weight[id] = tmp_a[id];
    }
    vector<int> cnt(tmp_a.size(), 0);

    i128 s = 0; // 使用 i128
    int max_color_id = -1;
    int min_color_id = -1;

    auto add = [&](int i) -> void {
        int v_id = index_to_val[i];

        if (max_color_id == -1) {
            max_color_id = v_id;
            min_color_id = v_id;
            cnt[v_id]++;
            return;
        }

        int original_val = id_to_weight[v_id];
        s += (i128) cnt[v_id] * original_val;
        cnt[v_id]++;

        i128 current_sum = (i128) cnt[v_id] * (cnt[v_id] - 1) / 2 * original_val;
        i128 max_sum = (i128) cnt[max_color_id] * (cnt[max_color_id] - 1) / 2 * id_to_weight[max_color_id];

        if (current_sum > max_sum) {
            max_color_id = v_id;
            min_color_id = v_id;
        } else if (current_sum == max_sum) {
            if (original_val < id_to_weight[min_color_id]) {
                min_color_id = v_id;
                max_color_id = v_id;
            }
        }
    };

    struct Query {
        int bid, l, r, qid;
    };

    vector<Query> queries;
    For(_, q) {
        int l, r;
        cin >> l >> r;
        l--, r--;

        if (r - l + 1 <= block_size) {
            i128 temp_s = 0;
            int temp_max_id = -1, temp_min_id = -1;
            vector<int> temp_cnt(tmp_a.size(), 0);

            for (int i = l; i <= r; i++) {
                int v_id = index_to_val[i];
                int original_val = id_to_weight[v_id];

                if (temp_max_id == -1) {
                    temp_max_id = v_id;
                    temp_min_id = v_id;
                    temp_cnt[v_id]++;
                } else {
                    temp_s += (i128) temp_cnt[v_id] * original_val;
                    temp_cnt[v_id]++;

                    i128 current_sum = (i128) temp_cnt[v_id] * (temp_cnt[v_id] - 1) / 2 * original_val;
                    i128 max_sum =
                        (i128) temp_cnt[temp_max_id] * (temp_cnt[temp_max_id] - 1) / 2 * id_to_weight[temp_max_id];

                    if (current_sum > max_sum) {
                        temp_max_id = v_id;
                        temp_min_id = v_id;
                    } else if (current_sum == max_sum) {
                        if (original_val < id_to_weight[temp_min_id]) {
                            temp_min_id = v_id;
                            temp_max_id = v_id;
                        }
                    }
                }
            }
            ans[_] = {temp_s, temp_min_id == -1 ? a[l] : id_to_weight[temp_min_id]};
            continue;
        }

        queries.emplace_back(l / block_size, l, r, _);
    }

    ranges::sort(queries, [](const Query &q1, const Query &q2) {
        if (q1.bid != q2.bid)
            return q1.bid < q2.bid;
        return q1.r < q2.r;
    });

    int global_r = -1;
    for (size_t i = 0; i < queries.size(); i++) {
        auto &q = queries[i];
        int bid = q.bid, l = q.l, r = q.r, qid = q.qid;
        int l0 = (bid + 1) * block_size;

        if (i == 0 || bid != queries[i - 1].bid) {
            global_r = l0;
            fill(cnt.begin(), cnt.end(), 0);
            s = 0;
            max_color_id = -1;
            min_color_id = -1;
        }

        while (global_r <= r) {
            add(global_r);
            global_r++;
        }

        i128 tmp_s = s;
        int tmp_max_col_id = max_color_id, tmp_min_col_id = min_color_id;

        for (int j = l; j < l0; j++) {
            add(j);
        }

        ans[qid] = {s, min_color_id == -1 ? a[l] : id_to_weight[min_color_id]};

        s = tmp_s;
        max_color_id = tmp_max_col_id;
        min_color_id = tmp_min_col_id;
        for (int j = l; j < l0; j++) {
            cnt[index_to_val[j]]--;
        }
    }

    for (auto &[x, y]: ans) {
        print_i128(x);
        cout << ' ' << y << '\n';
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    while (T--)
        solve();
    return 0;
}
