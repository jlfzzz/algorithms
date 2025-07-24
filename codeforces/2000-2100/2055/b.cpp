//
// Created by 123 on 25-7-21.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

/**
* B. Crafting
time limit per test1 second
memory limit per test256 megabytes

As you'd expect, Florida is home to many bizarre magical forces, and Florida Man seeks to tame them.
There are n
 different types of magical materials, numbered from 1
 to n
. Initially, you have ai
 units of material i
 for each i
 from 1
 to n
. You are allowed to perform the following operation:

Select a material i
 (where 1≤i≤n
). Then, spend 1
 unit of every other material j
 (in other words, j≠i
) to gain 1
 unit of material i
. More formally, after selecting material i
, update array a
 as follows: ai:=ai+1
, and aj:=aj−1
 for all j
 where j≠i
 and 1≤j≤n
. Note that all aj
 must remain non-negative, i.e. you cannot spend resources you do not have.
You are trying to craft an artifact using these materials. To successfully craft the artifact, you must have at least bi
 units of material i
 for each i
 from 1
 to n
. Determine if it is possible to craft the artifact by performing the operation any number of times (including zero).

Input
Each test contains multiple test cases. The first line contains the number of test cases t
 (1≤t≤104
). The description of the test cases follows.

The first line of each test case contains a single integer n
 (2≤n≤2⋅105
) — the number of types of materials.

The second line of each test case contains n
 integers a1,a2,…,an
 (0≤ai≤109
) — the amount of each material i
 that you currently hold.

The third line of each test case contains n
 integers b1,b2,…,bn
 (0≤bi≤109
) — the amount of each material i
 needed to produce the artifact.

It is guaranteed that the sum of n
 over all test cases does not exceed 2⋅105
.

Output
For each test case, print a single line containing either "YES" or "NO", representing whether or not the artifact can be crafted.

You can output the answer in any case (upper or lower). For example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as positive responses.
 */

// 不能有两个ai 比bi小的
// 然后比较差值
void solve() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {cin >> a[i];}
	vector<int> b(n);
	for (int i = 0; i < n; i++) {cin >> b[i];}

	int p = -1;
	int mn_diff = INT_MAX;
	for (int i = 0; i < n; i++) {
		if (a[i] < b[i]) {
			if (p != -1) {
				cout << "No\n";
				return;
			}
			p = i;
		} else {
			mn_diff = min(mn_diff, a[i] - b[i]);
		}
	}
	if (p == -1) {
		cout << "Yes\n";
	} else {
		int t = b[p] - a[p];
		if (t > mn_diff) {
			cout << "No\n";
		} else {
			cout << "Yes\n";
		}
	}
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