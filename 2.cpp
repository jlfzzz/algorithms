#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
constexpr int MOD = int(1e9 + 7);
#define i128 __int128_t
#define ull unsigned long long
constexpr int inf = 0x3f3f3f3f / 2;

vector<int> random_array(int n, int lo, int hi);

void func1() {
    ll s = 9;

    while (true) {
        if (s % 10 == 0) {
            break;
        }

        s += s % 10;
        cout << s << endl;
        this_thread::sleep_for(chrono::duration<double>(0.1));
    }

    cout << s << endl;
}

int main() { func1(); }






vector<int> random_array(int n, int lo, int hi) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(lo, hi);

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i] = dist(gen);
    }
    return arr;
}
