#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, ans = 0;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; i++)
        cin >> p[i];
    for (int i = 0; i < n; i++) {
        int left = 0, right = 0;
        for (int j = 0; j < i; j++)
            if (p[j] > p[i])
                left++;
        for (int j = i + 1; j < n; j++)
            if (p[j] > p[i])
                right++;
        ans += min(left, right);
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--)
        solve();
}


template<typename T>
struct FenwickTree {
    int size;
    std::vector<T> tree;

    FenwickTree(int n) : size(n), tree(n + 1, 0) {}

    void update(int idx, T val) {
        for (; idx <= size; idx += idx & -idx) {
            tree[idx] += val;
        }
    }

    T query(int idx) {
        if (idx < 1)
            return 0;
        T sum = 0;
        for (; idx > 0; idx -= idx & -idx) {
            sum += tree[idx];
        }
        return sum;
    }

    void clear() { tree.assign(size + 1, 0); }
};

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> p(n);
    for (int i = 0; i < n; i++) {
        std::cin >> p[i];
    }

    FenwickTree<int> bit(n);
    std::vector<int> left_counts(n);
    std::vector<int> right_counts(n);

    // Pass 1: Calculate all left counts
    for (int i = 0; i < n; ++i) {
        int val = p[i];
        int elements_before = i;
        int smaller_or_equal_before = bit.query(val);
        left_counts[i] = elements_before - smaller_or_equal_before;
        bit.update(val, 1);
    }

    // Pass 2: Calculate all right counts
    bit.clear(); // Reset the Fenwick tree
    for (int i = n - 1; i >= 0; --i) {
        int val = p[i];
        int elements_after = (n - 1 - i);
        int smaller_or_equal_after = bit.query(val);
        right_counts[i] = elements_after - smaller_or_equal_after;
        bit.update(val, 1);
    }

    // Final calculation
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        ans += std::min(left_counts[i], right_counts[i]);
    }

    std::cout << ans << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
