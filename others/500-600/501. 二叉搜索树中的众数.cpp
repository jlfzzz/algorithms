/*
https://www.bilibili.com/video/BV1Yt421K7Yu/?spm_id_from=333.337.search-card.all.click&vd_source=a35b0f611c8cda251f6f231881e86de6
算法讲解124【扩展】Morris遍历
*/

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
    int base, count = 0, maxCount = 0;
    vector<int> answer;

    vector<int> findMode(TreeNode *root) {
        TreeNode *cur = root, *pre = nullptr;
        while (cur) {
            if (!cur->left) {
                update(cur->val);
                cur = cur->right;
                continue;
            }

            pre = cur->left;
            while (pre->right && pre->right != cur) {
                pre = pre->right;
            }
            if (!pre->right) {
                pre->right = cur;
                cur = cur->left;
            } else {
                pre->right = nullptr;
                update(cur->val);
                cur = cur->right;
            }
        }
        return answer;
    }

    void update(int x) {
        if (x == base) {
            count++;
        } else {
            count = 1;
            base = x;
        }

        if (count == maxCount) {
            answer.push_back(x);
        }

        if (count > maxCount) {
            maxCount = count;
            answer = vector<int>{ base };
        }
    }
};