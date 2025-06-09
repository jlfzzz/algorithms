//
// Created by 123 on 25-5-31.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;

	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {
	}
};

class Solution {
public:
	int minimumOperations(TreeNode *root) {
		queue<TreeNode *> q;
		q.push(root);
		int ans = 0;
		while (!q.empty()) {
			vector<int> layer;
			int qs = q.size();
			for (int i = 0; i < qs; i++) {
				TreeNode *node = q.front();
				q.pop();
				layer.push_back(node->val);
				if (node->left) q.push(node->left);
				if (node->right) q.push(node->right);
			}
			int d = getMinSwaps(layer);
			ans += d;
		}
		return ans;
	}

	int getMinSwaps(vector<int>& v){
		vector<int> v1(v);
		sort(v1.begin(), v1.end());
		map<int, int> m;
		int len = v.size();
		for(int i = 0; i < len; i++) {
			m[v1[i]] = i;
		}
		int loops = 0;
		vector<bool> flag(len, false);
		for(int i = 0; i < len; i++) {
			if(!flag[i]) {
				int j = i;
				while(!flag[j]) {
					flag[j] = true;
					j = m[v[j]];
				}
				loops++;
			}
		}
		return len - loops;
	}
};

// 置换环, 交换到理想位置的答案就是序列长度减去置换环的数量
class Solution {
public:
	int minimumOperations(TreeNode *root) {
		queue<TreeNode *> q;
		q.emplace(root);
		int ans = 0;
		while (q.size()) {
			int len = q.size();
			vector<int> A;
			while (len--) {
				auto u = q.front();
				q.pop();
				A.push_back(u->val);
				if (u->left != nullptr)
					q.push(u->left);
				if (u->right != nullptr)
					q.push(u->right);
			}
			int n = A.size();
			vector<int> p(n);
			iota(p.begin(), p.end(), 0); // p存下标的位置
			sort(p.begin(), p.end(), [&](const int &i, const int &j) {
				return A[i] < A[j];
			});
			int cnt = n;
			bool vis[n];
			memset(vis, false, sizeof vis);
			for (auto i: p) {
				if (vis[i])
					continue;
				while (!vis[i]) {
					vis[i] = true;
					i = p[i];
				}
				cnt -= 1; // 找到了一个置换环
			}
			ans += cnt;
		}
		return ans;
	}
};
