from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
from typing import *
from queue import *

MOD = int(1e9 + 7)
DIRS = [(1, 1), (1, -1), (-1, -1), (-1, 1)]
INF = int(1e9)


class Solution:
    def watchedVideosByFriends(
        self,
        watchedVideos: List[List[str]],
        friends: List[List[int]],
        id: int,
        level: int,
    ) -> List[str]:
        if level == 0:
            return []

        visited = set()
        visited.add(id)  
        q = Queue()
        q.put(id)

        for i in range(level):
            n = q.qsize()
            for j in range(n):
                x = q.get()
                for friend in friends[x]:
                    if friend not in visited:
                        visited.add(friend)
                        q.put(friend)

        video_count = defaultdict(int)
        while not q.empty():
            friend = q.get()
            for video in watchedVideos[friend]:
                video_count[video] += 1

        ans = list(video_count.keys())
        ans.sort(key=lambda x: (video_count[x], x))
        return ans
