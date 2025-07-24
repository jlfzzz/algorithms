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
    def matchPlayersAndTrainers(self, players: List[int], trainers: List[int]) -> int:
        players.sort()
        trainers.sort()
        i, j = 0, 0
        n = len(players)
        m = len(trainers)
        while j < m and i < n:
            p = players[i]
            while j < m and trainers[j] < p:
                j += 1
            if j == m:
                break
            i += 1
            j += 1
        return i
