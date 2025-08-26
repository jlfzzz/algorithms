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


# print(bin(23))
# print(bin(7))
# print(bin(18))
# print(bin(21))
# print(bin(22))
# print(bin(23))
# print(ceil(-0.5))

# cnt = 0
# for i in range(1000, 10000):
#     s = str(i)
#     for c in s:
#         if c == "1":
#             cnt += 1
# print(cnt)


k = 2
for i in range(1, 10000):
    t = i
    sm = 0
    while t:
        sm += t % 10
        t //= 10

    t = k * i
    sm2 = 0
    while t:
        sm2 += t % 10
        t //= 10
    if sm2 == k * sm:
        print(i)
