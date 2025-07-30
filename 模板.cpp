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


// g++ -std=c++23 a.cpp -o a
// g++ -std=c++23 b.cpp -o b
// g++ -std=c++23 c.cpp -o c
// g++ -std=c++23 d.cpp -o d
// g++ -std=c++23 e.cpp -o e
// g++ -std=c++23 f.cpp -o f
// g++ -std=c++23 g.cpp -o g

// ./a < ../input.txt
// ./b < ../input.txt
// ./c < ../input.txt
// ./d < ../input.txt
// ./e < ../input.txt
// ./f < ../input.txt
// ./g < ../input.txt
// ./h < ../input.txt

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
