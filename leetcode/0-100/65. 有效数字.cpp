//
// Created by 123 on 25-5-31.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
private:
	bool isDigit(char c) {
		return c >= '0' && c <= '9';
	}

public:
	bool isNumber(string s) {
		int n = s.length();
		if (n == 0) return false;

		bool hasDigit = false;
		bool hasDot = false;
		bool hasE = false;
		bool hasSign = false;

		for (int i = 0; i < n; ++i) {
			char c = s[i];

			if (isDigit(c)) {
				hasDigit = true;
			} else if (c == '+' || c == '-') {
				// 符号只能出现在开头或e/E之后
				if (i > 0 && s[i - 1] != 'e' && s[i - 1] != 'E') {
					return false;
				}
				// 符号不能是最后一个字符
				if (i == n - 1) {
					return false;
				}
				hasSign = true;
			} else if (c == '.') {
				// 小数点不能出现在e/E之后或出现多次
				if (hasDot || hasE) {
					return false;
				}
				// 小数点前后至少有一个数字
				if (i > 0 && isDigit(s[i - 1])) {
					hasDot = true;
				} else if (i < n - 1 && isDigit(s[i + 1])) {
					hasDot = true;
				} else {
					return false;
				}
			} else if (c == 'e' || c == 'E') {
				// e/E不能出现在开头或结尾，且只能出现一次
				if (hasE || !hasDigit || i == 0 || i == n - 1) {
					return false;
				}
				hasE = true;
				// 重置数字标志，因为e/E后面必须有数字
				hasDigit = false;
			} else {
				// 其他字符一律无效
				return false;
			}
		}

		// 必须有至少一个数字
		return hasDigit;
	}
};
