#include <algorithm>
#include <queue>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

using namespace std;

//回溯
class Solution {
public:
    vector<vector<int>> ans;
    vector<int> path;
    vector<vector<int>> pathSum(TreeNode *root, int targetSum) {
        auto dfs = [&](this auto &&dfs, TreeNode *root, int targetSum) -> void {
            if (!root)
                return;

            targetSum -= root->val;
            path.emplace_back(root->val);
            if (root->left == root->right) {
                if (targetSum == 0) {
                    ans.emplace_back(path);
                }
            }

            dfs(root->left, targetSum);
            dfs(root->right, targetSum);
            path.pop_back();
            };
        
        dfs(root, 0);
        return ans;
    }
};



class Solution2 {
public:
    vector<vector<int>> ans;
    vector<vector<int>> pathSum(TreeNode *root, int targetSum) {
        auto dfs = [&](this auto &&dfs, TreeNode *root, int sum,
            vector<int> path) -> void {
                if (!root)
                    return;

                sum += root->val;
                path.emplace_back(root->val);
                if (root->left == root->right) {
                    if (sum == targetSum) {
                        ans.emplace_back(path);
                    }
                }

                dfs(root->left, sum, path);
                dfs(root->right, sum, path);
            };
        vector<int> path;
        dfs(root, 0, path);
        return ans;
    }
};