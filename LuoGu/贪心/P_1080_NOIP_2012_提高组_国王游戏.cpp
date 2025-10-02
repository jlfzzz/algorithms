#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 简化版高精度类（只支持必要操作）
class BigInt {
    vector<int> digits;
    static const int BASE = 1000000000; // 10^9

public:
    BigInt() : digits(1, 0) {}

    BigInt(int x) {
        if (x == 0)
            digits = {0};
        else {
            while (x > 0) {
                digits.push_back(x % BASE);
                x /= BASE;
            }
        }
    }

    BigInt &operator=(int x) {
        digits.clear();
        if (x == 0)
            digits = {0};
        else {
            while (x > 0) {
                digits.push_back(x % BASE);
                x /= BASE;
            }
        }
        return *this;
    }

    BigInt &operator*=(int x) {
        ll carry = 0;
        for (int i = 0; i < digits.size(); i++) {
            carry += (ll) digits[i] * x;
            digits[i] = carry % BASE;
            carry /= BASE;
        }
        while (carry > 0) {
            digits.push_back(carry % BASE);
            carry /= BASE;
        }
        return *this;
    }

    BigInt operator*(int x) const {
        BigInt res = *this;
        res *= x;
        return res;
    }

    // 除法（返回商）
    BigInt operator/(int x) const {
        BigInt res;
        res.digits.resize(digits.size());
        ll rem = 0;
        for (int i = digits.size() - 1; i >= 0; i--) {
            rem = rem * BASE + digits[i];
            res.digits[i] = rem / x;
            rem %= x;
        }
        // 去除前导零
        while (res.digits.size() > 1 && res.digits.back() == 0) {
            res.digits.pop_back();
        }
        return res;
    }

    bool operator>(const BigInt &other) const {
        if (digits.size() != other.digits.size()) {
            return digits.size() > other.digits.size();
        }
        for (int i = digits.size() - 1; i >= 0; i--) {
            if (digits[i] != other.digits[i]) {
                return digits[i] > other.digits[i];
            }
        }
        return false;
    }

    // 转换为 long long（注意可能溢出）
    operator long long() const {
        long long res = 0;
        for (int i = digits.size() - 1; i >= 0; i--) {
            res = res * BASE + digits[i];
        }
        return res;
    }

    // 输出
    friend ostream &operator<<(ostream &os, const BigInt &num) {
        os << num.digits.back();
        for (int i = num.digits.size() - 2; i >= 0; i--) {
            os << setw(9) << setfill('0') << num.digits[i];
        }
        return os;
    }
};

void solve() {
    int n;
    cin >> n;
    int a, b;
    cin >> a >> b;

    vector<pair<int, int>> v(n);
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        v[i] = {x, y};
    }

    sort(v.begin(), v.end(), [](auto &a, auto &b) { return a.first * a.second < b.first * b.second; });

    BigInt pre = a; // 初始值为国王的左手数
    BigInt ans = 0;

    for (auto &[x, y]: v) {
        BigInt current = pre / y;
        if (current > ans) {
            ans = current;
        }
        pre = pre * x;
    }

    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}
