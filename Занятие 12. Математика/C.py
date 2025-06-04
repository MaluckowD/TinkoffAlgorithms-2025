from math import sqrt

def is_prime(num):
    if num < 2:
        return False
    for d in range(2, int(sqrt(num)) + 1):
        if num % d == 0:
            return False
    return True

n = int(input())

if is_prime(n - 2):
    print(2, n - 2)
else:
    p = 3
    while p <= n // 2:
        if is_prime(p) and is_prime(n - p):
            print(p, n - p)
            break
        p += 2