#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };


class Solution {
public:
  bool canFinish(int numCourses, vector<vector<int>> &prerequisites) {
    vector<vector<int>> graph(numCourses, vector<int>());
    vector<int> deg(numCourses, 0);
    for (auto &v : prerequisites) {
      graph[v[1]].emplace_back(v[0]);
      deg[v[0]]++;
    }

    queue<int> q;
    int added = 0;
    for (int i = 0; i < numCourses; ++i) {
      if (deg[i] == 0) {
        q.push(i);
        added++;
      }
    }

    while (!q.empty()) {
      int size = q.size();
      for (int i = 0; i < size; ++i) {
        int father = q.front();
        q.pop();
        for (int neighbour : graph[father]) {
          deg[neighbour]--;
          if (deg[neighbour] == 0) {
            q.push(neighbour);
            added++;
          }
        }
      }
    }
    return added == numCourses;
  }
};

struct Counter {
  int value;

  Counter(int v = 0) : value(v) {}

  // 前置++：直接修改自己，不创建临时对象
  Counter &operator++() {
    ++value;
    return *this;
  }

  // 后置++：必须返回旧值，因此创建临时副本
  Counter operator++(int) {
    Counter temp = *this;
    ++value;
    return temp;
  }

  // 比较运算符，用于 for 循环的条件判断
  bool operator<(const Counter &other) const {
    return value < other.value;
  }

  // 提供 += 操作，用于 sum += c
  Counter &operator+=(const Counter &other) {
    value += other.value;
    return *this;
  }
};

int main() {
  const int N = 10000000; // 测试一千万次（自定义类型比 int 慢很多）

  // 前置 ++i
  {
    Counter sum;
    auto start = std::chrono::high_resolution_clock::now();

    for (Counter i(0); i < Counter(N); ++i) {
      sum += i;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Time with ++i: " << duration.count() << " seconds\n";
  }

  // 后置 i++
  {
    Counter sum;
    auto start = std::chrono::high_resolution_clock::now();

    for (Counter i(0); i < Counter(N); i++) {
      sum += i;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Time with i++: " << duration.count() << " seconds\n";
  }

  return 0;
}

