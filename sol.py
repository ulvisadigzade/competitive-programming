# ==================== IMPORTS ====================

import sys
import math
from collections import defaultdict, deque, Counter
from heapq import heappush, heappop
from bisect import bisect_left, bisect_right


# ==================== FAST IO ====================

input = sys.stdin.buffer.readline


# ==================== INPUT HELPERS ====================

def ints():
    return map(int, input().split())

def list_ints():
    return list(map(int, input().split()))

def int_input():
    return int(input())

def string():
    return input().decode().strip()

def strings():
    return input().decode().split()

def chars():
    return list(input().decode().strip())


# ==================== FAST SCANNER ====================
# Use only for extremely large input

class FastScanner:
    def __init__(self):
        self.data = sys.stdin.buffer.read().split()
        self.idx = 0

    def next(self):
        val = self.data[self.idx]
        self.idx += 1
        return val.decode()

    def int(self):
        val = self.data[self.idx]
        self.idx += 1
        return int(val)

    def float(self):
        val = self.data[self.idx]
        self.idx += 1
        return float(val)


# ==================== CONSTANTS ====================

INF = 10**18
MOD = 10**9 + 7

EPS = 1e-9

# ==================== HELPERS ====================

def ckmin(a, b):
    return min(a, b)

def ckmax(a, b):
    return max(a, b)


def gcd(a, b):
    return math.gcd(a, b)


def lcm(a, b):
    return a // math.gcd(a, b) * b


def is_even(x):
    return x % 2 == 0


def is_odd(x):
    return x % 2 == 1


# ==================== DEBUG ====================

LOCAL = False

def debug(*args):
    if LOCAL:
        print("[DEBUG]", *args, file=sys.stderr)


# ==================== SOLUTION ====================

def solve():
    a = 232
    if a%2==0:
        print(f"It's evenn {a}")


# ==================== MAIN ====================

if __name__ == "__main__":
    solve()