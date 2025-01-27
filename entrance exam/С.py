def check(day):
    for i in range(n):
        count = 0
        for j in range(n):
            if i != j:
                if h[j] + a[j] * day > h[i] + a[i] * day:
                      count += 1
        if count != target[i]:
            return False
    return True

T = int(input())
for _ in range(T):
  n = int(input())
  h = list(map(int, input().split()))
  a = list(map(int, input().split()))
  target = list(map(int, input().split()))


  left, right = 0, 2000 
  result = -1

  while left <= right:
      mid = left + (right - left) // 2
      if check(mid):
        result = mid
        right = mid - 1
      else:
          left = mid + 1
        

  print(result)

