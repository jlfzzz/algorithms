#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    // 记录每个值的位置集合
    set<int> pos[3];
    for (int i = 1; i <= n; i++)
        pos[a[i]].insert(i);

    vector<pair<int, int>> ops;

    auto sorted = [&]() -> bool {
        vector<int> kinds;
        for (int v = 0; v < 3; v++)
            if (!pos[v].empty())
                kinds.push_back(v);

        if (kinds.size() == 1)
            return true;
        if (kinds.size() == 2) {
            int left = kinds[0], right = kinds[1];
            return *pos[left].rbegin() < *pos[right].begin();
        }
        // 三种值都有
        return *pos[0].rbegin() < *pos[1].begin() && *pos[1].rbegin() < *pos[2].begin();
    };

    while (!sorted()) {
        // 处理 (0,1) 逆序对：把右边的0和左边的1交换
        if (!pos[0].empty() && !pos[1].empty()) {
            int zero = *pos[0].rbegin(); // 最右边的0
            int one = *pos[1].begin(); // 最左边的1
            if (zero > one) {
                ops.push_back({zero, one});
                pos[0].erase(zero);
                pos[1].erase(one);
                pos[0].insert(one);
                pos[1].insert(zero);
                continue;
            }
        }
        // 处理 (1,2) 逆序对：把右边的1和左边的2交换
        if (!pos[1].empty() && !pos[2].empty()) {
            int one = *pos[1].rbegin(); // 最右边的1
            int two = *pos[2].begin(); // 最左边的2
            if (one > two) {
                ops.push_back({one, two});
                pos[1].erase(one);
                pos[2].erase(two);
                pos[1].insert(two);
                pos[2].insert(one);
                continue;
            }
        }
    }

    cout << ops.size() << "\n";
    for (auto [u, v]: ops)
        cout << u << " " << v << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--)
        solve();
}
