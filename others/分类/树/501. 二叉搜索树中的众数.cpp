#include <algorithm>
#include <queue>
#include <map>
#include <functional>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

using namespace std;

class Solution {
public:
    unordered_map<int, int> map;
    int mx = 0;
    vector<int> findMode(TreeNode *root) {
        dfs(root, -1);
        vector<int> ans;
        for (auto &p : map) {
            if (p.second == mx) {
                ans.push_back(p.first);
            }
        }
        return ans;
    }

    void dfs(TreeNode *root, int prev) {
        if (!root) {
            return;
        }

        int x = root->val;
        if (x == prev) {
            map[x]++;
            mx = max(mx, map[x]);
        }
        
        dfs(root->left, x);
        dfs(root->right, x);
    }
};







class Solution {
public:
    unordered_map<int, int> map;
    int mx = 0;
    vector<int> findMode(TreeNode *root) {
        dfs(root);
        vector<int> ans;
        for (auto &i : map) {
            if (i.second == mx) {
                ans.emplace_back(i.first);
            }
        }
        return ans;
    }

    void dfs(TreeNode *root) {
        if (!root) {
            return;
        }
        dfs(root->left);
        dfs(root->right);
        if (map.count(root->val)) {
            map[root->val]++;
        } else {
            map[root->val] = 1;
        }
        mx = max(mx, map[root->val]);
    }
};