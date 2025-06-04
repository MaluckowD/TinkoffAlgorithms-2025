import sys

MOD = 10**9 + 7

n, k = map(int, sys.stdin.readline().split())

max_n = n
fact = [1] * (max_n + 1)
for i in range(1, max_n + 1):
    fact[i] = fact[i - 1] * i % MOD

inv_fact = [1] * (max_n + 1)
inv_fact[max_n] = pow(fact[max_n], MOD - 2, MOD)
for i in range(max_n - 1, -1, -1):
    inv_fact[i] = inv_fact[i + 1] * (i + 1) % MOD

if k < 0 or k > n:
    print(0)
else:
    res = fact[n] * inv_fact[k] % MOD
    res = res * inv_fact[n - k] % MOD
    print(res)

