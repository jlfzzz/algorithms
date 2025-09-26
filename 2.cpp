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
    int n = 10;
    int k = 100;

    vector<int> arr = {1, 2, 3, 4, 5};
    vector<int> random_arr = random_array(n, 1, 100);

    
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
