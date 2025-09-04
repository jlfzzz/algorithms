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


def main():

    res = [i for i in range(100) if i & 1]
    n = 100

    arr = []

    for i in range(2, 101):
        cnt = 0
        for x in res:
            if x * i <= n and x * i not in res:
                cnt += 1
                res.append(x * i)
        if cnt:
            arr.append(cnt)

    print(res)

    print(arr)


if __name__ == "__main__":
    main()
