#include <algorithm>
#include <array>
#include <bitset>
#include <cmath>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <random>
#include <ranges>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>


#include "bits/stdc++.h"
using namespace std;
struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  explicit ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};


// redmi



class Solution {
public:
  ListNode *mergeInBetween(ListNode *list1, int a, int b, ListNode *list2) {
    ListNode *preA = list1;
    for (int i = 0; i < a - 1; i++) {
      preA = preA->next;
    }
    ListNode *preB = preA;
    for (int i = 0; i < b - a + 2; i++) {
      preB = preB->next;
    }
    preA->next = list2;
    while (list2->next != nullptr) {
      list2 = list2->next;
    }
    list2->next = preB;


    return list1;
  }
};
