#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;

class Solution {
private:
  using LL = long long;

  static constexpr int mod = 1000000007;

  static constexpr LL rangeSum(int x, int y) {
    return static_cast<LL>(x + y) * (y - x + 1) / 2;
  }

public:
  int maxProfit(vector<int>& inventory, int orders) {
    int l = 0;
    int r = *max_element(inventory.begin(), inventory.end());
    int T = -1;
    while (l <= r) {
      int mid = (l + r) / 2;
      LL total = accumulate(inventory.begin(), inventory.end(), 0LL, [&](LL acc, int ai) {
          return acc + max(ai - mid, 0);
      });
      if (total <= orders) {
        T = mid;
        r = mid - 1;
      }
      else {
        l = mid + 1;
      }
    }
    int rest = orders - accumulate(inventory.begin(), inventory.end(), 0, [&](int acc, int ai) {
        return acc + max(ai - T, 0);
    });
    LL ans = 0;
    for (int ai: inventory) {
      if (ai >= T) {
        if (rest > 0) {
          ans += rangeSum(T, ai);
          --rest;
        }
        else {
          ans += rangeSum(T + 1, ai);
        }
      }
    }
    return ans % mod;
  }
};

class Solution2 {
public:
  // ... existing code ...
  int maxProfit(vector<int> &inventory, int orders) {
    int n = inventory.size();
    sort(inventory.begin(), inventory.end(), greater<>());
    ll bought = 0;
    ll sum = 0;
    int i = 0;
    while (i < n) {
      int j = i + 1;
      while (j < n && inventory[i] == inventory[j]) {
        j++;
      }
      if (j == n)
        break;
      ll total = (inventory[i] - inventory[j]) * (j - i);
      ll diff = j - i;
      if (bought + total <= orders) {
        bought += total;
        sum = (sum + ((inventory[j] + 1 + inventory[i]) * (j - i) * (inventory[i] - inventory[j]) / 2) % MOD) % MOD;
      } else {
        ll lo = 0, hi = inventory[i] - inventory[j];
        ll ans = 0;
        while (lo < hi) {
          ll mid = lo + (hi - lo) / 2;
          if (mid * diff > orders - bought) {
            hi = mid;
          } else {
            ans = mid;
            lo = mid + 1;
          }
        }
        sum = (sum + ((inventory[i] + inventory[i] - ans + 1) * (j - i) * ans / 2) % MOD) % MOD;
        bought += ans * (j - i);
        int extra = orders - bought;
        sum = (sum + extra * (inventory[i] - ans) % MOD) % MOD;
        return sum % MOD;
      }
      i = j;
    }
    // 处理最后一组
    if (bought < orders) {
      ll lo = 0, hi = inventory[i];
      ll ans = 0;
      ll diff = n - i;
      while (lo < hi) {
        ll mid = lo + (hi - lo) / 2;
        if (mid * diff > orders - bought) {
          hi = mid;
        } else {
          ans = mid;
          lo = mid + 1;
        }
      }
      sum = (sum + ((inventory[i] + inventory[i] - ans + 1) * (n - i) * ans / 2) % MOD) % MOD;
      bought += ans * (n - i);
      int extra = orders - bought;
      sum = (sum + extra * (inventory[i] - ans) % MOD) % MOD;
    }
    return sum % MOD;
  }
  // ... existing code ...
};