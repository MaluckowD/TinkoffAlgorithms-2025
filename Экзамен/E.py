n = int(input())
a = list(map(int, input().split()))
q = int(input())
for _ in range(q):
    query = list(map(int, input().split()))
    if query[0] == 1:
        print(sum(a[query[1] - 1: query[2]]))
    else:
        for j in range(query[1] - 1, query[2]):
            a[j] ^= query[3]