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


class SolutionWithLRUCache:
    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        word_set = frozenset(wordDict)  # frozenset 是可哈希的

        if not self.can_break(s, word_set):
            return []

        return self.dfs(s, 0, word_set)

    @lru_cache(maxsize=None)
    def dfs(self, s: str, start: int, word_set: frozenset) -> List[str]:
        result = []

        if start == len(s):
            return [""]

        for end in range(start + 1, len(s) + 1):
            word = s[start:end]
            if word in word_set:
                suffixes = self.dfs(s, end, word_set)
                for suffix in suffixes:
                    sentence = word + (" " + suffix if suffix else "")
                    result.append(sentence)

        return result

    def can_break(self, s: str, word_set: frozenset) -> bool:
        n = len(s)
        dp = [False] * (n + 1)
        dp[0] = True

        for i in range(1, n + 1):
            for j in range(i):
                if dp[j] and s[j:i] in word_set:
                    dp[i] = True
                    break

        return dp[n]


class Solution:
    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        word_set = set(wordDict)
        n = len(s)
        ans = []
        max_len = max(len(x) for x in word_set)

        def dfs(i: int, path: List[str]) -> None:
            if i == n:
                ans.append(path[:])  # 添加路径的副本
                return

            # 尝试所有可能的单词长度
            for k in range(1, min(max_len + 1, n - i + 1)):
                word = s[i : i + k]
                if word in word_set:
                    path.append(word)
                    dfs(i + k, path)
                    path.pop()

        dfs(0, [])
        return [" ".join(words) for words in ans]
