# ===================== 🌐 标准库通用 =====================

import os
import sys
import copy
import math
import time
import random
import re
import heapq
import bisect

from pathlib import Path
from enum import Enum, auto
from typing import List, Dict, Set, Tuple, Optional, Any, Union, Callable, Iterator
from dataclasses import dataclass, field
from datetime import datetime, timedelta, timezone
from decimal import Decimal, getcontext

# ===================== 🧩 数据结构相关 =====================

from collections import Counter, defaultdict, deque, namedtuple, OrderedDict

# ===================== 🔁 函数式工具 =====================

import functools
from functools import lru_cache, reduce, partial, cmp_to_key

# ===================== 🔢 数学与精度 =====================

from math import gcd, lcm, ceil, floor, sqrt, log2, log10, factorial, comb, perm
from random import randint, choice, sample, shuffle, uniform

# ===================== 🔍 正则表达式 =====================

import re

# ===================== 🧮 算法与竞赛常用 =====================

# 排列组合、积累、笛卡尔积、分组等
from itertools import combinations, permutations, product, accumulate, groupby

# 优先队列（小顶堆/大顶堆）
import heapq  # heapq.heappush(), heappop(), heapify()

# 二分搜索
import bisect  # bisect.bisect_left(), bisect.bisect_right()

# 快速递归缓存
from functools import lru_cache

# 有序并查集等结构可能用到的构造器
from collections import defaultdict

# ===================== 🧪 调试工具（可选） =====================

from pprint import pprint  # 更漂亮地打印调试数据结构
import logging  # logging.debug/info/warning/error

# ===================== 🛠️ 其他工具类（按需） =====================

# from typing_extensions import TypedDict, Literal  # 若 Python 版本较老

# ===================== ✅ 模板完成 =====================
