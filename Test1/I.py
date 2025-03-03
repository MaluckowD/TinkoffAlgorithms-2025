n = int(input())
pos = list(map(int, input().split()))

results = [0] * n
k = 1 
ans = [1]

for i in range(n):
    results[pos[i] - 1] = 1
    k += 1

    while results and results[-1] == 1:
        results.pop() 
        k -= 1  

    ans.append(k)

print(*ans)