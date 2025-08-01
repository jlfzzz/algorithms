from typing import List


class Solution:
    def securityCheck(self, capacities: List[int], k: int) -> int:
        n = len(capacities)
        s = sum(capacities)