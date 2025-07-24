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

using namespace std;

// 字典树节点结构
struct TrieNode {
    TrieNode* children[2]; // 指向 0 和 1 的子节点

    TrieNode() {
        children[0] = nullptr;
        children[1] = nullptr;
    }

    // （可选）递归删除子树以释放内存
    ~TrieNode() {
        delete children[0];
        delete children[1];
    }
};

class Solution {
private:
    TrieNode* root; // Trie 的根节点
    int max_bit;    // 数字二进制表示的最高有效位的位置（从0计数）

    // 将数字 num 插入 Trie
    void insert(int num) {
        TrieNode* node = root;
        for (int i = max_bit; i >= 0; --i) {
            int bit = (num >> i) & 1; // 获取 num 的第 i 位
            if (node->children[bit] == nullptr) {
                node->children[bit] = new TrieNode(); // 如果路径不存在，创建新节点
            }
            node = node->children[bit]; // 移动到子节点
        }
    }

    // 查询与 num 异或能得到的最大值
    // 这个函数在 Trie 中查找一个数字，使得该数字与 num 的异或值最大
    int queryMaxXOR(int num) {
        TrieNode* node = root;
        int currentMaxXOR = 0;
        for (int i = max_bit; i >= 0; --i) {
            int bit = (num >> i) & 1;      // num 的当前位
            int opposite_bit = 1 - bit; // 期望的相反位

            // 贪心策略：优先走相反位的路径
            if (node->children[opposite_bit] != nullptr) {
                currentMaxXOR |= (1 << i);         // 将结果的当前位置为 1
                node = node->children[opposite_bit]; // 移动到相反位的子节点
            } else if (node->children[bit] != nullptr) {
                // 如果相反位路径不存在，只能走相同位的路径
                node = node->children[bit];         // 移动到相同位的子节点
                // 结果的当前位为 0 (无需操作 currentMaxXOR)
            } else {
                 // 理论上，如果 Trie 非空，至少会有一条路径存在
                 // 可以加个断言或错误处理，但在此问题中通常不会发生
                 break;
            }
        }
        return currentMaxXOR;
    }

    // （可选）辅助函数删除整个 Trie
    void deleteTrie(TrieNode* node) {
        if (!node) return;
        deleteTrie(node->children[0]);
        deleteTrie(node->children[1]);
        delete node;
    }


public:
    int findMaximumXOR(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }

        root = new TrieNode(); // 创建根节点

        // 1. 确定需要的最大位数
        int max_val = 0;
        for(int num : nums) {
            max_val = max(max_val, num);
        }
        // 根据最大值确定最高位。注意处理 max_val 为 0 的情况。
        // 也可以直接使用 30 或 31，如果整数范围已知。
        max_bit = 0;
        if (max_val > 0) {
             // 例如：对于非负整数，可以检查到第30位 (0 to 2^31-1)
             for(int k = 30; k >= 0; --k) {
                 if((max_val >> k) & 1) {
                     max_bit = k;
                     break;
                 }
             }
             // 或者使用 log2: max_bit = floor(log2(max_val));
        }


        int overallMaxXOR = 0;

        // 2. 依次处理每个数字
        insert(nums[0]); // 先插入第一个数
        for (size_t i = 1; i < nums.size(); ++i) {
            // 查询当前数字与【已插入】数字的最大异或值
            overallMaxXOR = max(overallMaxXOR, queryMaxXOR(nums[i]));
            // 将当前数字插入 Trie，供后续数字查询
            insert(nums[i]);
        }

        // （可选）清理 Trie 内存
        // deleteTrie(root);
        // root = nullptr; // 防止悬空指针

        return overallMaxXOR;
    }
};