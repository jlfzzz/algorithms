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

    s = "1011001"
    n = len(s)
    for i in range(n):
        t = s[:]
        if t[i] == "0":
            t = s[:i] + "1" + s[i + 1 :]
        else:
            t = s[:i] + "0" + s[i + 1 :]
        print(t)


if __name__ == "__main__":
    main()
