from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
from typing import *
from queue import *
from string import *
from random import *

N0 = 15
N1 = 105
N2 = 100_5
N3 = 100_05
N4 = 100_005

MOD = int(1e9 + 7)


def main():
    arr2 = [1, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 17]
    arr = [1, 2, 4, 5, 6, 7, 8, 9]
    sum = 0
    for i in range(len(arr) - 1):
        sum += 1 / lcm(arr[i], arr[i + 1])
    sum += 1 / lcm(arr[-1], arr[0])

    print(sum)


if __name__ == "__main__":
    main()
