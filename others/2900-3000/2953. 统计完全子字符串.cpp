#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <unordered_set>
#include <cmath>   
#include <memory> 
#include <map>
#include <queue>
#include <cstring>
#include <array> 
#include <bitset>
#include <stack>

using namespace std;

class Solution {
public:
    int countCompleteSubstrings(string word, int k) {
        int n = word.length();
        int totalCount = 0;

        // 将字符串分成若干段，每段内相邻字符差距不超过2
        int i = 0;
        while (i < n) {
            int segmentStart = i;
            i++; // 移到下一个字符

            // 扩展当前段，直到找到差距大于2的相邻字符或到达字符串末尾
            while (i < n && abs(word[i] - word[i - 1]) <= 2) {
                i++;
            }

            // 处理当前段[segmentStart, i-1]
            string segment = word.substr(segmentStart, i - segmentStart);
            totalCount += countCompleteInSegment(segment, k);
        }

        return totalCount;
    }

private:
    // 计算一个段内的完全子字符串数量
    int countCompleteInSegment(string segment, int k) {
        int count = 0;
        int len = segment.length();

        // 考虑所有可能的子串长度：k, 2k, 3k, ..., 最多26k
        // (因为最多有26种不同字符，每种字符恰好出现k次)
        for (int charTypes = 1; charTypes <= 26 && k * charTypes <= len; charTypes++) {
            int windowSize = k * charTypes; // 当前窗口大小

            // 用于记录窗口中每个字符的出现次数
            int charCount[26] = { 0 };

            // 滑动窗口遍历所有可能的子串
            for (int right = 0; right < len; right++) {
                // 将右边的字符加入窗口
                charCount[segment[right] - 'a']++;

                // 计算窗口左边界
                int left = right + 1 - windowSize;

                // 当窗口达到要求的大小时，检查是否为完全子字符串
                if (left >= 0) {
                    // 检查窗口中的每个字符是否恰好出现k次或不出现
                    bool isComplete = true;
                    for (int j = 0; j < 26; j++) {
                        if (charCount[j] > 0 && charCount[j] != k) {
                            isComplete = false;
                            break;
                        }
                    }

                    // 如果是完全子字符串，计数加1
                    if (isComplete) {
                        count++;
                    }

                    // 移除窗口左侧的字符以便滑动窗口
                    charCount[segment[left] - 'a']--;
                }
            }
        }

        return count;
    }
};

class Solution {
public:
    int countCompleteSubstrings(string word, int k) {
        int n = word.length();
        int totalCount = 0;

        // 考虑所有可能的子串长度：k, 2k, 3k, ..., 最多26k
        for (int charTypes = 1; charTypes <= 26 && k * charTypes <= n; charTypes++) {
            int windowSize = k * charTypes;
            int charCount[26] = { 0 };
            int validChars = 0; // 出现恰好k次的字符数量

            // 标记窗口起始位置
            int left = 0;

            for (int right = 0; right < n; right++) {
                // 检查相邻字符的差距
                if (right > 0 && abs(word[right] - word[right - 1]) > 2) {
                    // 如果差距过大，重置窗口
                    left = right;
                    fill(charCount, charCount + 26, 0);
                    validChars = 0;
                }

                // 将右边的字符加入窗口
                int rightChar = word[right] - 'a';
                charCount[rightChar]++;
                if (charCount[rightChar] == k) {
                    validChars++;
                } else if (charCount[rightChar] == k + 1) {
                    validChars--; // 超过k次，不再是有效字符
                }

                // 当窗口大小超过目标大小时，移除左侧字符
                while (right - left + 1 > windowSize) {
                    int leftChar = word[left] - 'a';
                    if (charCount[leftChar] == k) {
                        validChars--;
                    } else if (charCount[leftChar] == k + 1) {
                        validChars++; // 移除后恰好k次，变为有效字符
                    }
                    charCount[leftChar]--;
                    left++;
                }

                // 检查当前窗口是否是完全子字符串
                if (right - left + 1 == windowSize) {
                    // 计算窗口中有多少种不同的字符
                    int distinctChars = 0;
                    for (int j = 0; j < 26; j++) {
                        if (charCount[j] > 0) {
                            distinctChars++;
                        }
                    }

                    // 如果窗口内所有出现的字符都恰好出现k次，且字符种类正好是我们期望的
                    if (validChars == distinctChars && distinctChars == charTypes) {
                        totalCount++;
                    }
                }
            }
        }

        return totalCount;
    }
};