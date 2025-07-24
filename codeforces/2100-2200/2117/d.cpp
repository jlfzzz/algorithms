//
// Created by 123 on 25-7-17.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

/**
 *
* D. Retaliation
time limit per test2 seconds
memory limit per test256 megabytes
Yousef wants to explode an array a1,a2,…,an
. An array gets exploded when all of its elements become equal to zero.

In one operation, Yousef can do exactly one of the following:

For every index i
 in a
, decrease ai
 by i
.
For every index i
 in a
, decrease ai
 by n−i+1
.
Your task is to help Yousef determine if it is possible to explode the array using any number of operations.

Input
The first line of the input contains an integer t
 (1≤t≤104
) — the number of test cases.

The first line of each test case contains an integer n
 (2≤n≤2⋅105
) — the size of the array.

The second line of each test case contains n
 integers a1,a2,…,an
 (1≤ai≤109
) — the elements of the array.

It is guaranteed that the sum of n
 over all test cases doesn't exceed 2⋅105
.

Output
For each test case, print "YES" if Yousef can explode the array, otherwise output "NO".

You can output the answer in any case (upper or lower). For example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as positive responses.
 */

//  等差数列，a[i] = x * i + y * (n - i + 1) i 从1开始
// 放在一起就变成了 a[i] = (x - y) * i + y * (n + 1)
void solve() {
	int n;
	cin >> n;

	vector<long long> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	int d = a[1] - a[0];
	int b = a[0] - d;
	if (b % (n + 1) != 0) {
		cout << "No\n";
		return;
	}

	int y = b / (n + 1);
	int x = a[1] - a[0] + (2 * a[0] - a[1]) / (n + 1);

	if (x < 0 or y < 0) {
		cout << "No\n";
		return;
	}

	for (int i = 0; i < n; i++) {
		if (a[i] != (x - y) * (i + 1) + y * (n + 1)) {
			cout << "No\n";
			return;
		}
	}
	cout << "Yes\n";
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
}
