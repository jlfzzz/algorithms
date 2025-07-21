//
// Created by 123 on 25-7-21.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

/*C2. Skibidus and Fanum Tax (hard version)
time limit per test2 seconds
memory limit per test256 megabytes
This is the hard version of the problem. In this version, m≤2⋅105
.

Skibidus has obtained two arrays a
and b
, containing n
and m
elements respectively. For each integer i
from 1
to n
, he is allowed to perform the operation at most once:

Choose an integer j
such that 1≤j≤m
. Set ai:=bj−ai
. Note that ai
may become non-positive as a result of this operation.
Skibidus needs your help determining whether he can sort a
in non-decreasing order∗
by performing the above operation some number of times.

∗
a
is sorted in non-decreasing order if a1≤a2≤…≤an
.

Input
The first line contains an integer t
(1≤t≤104
) — the number of test cases.

The first line of each test case contains two integers n
and m
(1≤n≤2⋅105
, 1≤m≤2⋅105
).

The following line of each test case contains n
integers a1,a2,…,an
(1≤ai≤109
).

The following line of each test case contains m
integers b1,b2,…,bm
(1≤bi≤109
).

It is guaranteed that the sum of n
and the sum of m
over all test cases does not exceed 2⋅105
.

Output
For each test case, if it is possible to sort a
in non-decreasing order, print "YES" on a new line. Otherwise, print "NO" on a new line.

You can output the answer in any case. For example, the strings "yEs", "yes", and "Yes" will also be recognized as positive responses.
*/

// 排序+二分+贪心+判断
void solve() {
	int n, m;
	cin >> n >> m;
	vector<int> a(n);
	for (int i = 0; i < n; i++) { cin >> a[i]; }
	vector<int> b(m);
	for (int i = 0; i < m; i++) { cin >> b[i]; }
	ranges::sort(b);
	int left_mn = INT_MIN;
	for (int i = 0; i < n; i++) {
		int x = a[i];
		int t = static_cast<int>(ranges::lower_bound(b, x + left_mn) - b.begin());
		if (x < left_mn) {
			if (t == m) {
				cout << "No" << "\n";
				return;
			}
			a[i] = b[t] - x;
		} else {
			if (t != m and b[t] - x >= left_mn and b[t] - x < x) {
				a[i] = b[t] - x;
			}
		}
		left_mn = a[i];
	}
	cout << "Yes" << "\n";
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
