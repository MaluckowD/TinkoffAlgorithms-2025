import math

N, K = map(int, input().split())
gcd = math.gcd(N, K)
lcm = (N * K) // gcd
print(lcm)