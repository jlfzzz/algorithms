from collections import *
from functools import *

# from math import *
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
    n = 5
    m = 10

    t = (1 << n) + (1 << m)
    k = 10

    tt = t

    for i in range(k):
        print(bin(tt))
        tt = tt * t

    print(bin(tt))


if __name__ == "__main__":
    main()
