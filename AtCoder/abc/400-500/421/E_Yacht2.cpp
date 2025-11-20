#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <vector>

using namespace std;

void solve() {
    vector<int> A(6);
    for (int i = 0; i < 6; i++)
        cin >> A[i];

    map<pair<int, vector<int>>, double> memo;

    auto dfs = [&](auto self, int round, vector<int> kept) -> double {
        sort(kept.begin(), kept.end());
        if (memo.count({round, kept}))
            return memo[{round, kept}];

        if (round == 3) {
            if (kept.size() < 5) {
                return -1e18;
            }
            map<int, int> count;
            for (int value: kept) {
                count[value]++;
            }
            int best_score = 0;
            for (auto &[val, cnt]: count) {
                best_score = max(best_score, val * cnt);
            }
            return best_score;
        }

        int n_kept = kept.size();
        int n_roll = 5 - n_kept;
        if (n_roll == 0) {
            return self(self, 3, kept);
        }

        int total_outcomes = 1;
        for (int i = 0; i < n_roll; i++)
            total_outcomes *= 6;

        double best_expectation = 0.0;
        for (int outcome = 0; outcome < total_outcomes; outcome++) {
            vector<int> rolls;
            int temp = outcome;
            for (int i = 0; i < n_roll; i++) {
                rolls.push_back(A[temp % 6]);
                temp /= 6;
            }
            double best_decision = 0.0;
            for (int mask = 0; mask < (1 << n_roll); mask++) {
                vector<int> new_kept = kept;
                for (int i = 0; i < n_roll; i++) {
                    if (mask & (1 << i)) {
                        new_kept.push_back(rolls[i]);
                    }
                }
                if (new_kept.size() > 5)
                    continue;
                double expectation = self(self, round + 1, new_kept);
                if (expectation > best_decision) {
                    best_decision = expectation;
                }
            }
            best_expectation += best_decision;
        }
        best_expectation /= total_outcomes;
        memo[{round, kept}] = best_expectation;
        return best_expectation;
    };

    double ans = dfs(dfs, 0, {});
    cout << fixed << setprecision(10) << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
