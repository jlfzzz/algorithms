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

    pre = 0
    arr = [0] * 31
    for i in range(30):
        arr[i] = 1 + pre
        pre = pre + arr[i]
    
    for x in arr:
        print(x)
    


if __name__ == "__main__":
    main()
