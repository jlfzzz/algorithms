#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
using ordered_set = tree<int, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>;
using ordered_map = tree<int, int, less<>, rb_tree_tag, tree_order_statistics_node_update>;

constexpr int N = int(1e5 + 5);

namespace DEBUG {
    template<typename A, typename B>
    ostream &operator<<(ostream &os, const pair<A, B> &p) {
        return os << '(' << p.first << ", " << p.second << ')';
    }

    template<typename Tuple, size_t... Is>
    void print_tuple(ostream &os, const Tuple &t, index_sequence<Is...>) {
        ((os << (Is == 0 ? "" : ", ") << get<Is>(t)), ...);
    }

    template<typename... Args>
    ostream &operator<<(ostream &os, const tuple<Args...> &t) {
        os << '(';
        print_tuple(os, t, index_sequence_for<Args...>{});
        return os << ')';
    }

    template<typename T, typename = decltype(begin(declval<T>())), typename = enable_if_t<!is_same_v<T, string>>>
    ostream &operator<<(ostream &os, const T &v) {
        os << '{';
        bool first = true;
        for (auto &x: v) {
            if (!first)
                os << ", ";
            first = false;
            os << x;
        }
        return os << '}';
    }

    void debug_out() { cerr << endl; }

    template<typename Head, typename... Tail>
    void debug_out(Head H, Tail... T) {
        cerr << H;
        if (sizeof...(T))
            cerr << " ";
        debug_out(T...);
    }
} // namespace DEBUG

using namespace DEBUG;

#define dbg(...) cerr << "[L" << __LINE__ << " " << __func__ << " | " << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__)

int INIT = [] { return 0; }();

using pll = pair<long long, long long>;
#define i128 __int128_t
#define ull unsigned long long
constexpr int inf = 0x3f3f3f3f / 2;
using pii = pair<int, int>;
constexpr int MOD = int(1e9 + 7);
using ll = long long;

struct Node {
    ll val = 0;
};

class PST {
private:
    int n, ts;
    std::vector<int> lc, rc;
    std::vector<Node> tree;

    void newnode(int pre, int cur) {
        lc[cur] = lc[pre];
        rc[cur] = rc[pre];
        tree[cur] = tree[pre];
    }

    Node merge(const Node &left, const Node &right) { return Node{left.val + right.val}; }

    int _build(const std::vector<int> &arr, int l, int r) {
        int cur = ++ts;
        if (l == r) {
            tree[cur] = Node{arr[l]};
            return cur;
        }
        int m = (l + r) / 2;
        lc[cur] = _build(arr, l, m);
        rc[cur] = _build(arr, m + 1, r);
        tree[cur] = merge(tree[lc[cur]], tree[rc[cur]]);
        return cur;
    }

    int _update(int pre, int l, int r, int pos, ll val) {
        int cur = ++ts;
        newnode(pre, cur);
        if (l == r) {
            tree[cur].val += val;
            return cur;
        }
        int m = (l + r) / 2;
        if (pos <= m)
            lc[cur] = _update(lc[pre], l, m, pos, val);
        else
            rc[cur] = _update(rc[pre], m + 1, r, pos, val);

        tree[cur] = merge(tree[lc[cur]], tree[rc[cur]]);
        return cur;
    }

    ll _query(int cur, int pre, int l, int r, int ql, int qr) {
        if (ql > r || qr < l)
            return 0;
        if (ql <= l && r <= qr)
            return tree[cur].val - tree[pre].val;
        int m = (l + r) / 2;
        return _query(lc[cur], lc[pre], l, m, ql, qr) + _query(rc[cur], rc[pre], m + 1, r, ql, qr);
    }

    int _kth(int cur, int pre, int l, int r, int k) {
        if (l == r)
            return l;
        ll cnt = tree[lc[cur]].val - tree[lc[pre]].val;
        int m = (l + r) / 2;
        if (k <= cnt)
            return _kth(lc[cur], lc[pre], l, m, k);
        else
            return _kth(rc[cur], rc[pre], m + 1, r, k - (int) cnt);
    }

public:
    PST(int n) : n(n), ts(0), lc(20 * n + 5), rc(20 * n + 5), tree(20 * n + 5) {}

    int build(const std::vector<int> &arr) { return _build(arr, 1, n); }

    int update(int pre_version, int pos, ll val) { return _update(pre_version, 1, n, pos, val); }

    ll query(int cur_version, int pre_version, int l, int r) { return _query(cur_version, pre_version, 1, n, l, r); }

    int kth(int cur_version, int pre_version, int k) { return _kth(cur_version, pre_version, 1, n, k); }
};

