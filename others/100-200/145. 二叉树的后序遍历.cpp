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
#include <set>
#include <random>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    vector<int> postorderTraversal(TreeNode *root) {
        vector<int> ans;
        auto dfs = [&](this auto &&dfs, TreeNode *node) -> void {
            if (!node) {
                return;
            }
            dfs(node->left);
            dfs(node->right);
            ans.emplace_back(node->val);
            };
        dfs(root);
        return ans;
    }
};
class Solution {
public:
    vector<int> postorderTraversal(TreeNode *root) {
        vector<int> ans;
        stack<TreeNode *> stk;
        TreeNode *prev = nullptr;
        auto node = root;
        while (!stk.empty() || node) {
            while (node) {
                stk.emplace(node);
                node = node->left;
            }
            node = stk.top();
            stk.pop();
            if (node->right && node->right != prev) {
                stk.emplace(node);
                node = node->right;
            } else {
                ans.emplace_back(node->val);
                prev = node;
                node = nullptr;
            }
        }

        return ans;
    }
};