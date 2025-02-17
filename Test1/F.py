def merge_sort(arr):
  if len(arr) <= 1:
    return arr
  ind = len(arr) // 2
  left = merge_sort(arr[:ind])
  right = merge_sort(arr[ind:])
  return merge(left,right)

def merge(left,right):
  res = []
  i, j = 0, 0
  while i < len(left) and j < len(right):
    if left[i] <= right[j]:
      res.append(left[i])
      i+=1
    else:
      res.append(right[j])
      j+=1
  
  if i < len(left):
    res.extend(left[i:])
  if j < len(right):
    res.extend(right[j:])
  return res

N = int(input())
arr = list(map(int,input().split()))
print(*merge_sort(arr))