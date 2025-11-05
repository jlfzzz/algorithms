#include <bits/stdc++.h>
using namespace std;

constexpr int N = int(1e5 + 5);

int INIT = [] { return 0; }();

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using ordered_set = tree<int, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>;
using ordered_map = tree<int, int, less<>, rb_tree_tag, tree_order_statistics_node_update>;
using pll = pair<long long, long long>;
#define i128 __int128_t
#define ull unsigned long long
constexpr int inf = 0x3f3f3f3f / 2;
using pii = pair<int, int>;
constexpr int MOD = int(1e9 + 7);
using ll = long long;

using ll = long long;
struct DS {
    priority_queue<ll> left;
    priority_queue<ll, vector<ll>, greater<>> right;
    multiset<ll> L, R;

    void clean() {
        while (!left.empty() && L.contains(left.top())) {
            ll t = left.top();
            left.pop();
            L.erase(L.find(t));
        }
        while (!right.empty() && R.contains(right.top())) {
            ll t = right.top();
            right.pop();
            R.erase(R.find(t));
        }
    }

    void reBalance() {
        while (true) {
            clean();
            ll d = (left.size() - L.size()) - (right.size() - R.size());
            if (d > 1) {
                right.push(left.top());
                left.pop();
            } else if (d < 0) {
                left.push(right.top());
                right.pop();
            } else {
                break;
            }
        }
    }

    void add(ll x) {
        reBalance();
        if (left.size() - L.size() == right.size() - R.size()) {
            right.push(x);
            left.push(right.top());
            right.pop();
        } else {
            left.push(x);
            right.push(left.top());
            left.pop();
        }
    }

    void del(ll x) {
        reBalance();
        if (left.empty()) {
            R.insert(x);
            return;
        }

        if (x <= left.top()) {
            L.insert(x);
        } else {
            R.insert(x);
        }
    }

    double query() {
        reBalance();

        double res = 0;
        if (left.size() - L.size() == right.size() - R.size()) {
            res = (left.top() + right.top()) / 2.0;
        } else {
            res = left.top();
        }

        return res;
    }
};

class Solution {
public:
    vector<double> medianSlidingWindow(vector<int> &nums, int k) {
        DS ds;
        vector<double> ans;
        int n = nums.size();

        int r = 0;
        for (int i = 0; i + k - 1 < n; i++) {
            while (r < n && r <= i + k - 1) {
                ds.add(nums[r]);
                r++;
            }
            ans.push_back(ds.query());
            ds.del(nums[i]);
        }

        return ans;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // Solution sol1;
    // ll n = 11;
    // vector<int> nums1{}, nums{};
}
