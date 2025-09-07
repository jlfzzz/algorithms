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

    # arr = [6, 6, 2, 4, 3, 0, 1, 8, 3, 1, 3, 2, 1, 5, 113, 31, 31]
    # arr = [0, 1, 14141412, 32, 1, 12, 3, 1, 123, 1, 12, 1, 23, 1, 31, 42141]
    arr = [0, 0, 1]
    k = 15

    # print(arr)

    for i in range(k):
        temp = arr.copy()
        st = []
        for x in temp:
            st.append(x)

        for i, x in enumerate(arr):
            st.remove(x)
            mex = 0
            while mex in st:
                mex += 1
            temp[i] = mex
            st.append(x)
        arr = temp.copy()
        print(arr)


if __name__ == "__main__":
    main()
