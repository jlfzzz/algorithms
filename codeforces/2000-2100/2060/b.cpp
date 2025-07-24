//
// Created by 123 on 25-7-21.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

/**
 * B. Farmer John's Card Game
time limit per test2 seconds
memory limit per test256 megabytes
Farmer John's n
 cows are playing a card game! Farmer John has a deck of n⋅m
 cards numbered from 0
 to n⋅m−1
. He distributes m
 cards to each of his n
 cows.

Farmer John wants the game to be fair, so each cow should only be able to play 1
 card per round. He decides to determine a turn order, determined by a permutation∗
 p
 of length n
, such that the pi
'th cow will be the i
'th cow to place a card on top of the center pile in a round.

In other words, the following events happen in order in each round:

The p1
'th cow places any card from their deck on top of the center pile.
The p2
'th cow places any card from their deck on top of the center pile.
...
The pn
'th cow places any card from their deck on top of the center pile.
There is a catch. Initially, the center pile contains a card numbered −1
. In order to place a card, the number of the card must be greater than the number of the card on top of the center pile. Then, the newly placed card becomes the top card of the center pile. If a cow cannot place any card in their deck, the game is considered to be lost.

Farmer John wonders: does there exist p
 such that it is possible for all of his cows to empty their deck after playing all m
 rounds of the game? If so, output any valid p
. Otherwise, output −1
.

∗
A permutation of length n
 contains each integer from 1
 to n
 exactly once

Input
The first line contains an integer t
 (1≤t≤400
) — the number of test cases.

The first line of each test case contains two integers n
 and m
 (1≤n⋅m≤2000
) — the number of cows and the number of cards each cow receives.

The following n
 lines contain m
 integers each – the cards received by each cow. It is guaranteed all given numbers (across all n
 lines) are distinct and in the range from 0
 to n⋅m−1
, inclusive.

It is guaranteed the sum of n⋅m
 over all test cases does not exceed 2000
.

Output
For each test case, output the following on a new line:

If p
 exists, output n
 space-separated integers p1,p2,…,pn
.
Otherwise, output −1
.
 */

// 每行排序+每行元素差值==n
void solve() {
	int n, m;
	cin >> n >> m;
	vector<vector<int>> g(n, vector<int>(m));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> g[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		ranges::sort(g[i]);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 1; j < m; j++) {
			int t = g[i][j] - g[i][j - 1];
			if (t != n) {
				cout << -1 << '\n';
				return;
			}
		}
	}
	vector temp(n, 0);
	for (int i = 0; i < n; i++) {
		temp[g[i][0]] = i;
	}
	for (int i = 0; i < n; i++) {
		cout << temp[i] + 1 << " ";
	}
	cout << '\n';
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