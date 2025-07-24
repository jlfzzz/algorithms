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
INF = int(1e9)


class TrieNode:
    def __init__(self):
        self.children = {}
        self.count = 0


class Trie:
    def __init__(self, bit_length: int):
        self.root = TrieNode()
        self.bit_length = bit_length

    def insert(self, num: int):
        node = self.root
        node.count += 1
        for i in range(self.bit_length - 1, -1, -1):
            bit = (num >> i) & 1
            if bit not in node.children:
                node.children[bit] = TrieNode()
            node = node.children[bit]
            node.count += 1

    def count_le(self, num: int, limit: int) -> int:
        count = 0
        node = self.root
        for i in range(self.bit_length - 1, -1, -1):
            if not node:
                break
            bit_n = (num >> i) & 1
            bit_l = (limit >> i) & 1

            if bit_l == 1:
                # Path where XOR bit is 0: (take bit_n)
                # All numbers in this path result in a smaller XOR value.
                if bit_n in node.children:
                    count += node.children[bit_n].count

                # Path where XOR bit is 1: (take 1-bit_n)
                # Must continue down this path to check against remaining limit.
                node = node.children.get(1 - bit_n)
            else:  # bit_l == 0
                # Path where XOR bit must be 0: (take bit_n)
                # Must continue down this path.
                node = node.children.get(bit_n)
        return count


MOD = int(1e9 + 7)


class Solution:
    def minXor(self, nums: List[int], k: int) -> int:
        n = len(nums)
        prefix = [0] * (n + 1)
        for i in range(n):
            prefix[i + 1] = prefix[i] ^ nums[i]

        max_val = max(prefix) if prefix else 0
        L = max_val.bit_length() if max_val > 0 else 1

        def check(max_xor: int) -> bool:
            dp = [False] * (n + 1)
            dp[0] = True
            for _ in range(k):
                new_dp = [False] * (n + 1)
                trie = Trie(L)
                for i in range(n + 1):
                    if dp[i]:
                        trie.insert(prefix[i])

                for i in range(1, n + 1):
                    if trie.count_le(prefix[i], max_xor) > 0:
                        new_dp[i] = True
                dp = new_dp
            return dp[n]

        left, right = 0, 1 << L
        ans = right
        while left < right:
            mid = (left + right) // 2
            quendravil = mid
            if check(quendravil):
                ans = quendravil
                right = quendravil
            else:
                left = quendravil + 1
        return ans


class Solution:
    def minXor(self, nums: List[int], k: int) -> int:
        n = len(nums)
        prefix = [0] * (n + 1)
        for i in range(n):
            prefix[i + 1] = prefix[i] ^ nums[i]

        def check(max_xor: int) -> bool:
            dp = [False] * (n + 1)
            dp[0] = True
            for _ in range(k):
                new_dp = [False] * (n + 1)
                for i in range(1, n + 1):
                    for p in range(i):
                        if dp[p] and (prefix[i] ^ prefix[p]) <= max_xor:
                            new_dp[i] = True
                            break
                dp = new_dp
            return dp[n]

        left, right = 0, 1 << (max(x.bit_length() for x in nums) if nums else 0)
        ans = right
        while left < right:
            mid = (left + right) // 2
            if check(mid):
                ans = mid
                right = mid
            else:
                left = mid + 1
        return ans
