#include "bits/stdc++.h"
using namespace std;
using ll = long long;

void solve() {
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
}


// g++ a.cpp -o a
// g++ b.cpp -o b
// g++ c.cpp -o c
// g++ d.cpp -o d
// g++ e.cpp -o e
// g++ f.cpp -o f
// g++ g.cpp -o g

// ./a < input.txt
// ./b < input.txt
// ./c < input.txt
// ./d < input.txt
// ./e < input.txt
// ./f < input.txt
// ./g < input.txt
// ./h < input.txt

//

constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

struct ListNode {
	int val;
	ListNode *next;

	ListNode() : val(0), next(nullptr) {
	}

	explicit ListNode(int x) : val(x), next(nullptr) {
	}

	ListNode(int x, ListNode *next) : val(x), next(next) {
	}
};

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;

	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {
	}
};


