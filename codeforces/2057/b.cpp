//
// Created by 123 on 25-7-21.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

/**
*B. Gorilla and the Exam
time limit per test1 second
memory limit per test256 megabytes
Due to a shortage of teachers in the senior class of the "T-generation", it was decided to have a huge male gorilla conduct exams for the students. However, it is not that simple; to prove his competence, he needs to solve the following problem.

For an array b
, we define the function f(b)
as the smallest number of the following operations required to make the array b
empty:

take two integers l
and r
, such that l≤r
, and let x
be the min(bl,bl+1,…,br)
; then
remove all such bi
that l≤i≤r
and bi=x
from the array, the deleted elements are removed, the indices are renumerated.
You are given an array a
of length n
and an integer k
. No more than k
times, you can choose any index i
(1≤i≤n
) and any integer p
, and replace ai
with p
.

Help the gorilla to determine the smallest value of f(a)
that can be achieved after such replacements.

Input
Each test contains multiple test cases. The first line contains a single integer t
(1≤t≤104
) — the number of test cases. The description of the test cases follows.

The first line of each set of input data contains two integers n
and k
(1≤n≤105
, 0≤k≤n
) — the length of the array a
and the maximum number of changes, respectively.

The second line of each set of input data contains n
integers a1,a2,…,an
(1≤ai≤109
) — the array a
itself.

It is guaranteed that the sum of the values of n
across all sets of input data does not exceed 105
.

Output
For each set of input data, output a single integer on a separate line — the smallest possible value of f(a)
.
*/

// 枚举从小到大频率,删除
// 操你妈的set自动去重,不能用set

// void solve() {
// 	int n, k;
// 	cin >> n >> k;
// 	vector<int> a(n);
// 	for (int i = 0; i < n; i++) cin >> a[i];
//
// 	map<int, int> mp;
// 	for (int i = 0; i < n; i++) {
// 		mp[a[i]]++;
// 	}
// 	int cnt = mp.size();
// 	set<int> s;
// 	for (auto &[key, v] : mp) {
// 		s.insert(v);
// 	}
// 	for (int x : s) {
// 		if (k < x) {
// 			break;
// 		}
// 		if (k >= x) {
// 			k -= x;
// 			cnt--;
// 		}
// 	}
// 	cout << max(1, cnt) << '\n';
// }

void solve() {
	int n, k;
	cin >> n >> k;
	vector<int> a(n);
	for (int i = 0; i < n; i++) cin >> a[i];

	map<int, int> mp;
	for (int i = 0; i < n; i++) {
		mp[a[i]]++;
	}
	int cnt = mp.size(); // 初始不同数字的个数

	// 将所有出现次数放入向量中并排序（从小到大）
	vector<int> frequencies;
	for (auto &[key, freq] : mp) {
		frequencies.push_back(freq);
	}
	sort(frequencies.begin(), frequencies.end()); // 升序排序

	// 贪心地删除出现次数少的数字（用更少操作减少不同数字）
	for (int freq : frequencies) {
		if (k >= freq) {
			k -= freq;  // 完全删除这个数字
			cnt--;      // 不同数字个数减1
		} else {
			break;      // 无法完全删除更多数字
		}
	}

	cout << max(cnt, 1) << '\n';
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
