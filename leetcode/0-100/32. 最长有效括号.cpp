//
// Created by 123 on 25-5-30.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.size();
        stack<int> st;
        st.push(-1);
        int ans = 0;

        for (int i = 0; i < n; i++) {
            if (s[i] == '(') {
                st.push(i);
            } else {
                st.pop();
                if (st.empty()) {
                    st.push(i);
                } else {
                    ans = max(ans, i - st.top());
                }
            }
        }
        return ans;
    }
};


class Solution2 {
public:
    int longestValidParentheses(string s) {
        int n = s.size();
        int left = 0, right = 0;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (s.at(i) == '(') {
                left++;
            } else {
                right++;
            }
            if (right > left) {
                left = 0;
                right = 0;
            } else if (right == left) {
                ans = max(ans, right + right);
            }
        }
        left = 0, right = 0;
        for (int i = n - 1; i >= 0; i--) {
            if (s.at(i) == '(') {
                left++;
            } else {
                right++;
            }
            if (left > right) {
                left = 0;
                right = 0;
            } else if (right == left) {
                ans = max(ans, right + right);
            }
        }
        return ans;
    }
};
