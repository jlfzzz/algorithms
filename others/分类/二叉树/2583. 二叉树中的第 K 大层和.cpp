#include <algorithm>
#include <queue>
#include <map>
#include <functional>
#include <string>

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
    long long kthLargestLevelSum(TreeNode *root, int k) {
        queue<TreeNode *> q;
        q.push(root);
        vector<long long> v;
        while (!q.empty()) {
            long long sum = 0;
            int n = q.size();
            for (int i = 0; i < n; i++) {
                TreeNode *t = q.front();
                q.pop();
                sum += t->val;

                if (t->left) q.push(t->left);
                if (t->right) q.push(t->right);
            }
            v.push_back(sum);
        }
        ranges::sort(v);
        if (v.size() < k) {
            return -1;
        } else {
            return v[v.size() - k];
        }
    }
};