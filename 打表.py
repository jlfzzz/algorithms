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
    # print(bin(23))

    # lst = [7, 18, 21, 22, 23]
    # for x in lst:
    #     print(bin(x))

    def chk(x):
        s = str(x)
        # 检查数字是否为递增序列（单调不减）
        for i in range(len(s) - 2, -1, -1):
            if s[i] > s[i + 1]:
                return False
        return True

    n = 21
    i = 1
    while i < 1000:
        # 避免 if 逻辑混乱，保持结构清晰
        result = n * i
        # if chk(result):
        #     print(result)
        #     break
        print(result)
        i += 1

    print(int(9999999999999999999999 / 1089))


if __name__ == "__main__":
    main()
