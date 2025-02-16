def binary_search(arr, x):
  l = 0
  r = len(arr) - 1
  while l <= r:
    m = (l + r) // 2
    if arr[m] == x:
      return "YES"
    elif arr[m] < x:
      l = m + 1
    else:
      r = m - 1
  return "NO"

N, K = map(int,input().split())
a = list(map(int,input().split()))
b = list(map(int,input().split()))
for i in range(K):
  print(binary_search(a, b[i]))
