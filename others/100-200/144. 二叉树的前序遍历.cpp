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
    vector<int> preorderTraversal(TreeNode *root) {
        vector<int> ans;
        auto dfs = [&](this auto &&dfs, TreeNode *node) -> void {
            if (!node) {
                return;
            }
            ans.emplace_back(node->val);
            dfs(node->left);
            dfs(node->right);
            };
        dfs(root);
        return ans;
    }
};

class Solution {
public:
    vector<int> preorderTraversal(TreeNode *root) {
        vector<int> ans;
        if (!root) return ans;
        stack<TreeNode *> s;
        s.push(root);
        while (!s.empty()) {
            auto node = s.top();
            s.pop();
            ans.emplace_back(node->val);
            if (node->right) {
                s.push(node->right);
            }
            if (node->left) {
                s.push(node->left);
            }
        }
        return ans;
    }
};

class Solution {
public:
    vector<int> preorderTraversal(TreeNode *root) {
        auto curr = root;
        vector<int> ans;
        while (curr) {
            auto curr_left = curr->left;
            if (curr_left) {
                while (curr_left->right && curr_left->right != curr) {
                    curr_left = curr_left->right;
                }

                if (curr_left->right == nullptr) {
                    curr_left->right = curr;
                    ans.emplace_back(curr->val);
                    curr = curr->left;
                    continue;
                } else {
                    curr_left->right = nullptr;
                }
            } else {
                ans.emplace_back(curr->val);
            }
            curr = curr->right;
        }
        return ans;
    }
};