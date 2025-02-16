def binary_search(arr, x):
  l = -1
  r = len(arr)
  while r - l > 1:
    m = (l + r) // 2
    if arr[m] <= x:
      l = m
    else:
      r = m
  return arr[l]

N, K = map(int,input().split())
a = list(map(int,input().split()))
b = list(map(int,input().split()))
for i in range(K):
  print(binary_search(a, b[i]))
