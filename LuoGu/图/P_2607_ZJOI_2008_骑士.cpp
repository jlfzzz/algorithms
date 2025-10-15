#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000100;
struct pp {
    int next, to;
} a[N];
int head[N], fa[N];
ll s[N], n, tot, ans, f[N][2];
bool v[N], v1[N];

void add(int x, int y) {
    a[++tot].next = head[x];
    a[tot].to = y;
    head[x] = tot;
    fa[y] = x;
}

void ss(int x) {
    v[x] = 1;
    f[x][1] = s[x];
    for (int i = head[x]; i; i = a[i].next) {
        if (v[a[i].to] == 0) {
            ss(a[i].to);
            f[x][0] += max(f[a[i].to][1], f[a[i].to][0]);
            f[x][1] += f[a[i].to][0];
        }
    }
}

void dp(ll x) {
    int root;
    for (root = x; v1[root] == 0; root = fa[root]) { // 寻找环，该循环会在有环的情况下--退出；^ ^
        v1[root] = 1; // 标记一下
    } // cout<<root<<endl;
    ss(root);
    x = fa[root]; // cout<<x<<endl;
    f[x][1] = f[x][0];
    for (x = fa[x]; x != root; x = fa[x]) {
        f[x][1] = s[x];
        f[x][0] = 0;
        for (int j = head[x]; j; j = a[j].next) {
            f[x][1] += f[a[j].to][0];
            f[x][0] += max(f[a[j].to][1], f[a[j].to][0]);
        }
    } // cout<<f[root][1]<<" "<<f[root][0]<<endl;
    f[root][1] = s[root];
    for (int i = head[root]; i; i = a[i].next) {
        f[root][1] += f[a[i].to][0];
    } // cout<<f[root][1]<<endl;
    ans += max(f[root][1], f[root][0]);
}

int main() {
    scanf("%lld", &n);
    ll q;
    for (int i = 1; i <= n; i++) {
        scanf("%lld%lld", &s[i], &q);
        add(q, i);
        // cout<<q<<"-->"<<i<<endl;
    }
    for (int i = 1; i <= n; i++) {
        if (v[i] == 0)
            dp(i);
    }
    printf("%lld", ans);
    return 0;
}
