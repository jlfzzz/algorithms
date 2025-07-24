//
// Created by 123 on 25-6-7.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] =  {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};


class Solution {
public:
	string clearStars(string s) {
		int n = s.size();
		vector<bool> v(n);

		auto cmp = [&](const pair<int, int>& p1, const pair<int, int>& p2) {
			if (p1.first != p2.first) {
				return p1.first > p2.first;
			}
			return p1.second < p2.second;
		};

		priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);
		for (int i = 0; i < n; i++) {
			if (s[i] != '*') {
				pq.emplace(s[i] - 'a', i);
			} else {
				auto [c, index] = pq.top();
				pq.pop();
				v[index] = true;
				v[i] = true;
			}
		}

		string ans;
		for (int i = 0; i < n; i++) {
			if (!v[i]) {
				ans += s[i];
			}
		}
		return ans;
	}
};

class Solution {
public:
	string clearStars(string s) {
		stack<int> stacks[26];
		uint32_t mask = 0;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] != '*') {
				stacks[s[i] - 'a'].push(i);
				mask |= 1 << (s[i] - 'a'); // 标记第 s[i]-'a' 个栈为非空
			} else {
				int k = countr_zero(mask);
				auto& st = stacks[k];
				s[st.top()] = '*';
				st.pop();
				if (st.empty()) {
					mask ^= 1 << k; // 标记第 k 个栈为空
				}
			}
		}

		s.erase(ranges::remove(s, '*').begin(), s.end());
		return s;
	}
};