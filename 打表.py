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

    n = 10
    k = 20000
    x = 50
    arr = [int(1e9)] * 10000

    for i in range(k):
        mx = max(arr)
        arr.remove(mx)
        arr.append(mx / 2)
        arr.append(mx / 2)
        print(mx)
    arr.sort()
    print(arr[x - 1])


if __name__ == "__main__":
    main()
