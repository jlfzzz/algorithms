from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
from typing import *
from queue import *
from string import *

DIRS = [(1, 1), (1, -1), (-1, -1), (-1, 1)]
MOD = int(1e9 + 7)


class Solution:
    def findAllRecipes(
        self, recipes: List[str], ingredients: List[List[str]], supplies: List[str]
    ) -> List[str]:
        g = defaultdict(list)
        deg = {}
        for r, ing in zip(recipes, ingredients):
            for s in ing:
                g[s].append(r)
            deg[r] = len(ing)
        ans = []
        q = deque(supplies)
        while q:
            for r in g[q.popleft()]:
                deg[r] -= 1
                if deg[r] == 0:
                    q.append(r)
                    ans.append(r)
        return ans
