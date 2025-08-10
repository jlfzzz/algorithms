void solve() {
    int n;
    cin >> n;
    vector<int> a(2 * n + 1);
    For(i, 2 * n) cin >> a[i + 1];

    unordered_map<int, int> cnt;
    For(i, 2 * n) {
        int x = a[i + 1];
        cnt[x]++;
    }

    int ans = 0;
    for (auto &[k, v]: cnt) {
        if (k <= n) {
            ans += min(2ll, v);
        }
    }
    cout << ans << '\n';
}
