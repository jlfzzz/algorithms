#include <iostream>
#include <string>
#include <utility> // For std::pair

// Your defines and using statements
using namespace std;
using ll = long long;
#define i128 __int128_t
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
const ll MOD2 = 4611686018427387847;
#define int ll // Using long long for int as in your snippet

// Recursive function to find number from coordinates
ll get_val(int n, ll r, ll c) {
    if (n == 1) {
        if (r == 1 && c == 1)
            return 1;
        if (r == 2 && c == 2)
            return 2;
        if (r == 2 && c == 1)
            return 3;
        if (r == 1 && c == 2)
            return 4;
    }

    ll half = 1LL << (n - 1);
    ll quad_size = 1LL << (2 * n - 2);

    // Top-Left
    if (r <= half && c <= half) {
        return get_val(n - 1, r, c);
    }
    // Bottom-Right
    if (r > half && c > half) {
        return quad_size + get_val(n - 1, r - half, c - half);
    }
    // Bottom-Left
    if (r > half && c <= half) {
        return 2 * quad_size + get_val(n - 1, r - half, c);
    }
    // Top-Right
    // if (r <= half && c > half)
    return 3 * quad_size + get_val(n - 1, r, c - half);
}

// Recursive function to find coordinates from number
pll get_coords(int n, ll d) {
    if (n == 1) {
        if (d == 1)
            return {1, 1};
        if (d == 2)
            return {2, 2};
        if (d == 3)
            return {2, 1};
        if (d == 4)
            return {1, 2};
    }

    ll half = 1LL << (n - 1);
    ll quad_size = 1LL << (2 * n - 2);

    // Top-Left
    if (d <= quad_size) {
        return get_coords(n - 1, d);
    }
    // Bottom-Right
    if (d <= 2 * quad_size) {
        pll sub_coords = get_coords(n - 1, d - quad_size);
        return {sub_coords.first + half, sub_coords.second + half};
    }
    // Bottom-Left
    if (d <= 3 * quad_size) {
        pll sub_coords = get_coords(n - 1, d - 2 * quad_size);
        return {sub_coords.first + half, sub_coords.second};
    }
    // Top-Right
    // if (d <= 4 * quad_size)
    pll sub_coords = get_coords(n - 1, d - 3 * quad_size);
    return {sub_coords.first, sub_coords.second + half};
}


void solve() {
    int n, q;
    cin >> n >> q;

    For(i, q) {
        string s;
        cin >> s;
        if (s == "->") {
            ll x, y;
            cin >> x >> y;
            cout << get_val(n, x, y) << '\n';
        } else { // s == "<-"
            ll d;
            cin >> d;
            pll coords = get_coords(n, d);
            cout << coords.first << " " << coords.second << '\n';
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // The problem statement says there are multiple test cases.
    int T = 1;
    cin >> T; // Uncomment if there's a t in the input
    while (T--)
        solve();
    return 0;
}
