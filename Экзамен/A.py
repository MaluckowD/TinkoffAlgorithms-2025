import sys


N, M = map(int, sys.stdin.readline().split())
computers = []
for _ in range(M):
    T, B, Y = map(int, sys.stdin.readline().split())
    computers.append((T, B, Y))

left = 0
right = max((N // B) * (B * T + Y) + (N % B) * T for T, B, Y in computers)

def is_possible(t):
    total = 0
    for T, B, Y in computers:
        full_blocks = t // (B * T + Y)
        remaining_time = t % (B * T + Y)
        remaining_tasks = min(B, remaining_time // T)
        total += full_blocks * B + remaining_tasks
        if total >= N:
            return True
    return total >= N

answer_time = 0
while left <= right:
    mid = (left + right) // 2
    if is_possible(mid):
        answer_time = mid
        right = mid - 1
    else:
        left = mid + 1

distribution = []
remaining = N
for T, B, Y in computers:
    full_blocks = answer_time // (B * T + Y)
    remaining_time = answer_time % (B * T + Y)
    remaining_tasks = min(B, remaining_time // T)
    k_i = full_blocks * B + remaining_tasks
    if remaining >= k_i:
        distribution.append(k_i)
        remaining -= k_i
    else:
        distribution.append(remaining)
        remaining = 0
while len(distribution) < M:
    distribution.append(0)

print(answer_time)
print(' '.join(map(str, distribution)))

