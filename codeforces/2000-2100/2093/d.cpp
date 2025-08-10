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

// // Recursive function to find number from coordinates
// ll get_val(int n, ll r, ll c) {
//     if (n == 1) {
//         if (r == 1 && c == 1)
//             return 1;
//         if (r == 2 && c == 2)
//             return 2;
//         if (r == 2 && c == 1)
//             return 3;
//         if (r == 1 && c == 2)
//             return 4;
//     }

//     ll half = 1LL << (n - 1);
//     ll quad_size = 1LL << (2 * n - 2);

//     // Top-Left
//     if (r <= half && c <= half) {
//         return get_val(n - 1, r, c);
//     }
//     // Bottom-Right
//     if (r > half && c > half) {
//         return quad_size + get_val(n - 1, r - half, c - half);
//     }
//     // Bottom-Left
//     if (r > half && c <= half) {
//         return 2 * quad_size + get_val(n - 1, r - half, c);
//     }
//     // Top-Right
//     // if (r <= half && c > half)
//     return 3 * quad_size + get_val(n - 1, r, c - half);
// }

// // Recursive function to find coordinates from number
// pll get_coords(int n, ll d) {
//     if (n == 1) {
//         if (d == 1)
//             return {1, 1};
//         if (d == 2)
//             return {2, 2};
//         if (d == 3)
//             return {2, 1};
//         if (d == 4)
//             return {1, 2};
//     }

//     ll half = 1LL << (n - 1);
//     ll quad_size = 1LL << (2 * n - 2);

//     // Top-Left
//     if (d <= quad_size) {
//         return get_coords(n - 1, d);
//     }
//     // Bottom-Right
//     if (d <= 2 * quad_size) {
//         pll sub_coords = get_coords(n - 1, d - quad_size);
//         return {sub_coords.first + half, sub_coords.second + half};
//     }
//     // Bottom-Left
//     if (d <= 3 * quad_size) {
//         pll sub_coords = get_coords(n - 1, d - 2 * quad_size);
//         return {sub_coords.first + half, sub_coords.second};
//     }
//     // Top-Right
//     // if (d <= 4 * quad_size)
//     pll sub_coords = get_coords(n - 1, d - 3 * quad_size);
//     return {sub_coords.first, sub_coords.second + half};
// }


// void solve() {
//     int n, q;
//     cin >> n >> q;

//     For(i, q) {
//         string s;
//         cin >> s;
//         if (s == "->") {
//             ll x, y;
//             cin >> x >> y;
//             cout << get_val(n, x, y) << '\n';
//         } else { // s == "<-"
//             ll d;
//             cin >> d;
//             pll coords = get_coords(n, d);
//             cout << coords.first << " " << coords.second << '\n';
//         }
//     }
// }

void solve() {
    int n, q;
    cin >> n >> q;

    auto get_val = [](this auto &&get_val, int power, int x, int y) -> int {
        if (power == 1) {
            if (x == 1 and y == 1) {
                return 1;
            } else if (x == 1 and y == 2) {
                return 4;
            } else if (x == 2 and y == 2) {
                return 2;
            } else {
                return 3;
            }
        }

        int half = 1ll << (power - 1);
        int half_total = 1ll << (2 * power - 2);

        if (x <= half and y <= half) {
            return get_val(power - 1, x, y);
        } else if (x > half and y > half) {
            return get_val(power - 1, x - half, y - half) + half_total;
        } else if (x > half and y <= half) {
            return get_val(power - 1, x - half, y) + 2 * half_total;
        } else {
            return get_val(power - 1, x, y - half) + 3 * half_total;
        }
    };

    auto get_coords = [](this auto &&get_coords, int power, int d) -> pii {
        if (power == 1) {
            if (d == 1) {
                return {1, 1};
            } else if (d == 2) {
                return {2, 2};
            } else if (d == 3) {
                return {2, 1};
            } else {
                return {1, 2};
            }
        }

        int half_total = 1ll << (2 * power - 2);
        int half = 1ll << (power - 1);

        if (d <= half_total) {
            return get_coords(power - 1, d);
        } else if (d <= 2 * half_total) {
            auto [x, y] = get_coords(power - 1, d - half_total);
            return {x + half, y + half};
        } else if (d <= 3 * half_total) {
            auto [x, y] = get_coords(power - 1, d - 2 * half_total);
            return {x + half, y};
        } else {
            auto [x, y] = get_coords(power - 1, d - 3 * half_total);
            return {x, y + half};
        }
    };

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
