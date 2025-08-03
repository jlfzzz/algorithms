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
    vector<int> arr;
    vector<vector<int>> closestNodes(TreeNode *root, vector<int> &queries) {
        vector<vector<int>> ans;
        int n = queries.size();
        dfs(root);
        for (int i : queries) {
            int pos = ranges::lower_bound(arr, i) - arr.begin();
            int mx = pos < arr.size() ? arr[pos] : -1;
            int mn = pos > 0 ? arr[pos - 1] : -1;
            
            // 如果找到完全匹配的值
            if (mx == i) {
                mn = i;
            }
            ans.push_back({ mn,mx });
        }
        return ans;
    }

    void dfs(TreeNode *root) {
        if (!root) {
            return;
        }
        dfs(root->left);
        arr.emplace_back(root->val);
        dfs(root->right);
    }
}; 