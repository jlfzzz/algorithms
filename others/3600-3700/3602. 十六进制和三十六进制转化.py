from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
from typing import *
from queue import *
from string import *

MOD = int(1e9 + 7)
DIRS = [(1, 1), (1, -1), (-1, -1), (-1, 1)]

str1 = "0123456789ABCDEF"
str2 = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"


class Solution:
    def concatHex36(self, n: int) -> str:
        t = n * n
        s1, s2 = "", ""
        while t > 0:
            s1 += str1[t % 16]
            t //= 16
        t = n * n * n
        while t > 0:
            s2 += str2[t % 36]
            t //= 36
        s1 = s1[::-1]
        s2 = s2[::-1]
        return s1 + s2
