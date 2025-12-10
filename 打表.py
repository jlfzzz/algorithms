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
    d = 911
    r = 420
    degree = 69

    rad = radians(degree)

    t1 = d * d

    t2 = 4 * r * r * sin(rad / 2) * sin(rad / 2)

    if t1 < t2:
        print("Error: Negative value inside sqrt")
        return

    ans = sqrt(t1 - t2)

    print(f"Answer: {ans}")


if __name__ == "__main__":
    main()
