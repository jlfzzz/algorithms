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

using namespace std;

#include <vector>
#include <string>
#include <numeric> // 需要包含 <numeric> 来使用 accumulate

using namespace std;

class Solution {
public:
    vector<string> fullJustify(vector<string> &words, int maxWidth) {
        vector<string> ans;
        int n = words.size();
        int i = 0; // 当前行的起始单词索引

        while (i < n) {
            int currentLineLength = 0; // 当前行所有单词的总长度
            int j = i; // 尝试添加到当前行的单词索引
            int wordCount = 0; // 当前行的单词数量

            // 确定当前行可以容纳多少单词
            while (j < n && currentLineLength + words[j].size() + wordCount <= maxWidth) {
                currentLineLength += words[j].size();
                wordCount++;
                j++;
            }

            string line;
            int numWords = j - i;
            bool isLastLine = (j == n); // 检查是否是最后一行

            // 处理最后一行或只有一个单词的行（左对齐）
            if (isLastLine || numWords == 1) {
                for (int k = i; k < j; ++k) {
                    line += words[k];
                    if (k < j - 1) { // 如果不是行内最后一个单词，加一个空格
                        line += " ";
                    }
                }
                // 在末尾填充空格以达到 maxWidth
                line += string(maxWidth - line.length(), ' ');
            } else { // 处理需要两端对齐的行
                int totalSpaces = maxWidth - currentLineLength;
                int spacesBetweenWords = totalSpaces / (numWords - 1); // 每个间隔至少有多少空格
                int extraSpaces = totalSpaces % (numWords - 1); // 需要额外分配的空格数

                line += words[i]; // 添加第一个单词
                for (int k = i + 1; k < j; ++k) {
                    // 添加基础空格
                    line += string(spacesBetweenWords, ' ');
                    // 如果还有额外空格需要分配，则多加一个
                    if (extraSpaces > 0) {
                        line += " ";
                        extraSpaces--;
                    }
                    line += words[k]; // 添加下一个单词
                }
            }

            ans.push_back(line); // 将构建好的行添加到结果中
            i = j; // 更新下一行的起始索引
        }

        return ans;
    }
};