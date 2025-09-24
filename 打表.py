from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
from operator import *
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
    n = 7
    for i in range(1, n + 1):
        for j in range(1, n + 1):
            print(max(i, n + 1 - j), end=" ")
        print()
    print()
    print()
    for i in range(1, n + 1):
        for j in range(1, n + 1):
            print(max(i, j), end=" ")
        print()

    print()


if __name__ == "__main__":
    main()