class Solution {
public:
    vector<long long> minOperations(vector<int> &nums, int k, vector<vector<int>> &queries) {
        int n = nums.size();
        auto a = nums;
        ranges::sort(a);
        a.erase(unique(a.begin(), a.end()), a.end());
        vector<int> b{-1};
        b.insert(b.end(), a.begin(), a.end());
        int m = b.size() - 1;
        vector<int> valid(n + 1, 0);
        for (int i = 1; i < n; i++) {
            bool diff = (nums[i] % k) != (nums[i - 1] % k);
            valid[i] = valid[i - 1] + (diff ? 1 : 0);
        }
        valid[n] = valid[n - 1];

        auto Get = [&](int x) { return (int) (ranges::lower_bound(b, x) - b.begin()); };

        vector<int> pos(n);
        for (int i = 0; i < n; i++) {
            pos[i] = Get(nums[i]);
        }

        PST pstCnt(n), pstSum(n);
        vector<int> rootCnt(n + 1), rootSum(n + 1);
        rootCnt[0] = 0;
        rootSum[0] = 0;

        for (int i = 1; i <= n; i++) {
            int p = pos[i - 1];
            int val = nums[i - 1];
            rootCnt[i] = pstCnt.update(rootCnt[i - 1], p, 1);
            rootSum[i] = pstSum.update(rootSum[i - 1], p, val);
        }

        int q = queries.size();
        vector<ll> ans(q);

        for (int i = 0; i < q; i++) {
            int l = queries[i][0];
            int r = queries[i][1];

            int len = r - l + 1;
            if (valid[r] - valid[l] > 0) {
                ans[i] = -1;
                continue;
            }

            int rl = rootCnt[l];
            int rr = rootCnt[r + 1];
            int rl2 = rootSum[l];
            int rr2 = rootSum[r + 1];

            int kth = (len + 1) / 2;
            int p = pstCnt.kth(rr, rl, kth);
            ll v = b[p];

            ll lsum = pstSum.query(rr2, rl2, 1, p);
            ll lcnt = pstCnt.query(rr, rl, 1, p);

            ll sum = pstSum.query(rr2, rl2, 1, m);
            ll cnt = pstCnt.query(rr, rl, 1, m);

            ll rsum = sum - lsum;
            ll rcnt = cnt - lcnt;

            ll cost = (lcnt * v - lsum) + (rsum - rcnt * v);

            ans[i] = cost / k;
        }

        return ans;
    }
};

class Solution2 {
public:
    vector<long long> minOperations(vector<int> &nums, int k, vector<vector<int>> &queries) {
        int n = nums.size();
        auto a = nums;
        ranges::sort(a);
        a.erase(unique(a.begin(), a.end()), a.end());
        vector<int> b{-1};
        b.insert(b.end(), a.begin(), a.end());
        int m = b.size() - 1;

        vector<int> valid(n + 1, 0);
        for (int i = 1; i < n; i++) {
            bool diff = (nums[i] % k) != (nums[i - 1] % k);
            valid[i] = valid[i - 1] + (diff ? 1 : 0);
        }
        valid[n] = valid[n - 1];

        auto Get = [&](int x) { return ranges::lower_bound(b, x) - b.begin(); };

        vector<int> pos(n);
        for (int i = 0; i < n; i++) {
            pos[i] = Get(nums[i]);
        }

        const int B = max(1, (int) sqrt(m));
        const int nB = m / B + 2;

        vector<ll> bsum(nB, 0), bcnt(nB, 0);
        vector<ll> cnt(m + 2, 0), sum(m + 2, 0);

        ll total = 0;
        ll have = 0;

        struct Q {
            int l, r, id;
        };
        int q = queries.size();
        vector<Q> qs;
        for (int i = 0; i < q; i++) {
            qs.push_back({queries[i][0], queries[i][1], i});
        }

        ranges::sort(qs, [&](const Q &x, const Q &y) {
            int bx = x.l / B;
            int by = y.l / B;
            if (bx != by)
                return bx < by;
            return (bx & 1) ? (x.r < y.r) : (x.r > y.r);
        });

        auto add = [&](int x) {
            ll val = b[x];
            cnt[x]++;
            sum[x] += val;

            int bid = x / B;
            bcnt[bid]++;
            bsum[bid] += val;

            total += val;
            have++;
        };

        auto del = [&](int x) {
            ll val = b[x];

            cnt[x]--;
            sum[x] -= val;

            int bid = x / B;
            bcnt[bid]--;
            bsum[bid] -= val;

            total -= val;
            have--;
        };

        auto getKth = [&](int k) -> int {
            int bid = 0;
            while (bid < nB && k > bcnt[bid]) {
                k -= bcnt[bid];
                bid++;
            }
            int i = bid * B;
            int limit = min((bid + 1) * B, m + 1);
            while (i < limit) {
                if (k <= cnt[i])
                    return i;
                k -= cnt[i];
                i++;
            }
            return i;
        };

        auto getSum = [&](int x) -> pair<ll, ll> {
            int bid = x / B;
            ll c1 = 0;
            ll s1 = 0;

            for (int i = 0; i < bid; i++) {
                c1 += bcnt[i];
                s1 += bsum[i];
            }

            int start = bid * B;
            for (int i = start; i <= x; i++) {
                c1 += cnt[i];
                s1 += sum[i];
            }
            return {c1, s1};
        };

        vector<ll> ans(q);
        int nl = 0, nr = -1;

        for (auto [l, r, id]: qs) {
            int len = r - l + 1;

            if (valid[r] - valid[l] > 0) {
                ans[id] = -1;
                continue;
            }

            while (nl > l)
                add(pos[--nl]);
            while (nr < r)
                add(pos[++nr]);
            while (nl < l)
                del(pos[nl++]);
            while (nr > r)
                del(pos[nr--]);

            int kth = (len + 1) / 2;

            auto calc = [&](int idx) {
                int p = getKth(idx);
                ll v = b[p];

                auto [lcnt, lsum] = getSum(p);

                ll rcnt = have - lcnt;
                ll rsum = total - lsum;

                ll cost = (lcnt * v - lsum) + (rsum - rcnt * v);

                return cost;
            };

            ll c1 = calc(kth);
            ll c2 = 1e15;
            if (kth + 1 < len) {
                c2 = calc(kth + 1);
            }
            ll c3 = 1e15;
            if (kth - 1 >= 0) {
                c3 = calc(kth - 1);
            }

            ans[id] = min({c1, c2, c3}) / k;
        }

        return ans;
    }
};



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Solution sol1;
    ll n = 11;
    vector<int> nums1{}, nums{};
}
