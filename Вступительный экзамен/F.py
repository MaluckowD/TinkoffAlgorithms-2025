def calculate_distance(x, y, a, b):
  if y >= x:
    return (y - x) * a
  else:
    return (x - y) * b


n = int(input())
x_values = list(map(int, input().split()))
q = int(input())

for _ in range(q):
  a, b = map(int, input().split())
  min_total_dist = float('inf')
  
  for y in range(0,2001):
      total_dist = 0
      for x in x_values:
        total_dist += calculate_distance(x, y, a, b)
      min_total_dist = min(min_total_dist, total_dist)

  print(int(min_total_dist))

