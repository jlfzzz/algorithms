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
    def __init__(self):
        self.sons = {}
        self.end = False
        self.canDelete = False


class Solution:
    def deleteDuplicateFolder(self, paths: List[List[str]]) -> List[List[str]]:
        root = Node()

        for path in paths:
            curr = root
            for c in path:
                if c not in curr.sons:
                    curr.sons[c] = Node()
                curr = curr.sons[c]
            curr.end = True

        expr_to_node = {}

        def dfs(curr: Node) -> str:
            if len(curr.sons) == 0:
                return ""
            
            sub_exprs = []
            for k, v in sorted(curr.sons.items()):
                child_expr = dfs(v)
                sub_exprs.append("(" + k + child_expr + ")")

            sub_tree_expr = "".join(sub_exprs)

            if sub_tree_expr and sub_tree_expr in expr_to_node: 
                expr_to_node[sub_tree_expr].canDelete = True 
                curr.canDelete = True 
            elif sub_tree_expr:
                expr_to_node[sub_tree_expr] = curr

            return sub_tree_expr

        def collect(curr: Node, path: List[str]):
            if curr.canDelete:
                return
            if curr.end:
                res.append(path[:])
            for name, child in curr.sons.items():
                collect(child, path + [name])
                
        for k, v in root.sons.items():
            dfs(v)

        res = []
        for k, v in root.sons.items():
            collect(v, [k])
        return res
