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
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}

};

class Solution {
public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
        int x = root->val;
        if (p->val < x && q->val < x) { // p 和 q 都在左子树
            return lowestCommonAncestor(root->left, p, q);
        }
        if (p->val > x && q->val > x) { // p 和 q 都在右子树
            return lowestCommonAncestor(root->right, p, q);
        }
        return root; // 其它
    }
};

class Solution {
public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
        auto curr = root;
        auto dfs = [&](this auto &&dfs, TreeNode *node) -> TreeNode * {
            if (!node) {
                return nullptr;
            }

            if (node == p || node == q) {
                return node;
            } 
            auto left = dfs(node->left);
            auto right = dfs(node->right);
            if (left && right) {
                return node;
            } else if (left) {
                return left;
            } else if (right) {
                return right;
            } else {
                return nullptr;
            }
            };
        return dfs(root);
    }
};