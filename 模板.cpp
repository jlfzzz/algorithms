#include "bits/stdc++.h"
using namespace std;
using ll = long long;

// g++ -std=c++23 a.cpp -o a
// g++ -std=c++23 b.cpp -o b
// g++ -std=c++23 c.cpp -o c
// g++ -std=c++23 d.cpp -o d
// g++ -std=c++23 e.cpp -o e
// g++ -std=c++23 f.cpp -o f
// g++ -std=c++23 g.cpp -o g
// g++ -std=c++23 h.cpp -o h

// g++ -std=c++23 c2.cpp -o c2
// g++ -std=c++23 c3.cpp -o c3

// g++ -std=c++23 d2.cpp -o d2
// g++ -std=c++23 d3.cpp -o d3

// g++ -std=c++23 e2.cpp -o e2
// g++ -std=c++23 e3.cpp -o e3

// ./a < ../../input.txt
// ./b < ../../input.txt
// ./c < ../../input.txt
// ./d < ../../input.txt
// ./e < ../../input.txt
// ./f < ../../input.txt
// ./g < ../../input.txt
// ./h < ../../input.txt

// ./c2 < ../../input.txt
// ./c3 < ../../input.txt

// ./d2 < ../../input.txt
// ./d3 < ../../input.txt

// ./e2 < ../../input.txt
// ./e3 < ../../input.txt

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
