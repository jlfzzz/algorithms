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

# x1 = 1313112
x1 = 562423413413131
st = set()
for i in range(100):
    print(bin(x1))
    st.add(x1)
    x1 = x1 ^ (x1 // 2)
    if x1 in st:
        print("find")
        print(x1)
        print(i)
        break
