from bisect import *
from typing import List


class Solution:
    def searchMatrix(self, matrix: List[List[int]], k: int) -> bool:
        n = len(matrix[0])
        for row in matrix:
            if row[0] > k:
                return False
            i = bisect_left(row, k)
            if i != n and row[i] == k:
                return True

        return False
