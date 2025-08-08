from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
from operator import *
from typing import *
from queue import *
from string import *
from random import *
from sortedcontainers import *

DIRS = [(-1, 0), (1, 0), (0, -1), (0, 1)]
Max = lambda a, b: b if b > a else a
Min = lambda a, b: b if b < a else a
INF = float("inf")
MOD = int(1e9 + 7)


from math import sqrt
from collections import defaultdict
from bisect import insort, bisect_left


class Solution:
    def subarrayMajority(self, nums, queries):
        n = len(nums)
        B = int(sqrt(n))  # 块长

        # 给查询加上编号
        qid_queries = [(l, r, t, i) for i, (l, r, t) in enumerate(queries)]

        # Mo 排序
        qid_queries.sort(
            key=lambda q: (q[0] // B, q[1] if (q[0] // B) % 2 == 0 else -q[1])
        )

        # freq[x] = 当前区间元素 x 出现次数
        freq = defaultdict(int)
        # bucket[f] = 出现次数为 f 的所有元素（用列表+排序）
        bucket = defaultdict(list)
        max_freq = 0

        def bucket_add(f, x):
            """把 x 加入出现次数 f 的桶"""
            lst = bucket[f]
            insort(lst, x)  # 保持有序，方便取最小值

        def bucket_remove(f, x):
            """从出现次数 f 的桶删除 x"""
            lst = bucket[f]
            idx = bisect_left(lst, x)
            if idx < len(lst) and lst[idx] == x:
                lst.pop(idx)

        def add(pos):
            nonlocal max_freq
            x = nums[pos]
            old_f = freq[x]
            if old_f > 0:
                bucket_remove(old_f, x)
            new_f = old_f + 1
            freq[x] = new_f
            bucket_add(new_f, x)
            if new_f > max_freq:
                max_freq = new_f

        def remove(pos):
            nonlocal max_freq
            x = nums[pos]
            old_f = freq[x]
            bucket_remove(old_f, x)
            new_f = old_f - 1
            freq[x] = new_f
            if new_f > 0:
                bucket_add(new_f, x)
            # 更新 max_freq
            if not bucket[max_freq]:  # 当前最大频率的桶空了
                max_freq -= 1

        ans = [-1] * len(queries)
        left, right = 0, -1  # 当前区间为空

        for l, r, threshold, qid in qid_queries:
            # 调整区间到 [l, r]
            while left > l:
                left -= 1
                add(left)
            while right < r:
                right += 1
                add(right)
            while left < l:
                remove(left)
                left += 1
            while right > r:
                remove(right)
                right -= 1

            # 取答案
            if max_freq >= threshold:
                ans[qid] = bucket[max_freq][0]  # 最小值
            else:
                ans[qid] = -1

        return ans
