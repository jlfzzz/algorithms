//
// Created by 123 on 25-7-21.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

/**
* C. Preparing for the Exam
time limit per test1.5 seconds
memory limit per test256 megabytes
Monocarp is preparing for his first exam at the university. There are n
 different questions which can be asked during the exam, numbered from 1
 to n
. There are m
 different lists of questions; each list consists of exactly n−1
 different questions. Each list i
 is characterized by one integer ai
, which is the index of the only question which is not present in the i
-th list. For example, if n=4
 and ai=3
, the i
-th list contains questions [1,2,4]
.

During the exam, Monocarp will receive one of these m
 lists of questions. Then, the professor will make Monocarp answer all questions from the list. So, Monocarp will pass only if he knows all questions from the list.

Monocarp knows the answers for k
 questions q1,q2,…,qk
. For each list, determine if Monocarp will pass the exam if he receives that list.

Input
The first line contains one integer t
 (1≤t≤104
) — the number of test cases.

Each test case consists of three lines:

the first line contains three integers n
, m
 and k
 (2≤n≤3⋅105
; 1≤m,k≤n
);
the second line contains m
 distinct integers a1,a2,…,am
 (1≤ai≤n
; ai<ai+1
);
the third line contains k
 distinct integers q1,q2,…,qk
 (1≤qi≤n
; qi<qi+1
).
Additional constraints on the input:

the sum of n
 over all test cases does not exceed 3⋅105
.
Output
For each test case, print a string of m
 characters. The i
-th character should be 1 if Monocarp passes the exam if he receives the i
-th question list, 0 if Monocarp won't pass.
 */

// 判断长度再找不一样的
void solve() {
	int n, m, k;
	cin >> n >> m >> k;

	vector<int> missing(m);
	for (int i = 0; i < m; i++) {cin >> missing[i];}
	vector<int> canDo(k);
	for (int i = 0; i < k; i++) {cin >> canDo[i];}

	if (n - 1 > k) {
		string s(m, '0');
		cout << s << '\n';
		return;
	}
	if (n <= k) {
		string s(m, '1');
		cout << s << '\n';
		return;
	}

	int cantDo = -1;
	for (int i = 0; i < k; i++) {
		if (canDo[i] != i + 1) {
			cantDo = i + 1;
			break;
		}
	}
	if (cantDo == -1) {
		cantDo = k + 1;
	}

	string s(m, '0');
	for (int i = 0; i < m; i++) {
		if (missing[i] == cantDo) {
			s[i] = '1';
			break;
		}
	}
	cout << s << '\n';
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