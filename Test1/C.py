import sys

def binary_search(n):
    l = 1
    r = n
    while r - l >= 0:
        m = (l + r) // 2
        m = min(m, n)
        ans = query(m)

        if ans == "<":
            r = m - 1
        else:
            l = m + 1

    if l <= n and query(l) == "<":
        m = l - 1

    print(f"! {m}")


def query(x):
    print(x)
    sys.stdout.flush()
    return input()

n = int(input())
binary_search(n)