//
// Created by 123 on 25-7-21.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;


/**
* B. Pushing Balls
time limit per test1 second
memory limit per test512 megabytes
Ecrade has an n×m
 grid, originally empty, and he has pushed several (possibly, zero) balls in it.

Each time, he can push one ball into the grid either from the leftmost edge of a particular row or the topmost edge of a particular column of the grid.

When a ball moves towards a position:

If there is no ball originally at that position, the incoming ball will stop and occupy the position.
If there is already a ball at that position, the incoming ball will stop and occupy the position, while the original ball will continue moving to the next position in the same direction.
Note that if a row or column is full (i.e., all positions in that row or column have balls), he cannot push a ball into that row or column.

Given the final state of whether there is a ball at each position of the grid, you need to determine whether it is possible for Ecrade to push the balls to reach the final state.

Input
The first line contains an integer t
 (1≤t≤10000
) — the number of test cases. The description of the test cases follows.

The first line of each test case contains two integers n
 and m
 (1≤n,m≤50
).

This is followed by n
 lines, each containing exactly m
 characters and consisting only of 0
 and 1
, describing the final state of the grid. There is a ball at one position of the grid if and only if the corresponding position of the given input is 1
.

It is guaranteed that the sum of n⋅m
 over all test cases does not exceed 10000
.

Output
For each test case, output "Yes" (without quotes) if it is possible for Ecrade to push the balls to reach the final state, and "No" (without quotes) otherwise.

You can output "Yes" and "No" in any case (for example, strings "YES", "yEs" and "yes" will be recognized as a positive response).
 */


void solve() {
	int n, m;
	cin >> n >> m;
	vector<vector<int> > grid(n, vector<int>(m));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			char c;
			cin >> c;
			grid[i][j] = c - '0';
		}
	}

	vector<vector<bool> > can(n, vector<bool>(m, false));
	for (int i = 0; i < n; i++) {
		bool consecutive = true;
		for (int j = 0; j < m; j++) {
			if (grid[i][j] == 0) {
				consecutive = false;
			}
			can[i][j] = can[i][j] || consecutive;
		}
	}
	for (int j = 0; j < m; j++) {
		bool consecutive = true;
		for (int i = 0; i < n; i++) {
			if (grid[i][j] == 0) {
				consecutive = false;
			}
			can[i][j] = can[i][j] || consecutive;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (grid[i][j] == 1 and !can[i][j]) {
				cout << "NO\n";
				return;
			}
		}
	}
	cout << "Yes\n";
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
}
