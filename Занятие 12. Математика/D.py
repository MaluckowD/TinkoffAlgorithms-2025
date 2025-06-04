
n = int(input())
ans = 1
for i in range(1, n + 1):
    ans = (ans * i)
    ans = str(ans)
    ans = ans.rstrip("0")
    ans = int(ans)
    ans = ans % 1000000
answ = str(ans)[-1]
print(answ)

