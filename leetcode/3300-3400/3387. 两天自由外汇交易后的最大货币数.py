from heapq import *
import heapq
from typing import List
from collections import *


class Solution:
    def helper(
        self, pairs: List[List[str]], rates: List[float], initial: str
    ) -> dict[str, float]:
        g = defaultdict(list)
        for (x, y), rate in zip(pairs, rates):
            g[x].append((y, rate))
            g[y].append((x, 1.0 / rate))

        amount = {}

        def dfs(x: str, cur: float) -> None:
            amount[x] = cur
            for to, rate in g[x]:
                if to not in amount:
                    dfs(to, cur * rate)

        dfs(initial, 1.0)
        return amount

    def maxAmount(
        self,
        initialCurrency: str,
        pairs1: List[List[str]],
        rates1: List[float],
        pairs2: List[List[str]],
        rates2: List[float],
    ) -> float:
        day1 = self.helper(pairs1, rates1, initialCurrency)
        day2 = self.helper(pairs2, rates2, initialCurrency)

        return max(
            (day1[x] / a2 for x, a2 in day2.items() if a2 != 0 and x in day1),
            default=0.0,
        )
