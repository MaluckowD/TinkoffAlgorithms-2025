n = int(input())
a = list(map(int, input().split()))

count = 0
for i in range(2, n):
    if a[i] < a[i - 1] < a[i - 2]:
        count += 1
print(count)