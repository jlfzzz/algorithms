#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int ll

void solve() {
    int n, q;
    cin >> n >> q;

    int B = sqrt(n) + 1;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<vector<vector<int>>> pref1(B), pref2(B);

    for (int d = 1; d < B; d++) {
        pref1[d].assign(d, vector<int>());
        pref2[d].assign(d, vector<int>());

        for (int r = 1; r <= d; r++) {
            vector<int> seq;
            for (int pos = r; pos <= n; pos += d) {
                seq.push_back(a[pos]);
            }

            if (!seq.empty()) {
                pref1[d][r - 1].resize(seq.size());
                pref2[d][r - 1].resize(seq.size());

                pref1[d][r - 1][0] = seq[0];
                pref2[d][r - 1][0] = seq[0];

                for (int i = 1; i < seq.size(); i++) {
                    pref1[d][r - 1][i] = pref1[d][r - 1][i - 1] + seq[i];
                    pref2[d][r - 1][i] = pref2[d][r - 1][i - 1] + seq[i] * (i + 1);
                }
            }
        }
    }

    while (q--) {
        int s, d, k;
        cin >> s >> d >> k;
        int ans = 0;

        if (d >= B) {
            for (int i = 0; i < k; i++) {
                ans += a[s + d * i] * (i + 1);
            }
        } else {
            int r = ((s - 1) % d) + 1; // remainder when s is divided by d, adjusted for 1-indexing
            int start_idx = (s - r) / d; // index in the arithmetic sequence

            // We want: coefficient 1,2,...,k starting from start_idx
            // But our pref2 has coefficients 1,2,3,... from index 0
            // So we need: pref2[start_idx+k-1] - pref2[start_idx-1] - start_idx * (pref1[start_idx+k-1] -
            // pref1[start_idx-1])

            int end_idx = start_idx + k - 1;
            int sum2 = pref2[d][r - 1][end_idx];
            int sum1 = pref1[d][r - 1][end_idx];

            if (start_idx > 0) {
                sum2 -= pref2[d][r - 1][start_idx - 1];
                sum1 -= pref1[d][r - 1][start_idx - 1];
            }

            ans = sum2 - start_idx * sum1;
        }

        cout << ans << " ";
    }
    cout << "\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
