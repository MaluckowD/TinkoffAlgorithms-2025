import sys
MOD = 10**9 + 9

N = int(sys.stdin.readline())

sieve = [True] * 1000
sieve[0] = sieve[1] = False
for i in range(2, int(1000**0.5) + 1):
    if sieve[i]:
        sieve[i*i : 1000 : i] = [False] * len(sieve[i*i : 1000 : i])
primes = [i for i in range(100, 1000) if sieve[i]]

transitions = {}
for a in range(10):
    for b in range(10):
        transitions[(a, b)] = []
        for c in range(10):
            num = 100 * a + 10 * b + c
            if num >= 100 and sieve[num]:
                transitions[(a, b)].append(c)

if N == 3:
    print(len(primes))
    exit(0)

dp = {}
for a in range(10):
    for b in range(10):
        dp[(a, b)] = 0
for prime in primes:
    a = prime // 100
    b = (prime // 10) % 10
    c = prime % 10
    dp[(b, c)] += 1

for _ in range(4, N + 1):
    new_dp = {}
    for a in range(10):
        for b in range(10):
            new_dp[(a, b)] = 0
    for (a, b), count in dp.items():
        for c in transitions.get((a, b), []):
            new_dp[(b, c)] = (new_dp[(b, c)] + count) % MOD
    dp = new_dp

total = sum(dp.values()) % MOD
print(total)