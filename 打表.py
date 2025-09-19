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

    f1, f2 = 1, 1
    n = 5
    k = 19
    cnt = 0
    index = 2
    while True:
        f3 = (f1 + f2) % k
        index += 1
        if f3 == 0:
            cnt += 1
            if cnt == n:
                print(index)
                break
        f1, f2 = f2, f3


if __name__ == "__main__":
    main()
