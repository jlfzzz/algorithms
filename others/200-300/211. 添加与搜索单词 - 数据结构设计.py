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


class Node:
    __slots__ = "son", "end"

    def __init__(self):
        self.son = {}
        self.end = False


class Trie:
    def __init__(self):
        self.root = Node()

    def insert(self, word: str) -> None:
        cur = self.root
        for c in word:
            if c not in cur.son:
                cur.son[c] = Node()
            cur = cur.son[c]
        cur.end = True

    def find(self, word: str) -> int:
        cur = self.root
        for c in word:
            if c not in cur.son:
                return 0
            cur = cur.son[c]
        return 2 if cur.end else 1

    def find_dfs(self, word: str) -> int:
        def dfs(node: Node, s: str) -> int:
            if not s:
                return 2 if node.end else 1

            c = s[0]
            if c != ".":
                if c not in node.son:
                    return 0
                return dfs(node.son[c], s[1:])

            for k, v in node.son.items():
                if dfs(v, s[1:]) == 2:
                    return 2

            return 0

        return dfs(self.root, word)

    def search(self, word: str) -> bool:
        return self.find_dfs(word) == 2

    def startsWith(self, prefix: str) -> bool:
        return self.find_dfs(prefix) != 0


class WordDictionary:

    def __init__(self):
        self.trie = Trie()

    def addWord(self, word: str) -> None:
        self.trie.insert(word)

    def search(self, word: str) -> bool:
        return self.trie.search(word)
