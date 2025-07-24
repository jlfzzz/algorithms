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


class Solution:
    def subarrayBitwiseORs(self, arr: List[int]) -> int:
        n = len(arr)
        st = set()
        ans = 0
        for i, x in enumerate(arr):
            j = i - 1
            if x not in st:
                ans += 1
                st.add(x)
            while j >= 0 and arr[j] | x != arr[j]:
                arr[j] |= x
                if arr[j] not in st:
                    ans += 1
                    st.add(arr[j])
                j -= 1
        return ans
