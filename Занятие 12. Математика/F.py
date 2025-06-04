import sys

def fast_pow(a, b, mod):
    result = 1
    a = a % mod
    while b > 0:
        if b % 2 == 1:
            result = (result * a) % mod
        a = (a * a) % mod
        b = b // 2
    return result

N, M, K, MOD = map(int, sys.stdin.readline().split())
mod_total = MOD * K
MN_mod = fast_pow(M, N, mod_total)
x = MN_mod % mod_total
y = K
if y % MOD == 0:
    inv_y = pow(y, MOD - 2, MOD)
else:
    inv_y = pow(y, MOD - 2, MOD)
res = (x % MOD) * inv_y % MOD
print(res)

