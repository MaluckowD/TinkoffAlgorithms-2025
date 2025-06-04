import math

def factorize(n):
    factors = []
    for d in range(2, int(math.sqrt(n)) + 1):
        if n % d == 0:
            count = 0
            while n % d == 0:
                n //= d
                count += 1
            factors.append((d, count))
    if n > 1:
        factors.append((n, 1))
    return factors

N = int(input())
factors = factorize(N)
output = []
for p, k in factors:
    if k == 1:
        output.append(str(p))
    else:
        output.append(f"{p}^{k}")
print("*".join(output))