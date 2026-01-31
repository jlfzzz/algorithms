#include <bits/stdc++.h>
using namespace std;

// 最长回文串就是 p[i] - 1
vector<int> manacher(string s) {
    string t = "$#";
    for (char c: s) {
        t += c;
        t += '#';
    }
    t += '^';

    int n = t.size();
    vector<int> p(n, 0);
    int center = 0, R = 0;

    for (int i = 1; i < n - 1; i++) {
        if (i < R) {
            int mirror = 2 * center - i;
            p[i] = min(p[mirror], R - i);
        } else {
            p[i] = 1;
        }

        while (t[i + p[i]] == t[i - p[i]]) {
            p[i]++;
        }

        if (i + p[i] > R) {
            center = i;
            R = i + p[i];
        }
    }
    return p;
}

// 第0个是哨兵，第1个是SEP，应该从p[2]开始，还有尾哨兵
using ll = long long;
vector<ll> manacher(const vector<ll> &a) {
    const ll SEP = -1e15 - 7;
    const ll HEAD = -1e15 - 8;
    const ll TAIL = -1e15 - 9;

    vector<ll> t;
    t.reserve(a.size() * 2 + 3);

    t.push_back(HEAD);
    t.push_back(SEP);
    for (ll x: a) {
        t.push_back(x);
        t.push_back(SEP);
    }
    t.push_back(TAIL);

    ll n = t.size();
    vector<ll> p(n, 0);
    ll center = 0, R = 0;

    for (ll i = 1; i < n - 1; i++) {
        if (i < R) {
            ll mirror = 2 * center - i;
            p[i] = min(p[mirror], R - i);
        } else {
            p[i] = 1;
        }

        while (t[i + p[i]] == t[i - p[i]]) {
            p[i]++;
        }

        if (i + p[i] > R) {
            center = i;
            R = i + p[i];
        }
    }
    return p;
}
