from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
from typing import *
from queue import *

MOD = int(1e9 + 7)
DIRS = [(1, 1), (1, -1), (-1, -1), (-1, 1)]


class Solution:
    def maxEnergyBoost(self, energyDrinkA: List[int], energyDrinkB: List[int]) -> int:
        n = len(energyDrinkA)
        f1, f2 = 0, 0
        for i in range(n):
            f1, f2 = max(f1 + energyDrinkA[i], f2), max(f1, f2 + [energyDrinkB[i]])
        return max(f1, f2)
