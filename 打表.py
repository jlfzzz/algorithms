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

    x =2221
    s1 = str(x)
    s2 = str(x * 8)
    s3 = s1 + s2
    y = int(s3)

    if y % (x + int(s2)) == 0:
        print(x)


        


if __name__ == "__main__":
    main()
