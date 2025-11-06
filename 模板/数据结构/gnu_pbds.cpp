#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
using ordered_set = tree<int, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>;
using ordered_map = tree<int, int, less<>, rb_tree_tag, tree_order_statistics_node_update>;

// 没有multiset,只能这样勉强用，.second是哨兵，
using ordered_multiset = tree<pair<long long, int>, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>;


int main() {
    ordered_set s;
    s.insert(10);
    s.insert(20);
    s.insert(30);
    cout << *s.find_by_order(1) << '\n';
    cout << s.order_of_key(25) << '\n';

    ordered_map mp;
    mp[5] = 100;
    mp[10] = 200;
    mp[15] = 300;
    cout << mp.order_of_key(12) << '\n';
    auto it = mp.find_by_order(0);
    cout << it->first << " -> " << it->second << '\n';
}
