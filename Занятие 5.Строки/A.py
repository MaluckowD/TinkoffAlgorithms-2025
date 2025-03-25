
s = input()
m = int(input())
n = len(s)

def are_equal(a, b, c, d):
    if (b - a) != (d - c):
        return False
    return s[a-1:b] == s[c-1:d]
    

for _ in range(m):
    a, b, c, d = map(int, input().split())
    if are_equal(a, b, c, d):
        print("Yes")
    else:
        print("No")
