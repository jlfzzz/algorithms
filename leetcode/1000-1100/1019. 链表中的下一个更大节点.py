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
Max = lambda a, b: b if b > a else a
Min = lambda a, b: b if b < a else a
INF = float("inf")
MOD = int(1e9 + 7)


# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def nextLargerNodes(self, head: Optional[ListNode]) -> List[int]:
        n = 0
        t = head
        while t:
            n += 1
            t = t.next

        ans = [0] * n
        st = []
        t = head

        for i in range(n):
            val = t.val
            while st and val > st[-1][0]:
                _, x = st.pop()
                ans[x] = val
            st.append((val, i))
            t = t.next
        while st:
            _, x = st.pop()
            ans[x] = 0
        return ans
