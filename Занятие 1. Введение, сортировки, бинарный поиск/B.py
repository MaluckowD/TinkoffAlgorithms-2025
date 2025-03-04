def binary_search(arr, x):
  l = -1
  r = len(arr)
  
  ans = [10 ** 10, 10 ** 10]
  while r - l > 1:
    m = (l + r) // 2
    k = abs(arr[m] - x)
    
    if k <= ans[0]:
      if k < ans[0]:
        ans[1] = arr[m]
      if k == ans[0]:
        ans[1] = min(ans[1], arr[m])
      ans[0] = k
    
    if arr[m] == x:
      return arr[m]
    
    if arr[m] < x:
      l = m
    else:
      r = m

  return ans[1]

N, K = map(int,input().split())
a = list(map(int,input().split()))
b = list(map(int,input().split()))
for i in range(K):
  print(binary_search(a, b[i]))
