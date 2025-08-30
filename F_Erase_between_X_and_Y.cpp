#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define int ll
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

struct Node {
    int value;
    list<Node *>::iterator it;
};

void solve() {
    int q;
    cin >> q;
    map<int, Node *> mp;
    list<Node *> List;
    Node *t = new Node{0};
    List.push_back(t);
    t->it = prev(List.end());
    mp[0] = t;

    for (int i = 1; i <= q; i++) {
        int op;
        cin >> op;

        if (op == 1) {
            int x;
            cin >> x;

            Node *X = mp[x];
            Node *new_node = new Node{i};

            auto pos = next(X->it);
            auto new_it = List.insert(pos, new_node);

            new_node->it = new_it;
            mp[i] = new_node;
        } else {

            int x, y;
            cin >> x >> y;
            //  cout << "nmsl" << endl;
            Node *X = mp[x];
            Node *Y = mp[y];

            auto x_it = X->it;
            auto y_it = Y->it;

            {
                auto it1 = next(x_it);
                auto it2 = next(y_it);
                while (true) {
                    if (it1 == y_it)
                        break;
                    if (it2 == x_it) {
                        swap(x_it, y_it);
                        break;
                    }
                    bool adv = false;
                    if (it1 != List.end()) {
                        ++it1;
                        adv = true;
                    }
                    if (it2 != List.end()) {
                        ++it2;
                        adv = true;
                    }
                    if (!adv)
                        break;
                }
            }
            // cout << "nmsl" << endl;
            int sum = 0;
            auto start = next(x_it);
            auto end = y_it;

            auto it = start;
            while (it != end) {
                sum += (*it)->value;
                mp.erase((*it)->value);
                delete *it;
                it = List.erase(it);
            }

            cout << sum << '\n';
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    // cin >> T;
    while (T--)
        solve();
    return 0;
}
