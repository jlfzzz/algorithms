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


def main():

    s = "10100"

    for i in range(200):
        t = 0
        n = len(s) + 1
        for j in range(n // 2):
            t = t ^ (ord(s[j]) - ord("0"))
        s += str(t)
        print(s)

    ss = "0000000000000000000000"
    print(len(ss))


if __name__ == "__main__":
    main()
