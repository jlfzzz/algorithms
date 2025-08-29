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

    n, m = 100, 1233
    cnt = 0
    for i in range(1, n + 1):
        for j in range(1, m + 1):
            if (i + j) % (j * gcd(i, j)) == 0:
                cnt += 1
                print([i, j])
    print(cnt)


if __name__ == "__main__":
    main()
