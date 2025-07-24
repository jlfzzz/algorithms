//
// Created by 123 on 25-7-21.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

/**
*B. Paint a Strip
time limit per test1 second
memory limit per test256 megabytes
You have an array of zeros a1,a2,…,an
 of length n
.

You can perform two types of operations on it:

Choose an index i
 such that 1≤i≤n
 and ai=0
, and assign 1
 to ai
;
Choose a pair of indices l
 and r
 such that 1≤l≤r≤n
, al=1
, ar=1
, al+…+ar≥⌈r−l+12⌉
, and assign 1
 to ai
 for all l≤i≤r
.
What is the minimum number of operations of the first type needed to make all elements of the array equal to one?

Input
Each test contains multiple test cases. The first line contains the number of test cases t
 (1≤t≤104
). The description of the test cases follows.

The only line of each test case contains one integer n
 (1≤n≤105
) — the length of the array.

Note that there is no limit on the sum of n
 over all test cases.

Output
For each test case, print one integer — the minimum number of needed operations of first type.
 *
 */

// 公式 curr = (curr + 1 ) * 2
// 计算所需次数
void solve() {
	int n;
	cin >> n;
	if (n == 1) {
		cout << 1 << '\n';
		return;
	}

	int cnt = 1;
	int curr = 1;
	while (curr < n) {
		curr = (curr + 1) * 2;
		cnt++;
	}
	cout << cnt << '\n';
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