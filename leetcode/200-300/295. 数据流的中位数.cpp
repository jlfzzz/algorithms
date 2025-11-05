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

struct DS {
    multiset<int>::iterator it;
    multiset<int> mset;

    void Add(int x) {
        if (mset.empty()) {
            mset.insert(x);
            it = mset.begin();
            return;
        }

        int med = *it;
        int sz = mset.size();
        mset.insert(x);


        if (x >= med) {
            if (sz % 2 == 0) {
                it++;
            }
        } else {
            if (sz % 2) {
                it--;
            }
        }
    }
};

class MedianFinder {
public:
    DS ds;
    MedianFinder() {}

    void addNum(int num) { ds.Add(num); }

    double findMedian() {
        if (ds.mset.size() & 1) {
            return *(ds.it);
        }
        return (*(ds.it) + *(next(ds.it))) / 2.0;
    }
};



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // Solution sol1;
    // ll n = 11;
    // vector<int> nums1{}, nums{};
}
