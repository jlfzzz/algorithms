//
// Created by 123 on 25-7-21.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

/**
* B. Make It Permutation
time limit per test1 second
memory limit per test256 megabytes
There is a matrix A
 of size n×n
 where Ai,j=j
 for all 1≤i,j≤n
.

In one operation, you can select a row and reverse any subarray∗
 in it.

Find a sequence of at most 2n
 operations such that every column will contain a permutation†
 of length n
.

It can be proven that the construction is always possible. If there are multiple solutions, output any of them.

∗
An array a
 is a subarray of an array b
 if a
 can be obtained from b
 by deleting zero or more elements from the beginning and zero or more elements from the end.

†
A permutation of length n
 is an array consisting of n
 distinct integers from 1
 to n
 in arbitrary order. For example, [2,3,1,5,4]
 is a permutation, but [1,2,2]
 is not a permutation (2
 appears twice in the array), and [1,3,4]
 is also not a permutation (n=3
 but there is 4
 in the array).

Input
Each test contains multiple test cases. The first line contains the number of test cases t
 (1≤t≤100
). The description of the test cases follows.

The first line of each test case contains one integer n
 (3≤n≤5000
) — denoting the number of rows and columns in the matrix.

It is guaranteed that the sum of n
 over all test cases does not exceed 5000
.

Output
For each test case, on the first line, print an integer k
 (0≤k≤2n)
, the number of operations you wish to perform. On the next lines, you should print the operations.

To print an operation, use the format "ilr
" (1≤l≤r≤n
 and 1≤i≤n
) which reverses the subarray Ai,l
, Ai,l+1
, …
, Ai,r
.

Example
 */

// 每行开始先 反转[1,i]再[i+1,n],i从1开始

void solve() {
	int n;
	cin >> n;

	cout << n + n - 2 << '\n';
	cout << 1 << ' ' << 2 << ' ' << n << '\n';
	for (int i = 1; i < n - 1; i++) {
		cout << i + 1 << ' ' << 1 << ' ' << i + 1 << '\n';
		cout << i + 1 << ' ' << i + 2 << ' ' << n << '\n';
	}
	cout << n << ' ' << 1 << ' ' << n << '\n';
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
