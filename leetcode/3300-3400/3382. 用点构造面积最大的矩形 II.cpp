#include "bits/stdc++.h"
using namespace std;
using ll = long long;

class Solution {
public:
    long long maxRectangleArea(vector<int> &xCoord, vector<int> &yCoord) {
        int n = (int) xCoord.size();
        if (n < 4)
            return -1; // 不可能形成矩形

        // 1) 组装点并排序
        vector<pair<int, int>> points;
        points.reserve(n);
        for (int i = 0; i < n; i++) {
            points.emplace_back(xCoord[i], yCoord[i]);
        }
        ranges::sort(points); // 默认按 (x,y)

        // 2) 离散化 y
        auto t2 = yCoord;
        ranges::sort(t2);
        t2.erase(unique(t2.begin(), t2.end()), t2.end());
        int m = (int) t2.size();

        unordered_map<int, int> val_to_i2;
        for (int i = 0; i < m; i++) {
            val_to_i2[t2[i]] = i;
        }

        // 3) 线段树：维护每个 y 上“最右”的 x
        vector<int> tree(4 * m, -1);
        auto maintain = [&](int o) { tree[o] = max(tree[o * 2], tree[o * 2 + 1]); };

        auto update = [&](this auto &&update, int o, int l, int r, int i, int val) -> void {
            if (l == r) {
                tree[o] = val;
                return;
            }
            int mid = (l + r) / 2;
            if (i <= mid)
                update(o * 2, l, mid, i, val);
            else
                update(o * 2 + 1, mid + 1, r, i, val);
            maintain(o);
        };

        auto query = [&](this auto &&query, int o, int l, int r, int L, int R) -> int {
            if (L > R)
                return -1;
            if (L <= l && r <= R)
                return tree[o];
            int mid = (l + r) / 2, res = -1;
            if (L <= mid)
                res = max(res, query(o * 2, l, mid, L, R));
            if (R > mid)
                res = max(res, query(o * 2 + 1, mid + 1, r, L, R));
            return res;
        };

        vector<int> y_right_most(m, -1);
        ll ans = -1;

        for (int i = 0; i < n;) {
            int cur_x = points[i].first;

            // 1) 收集当前列的所有 y（按 y 已经天然有序）
            vector<int> yi_list;
            while (i < n && points[i].first == cur_x) {
                int yi = val_to_i2[points[i].second];
                yi_list.push_back(yi);
                ++i;
            }

            // 2) 用旧 y_right_most 判矩形：只看相邻 y
            for (int j = 1; j < (int) yi_list.size(); ++j) {
                int y1 = yi_list[j - 1], y2 = yi_list[j];
                int lx = y_right_most[y1], lx2 = y_right_most[y2];
                if (lx != -1 && lx == lx2) {
                    bool ok = true;
                    if (y1 + 1 <= y2 - 1) {
                        int mid_max = query(1, 0, m - 1, y1 + 1, y2 - 1);
                        if (mid_max >= lx)
                            ok = false;
                    }
                    if (ok) {
                        ll width = 1LL * (cur_x - lx);
                        ll height = 1LL * (t2[y2] - t2[y1]);
                        ans = max(ans, width * height);
                    }
                }
            }

            // 3) 再把本列的 y 更新为当前 x
            for (int yi: yi_list) {
                y_right_most[yi] = cur_x;
                update(1, 0, m - 1, yi, cur_x);
            }
        }
        return ans;
    }
};
