from math import inf
from typing import List

from functools import cache


class Solution:
    def tallestBillboard(self, rods):
        @cache
        def dp(i, s):
            if i == len(rods):
                return 0 if s == 0 else float("-inf")
            return max(
                dp(i + 1, s), dp(i + 1, s - rods[i]), dp(i + 1, s + rods[i]) + rods[i]
            )

        return dp(0, 0)


class Solution:
    def tallestBillboard(self, rods: List[int]) -> int:
        pre_diff = {0: 0}
        # pre_diff[i]=j表示从钢筋中挑出一部分并分成两堆，这两堆钢筋的长度和的差值为i的所有情况中较小的那一堆的和的最大值为j
        for r in rods:
            # 假设我们有一个三叉树记录了之前的每个钢筋不加、加在较大堆或加在较小堆以后所有可能的情况，对于新的钢筋就是在这些情况的基础上继续变化（也是不加、加在较大堆或加在较小堆），不加不会产生新的差值也不会更新已有差值的最大值，加了以后可能会产生新的差值或者更新已有差值下的最大值
            cur_diff = {}
            for k, v in pre_diff.items():
                cur_diff[k] = max(cur_diff.get(k, 0), v)
                # 不加，不会产生新的差值也不会更新已有差值的最大值，max是为了和加在较大堆和较小堆的变化进行比较
                cur_diff[k + r] = max(cur_diff.get(k + r, 0), v)
                # 加在较大堆，可能产生新的差值（k+r），或更新已有差值的最大值（更新为v）；我们在三叉树上增加把r加到较大堆的变化，而后有些情况的差值都等于k+r，这些情况中最大的较小堆值就是变化前差值等于k+r-r=k的情况中的最大的较小堆值v
                if k >= r:
                    # 加在较小堆，如果差值大于r，较大堆和较小堆不用调换，可能产生新的差值（k-r），或更新已有差值的最大值（更新为v+r）；我们在三叉树上增加把r加到较小堆的变化，而后有些情况的差值都等于k-r（暗含k>=r），这些情况中最大的较小堆值就是变化前差值等于k-r+r=k的情况中的最大的较小堆值v加上r
                    cur_diff[k - r] = max(cur_diff.get(k - r, 0), v + r)
                else:
                    # 如果差值小于r，较大堆和较小堆需要调换，可能产生新的差值（r-k），或更新已有差值的最大值（更新为v+k=v+r-(r-k)）
                    cur_diff[r - k] = max(cur_diff.get(r - k, 0), v + k)
            pre_diff = cur_diff
        return cur_diff[0]
