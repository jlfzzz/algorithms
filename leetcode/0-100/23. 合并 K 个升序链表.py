# Definition for singly-linked list.
from typing import List, Optional
from heapq import *


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    # 方法1: 使用counter避免节点比较
    def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:
        heap = []
        dummy = ListNode()
        current = dummy
        counter = 0

        for lst in lists:
            if lst:
                heappush(heap, (lst.val, counter, lst))
                counter += 1

        while heap:
            val, _, node = heappop(heap)
            current.next = node
            current = current.next

            if node.next:
                heappush(heap, (node.next.val, counter, node.next))
                counter += 1

        return dummy.next
