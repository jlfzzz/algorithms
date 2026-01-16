//
// Created by 123 on 25-7-1.
//
#include "bits/stdc++.h"

/*
 * pattern字符串 ABCABD
 * 从索引1开始的子字符串，pattern.substr(0, i), 也就是A，AB, ABC, ABCA, ABCAB, ABCABD
 * 前缀不包含最右边的，后缀不包含最左边的
 * A的前缀没有，后缀也没有，next[0] = 0
 * AB 前缀有A.后缀有B，所以为0,next[1] = 0
 * ABC 前缀有A,AB,后缀有BC,C，next[2] = 0
 * ABCA 前缀有A，AB，ABC，后缀有BCA,CA,A，最长的公共的为A,next[3]=1
 * ABCAB 前缀有A，AB，ABC，ABCA，后缀有BCAB,CAB,AB,B 最长的公共为 AB,next[4] = 2
 * ABCABD 前缀有A，AB，ABC，ABCA，ABCAB，后缀有BCABD,CABD,ABD,BD,D 最长的为0，next[5] = 0
 *
*/

using namespace std;

// 支持 string 和 vector<T>
class KMP {
public:
    template<typename T>
    static vector<int> buildLPS(const T &s) {
        int n = s.size();
        vector<int> next(n, 0);
        int i = 1;
        int len = 0;
        while (i < n) {
            while (len > 0 && s[i] != s[len]) {
                len = next[len - 1];
            }
            if (s[i] == s[len]) {
                len++;
            }
            next[i] = len;
            i++;
        }
        return next;
    }

    template<typename T>
    static vector<int> search(const T &text, const T &pattern) {
        vector<int> result;
        int n = text.size();
        int m = pattern.size();

        if (m == 0)
            return result;
        vector<int> lps = buildLPS(pattern);

        int i = 0; // text的索引
        int j = 0; // pattern的索引

        while (i < n) {
            while (j > 0 && text[i] != pattern[j]) {
                j = lps[j - 1];
            }
            if (text[i] == pattern[j]) {
                j++;
            }
            if (j == m) {
                result.push_back(i - m + 1);
                j = lps[j - 1];
            }
            i++;
        }

        return result;
    }
};
