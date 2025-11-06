#include <iostream>
#include <vector>
using namespace std;
#define ll long long
ll revs(ll x) {
    ll ans = 0;
    while (x) {
        ans = ans * 10 + x % 10;
        x /= 10; // 去掉最后 1 位
    }
    return ans;
}
bool check(ll n, int a) // 检查回文数
{
    vector<int> d; // 储存 n 的 a 进制
    while (n) {
        d.push_back(n % a);
        n /= a;
    }
    int l = 0, r = d.size() - 1;
    while (l < r) // 逐位对比，判断回文数
    {
        if (d[l] != d[r])
            return 0;
        l++;
        r--;
    }
    return 1;
}
ll bs[20];
void init2b() // 初始化 10^i
{
    bs[0] = 1;
    for (int i = 1; i <= 12; i++)
        bs[i] = bs[i - 1] * 10;
}
ll solve(ll n, int a) // 生成回文数并检查
{
    int l = to_string(n).size();
    ll ans = 0;
    for (int d = 1; d <= l; d++) {
        int k = (d + 1) / 2;
        ll leftl = bs[k - 1];
        ll leftr = bs[k] - 1;
        for (ll left = leftl; left <= leftr; left++) {
            ll num;
            if (d % 2 == 0) {
                ll rev = revs(left);
                num = left * bs[k] + rev;
            } else {
                ll rev = revs(left / 10); // 去掉最后 1 位
                num = left * bs[k - 1] + rev;
            }
            if (d == l && num > n)
                break; // 位数与 n 相等时超过 n 可直接结束循环
            if (num > n)
                continue; // 回文数必须小于 n
            if (check(num, a))
                ans += num;
        }
    }
    return ans;
}
int main() {
    int a;
    ll n;
    cin >> a >> n;
    init2b();
    cout << solve(n, a);
    return 0;
}
