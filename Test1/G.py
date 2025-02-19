n = int(input())
b = list(range(1, n + 1))

for i in range(2, n):
    temp = b[i]
    b[i] = b[i // 2]
    b[i // 2] = temp
    
print(*b)