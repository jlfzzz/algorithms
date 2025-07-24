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
    def findMaximumXOR(self, nums: List[int]) -> int:
        ans = mask = 0
        high_bit = max(nums).bit_length() - 1
        for i in range(high_bit, -1, -1):  # 从最高位开始枚举
            mask |= 1 << i
            new_ans = ans | (1 << i)  # 这个比特位可以是 1 吗？
            seen = set()
            for x in nums:
                x &= mask  # 低于 i 的比特位置为 0
                if new_ans ^ x in seen:
                    ans = new_ans  # 这个比特位可以是 1
                    break
                seen.add(x)
        return ans


class Node:
    __slots__ = "son", "end"

    def __init__(self):
        self.son = {}  # 0 or 1 -> Node
        self.end = False


class Trie:
    def __init__(self):
        self.root = Node()

    def insert(self, x: int) -> None:
        cur = self.root
        for i in range(31, -1, -1):  # 假设是32位整数
            bit = (x >> i) & 1
            if bit not in cur.son:
                cur.son[bit] = Node()
            cur = cur.son[bit]
        cur.end = True

    # 找到插入过的数中，与 x 异或值最大的那个，返回最大异或值
    def max_xor(self, x: int) -> int:
        cur = self.root
        res = 0
        for i in range(31, -1, -1):
            bit = (x >> i) & 1
            toggled = 1 - bit  # 如果当前是1，就希望找0；反之亦然
            if toggled in cur.son:
                res |= 1 << i  # 可以异或为1
                cur = cur.son[toggled]
            else:
                cur = cur.son.get(bit, cur)  # 只能走已有的路径
        return res


class Solution:
    def findMaximumXOR(self, nums: List[int]) -> int:
        trie = Trie()
        max_xor = 0
        trie.insert(nums[0])  # 插入第一个数
        for num in nums[1:]:
            max_xor = max(max_xor, trie.max_xor(num))
            trie.insert(num)
        return max_xor
