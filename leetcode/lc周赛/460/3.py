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

DIRS = [(1, 1), (1, -1), (-1, -1), (-1, 1)]
Max = lambda a, b: b if b > a else a
Min = lambda a, b: b if b < a else a
INF = float("inf")
MOD = int(1e9 + 7)


def sieve(n):
    is_prime = [True] * (n + 1)
    is_prime[0] = is_prime[1] = False

    for i in range(2, int(n**0.5) + 1):
        if is_prime[i]:
            for j in range(i * i, n + 1, i):
                is_prime[j] = False

    primes = [i for i, prime in enumerate(is_prime) if prime]
    return primes


primes = set(sieve(100_005))


from collections import deque, defaultdict
from typing import List


def sieve(n):
    is_prime = [True] * (n + 1)
    is_prime[0] = is_prime[1] = False
    for i in range(2, int(n**0.5) + 1):
        if is_prime[i]:
            for j in range(i * i, n + 1, i):
                is_prime[j] = False
    primes = [i for i, prime in enumerate(is_prime) if prime]
    return primes


primes = set(sieve(100_0005))


class Solution:
    def minJumps(self, nums: List[int]) -> int:
        n = len(nums)
        if n <= 1:
            return 0

        dq = deque()
        dq.append((0, 0))
        dis = [float("inf")] * n
        dis[0] = 0

        mp = defaultdict(list)
        for i, x in enumerate(nums):
            mp[x].append(i)

        jumped = set()
        max_val = max(nums)
        while dq:
            i, d = dq.popleft()

            if d > dis[i]:
                continue

            if i == n - 1:
                return d

            if i - 1 >= 0 and d + 1 < dis[i - 1]:
                dis[i - 1] = d + 1
                dq.append((i - 1, d + 1))
            if i + 1 < n and d + 1 < dis[i + 1]:
                dis[i + 1] = d + 1
                dq.append((i + 1, d + 1))

            x = nums[i]
            if x in primes and x not in jumped:
                jumped.add(x)
                t = x

                while t <= max_val:
                    if t in mp:
                        for future_i in mp[t]:
                            if future_i != i and d + 1 < dis[future_i]:
                                dis[future_i] = d + 1
                                dq.append((future_i, d + 1))
                    t += x
