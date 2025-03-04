def f(x):
  return x ** 2 + (x + 1) ** 0.5

c = float(input())
l = 0
r = 10**10
eps = 1e-09
while r - l > eps:
  m = (r + l) / 2
  if f(m) < c:
    l = m
  else:
    r = m
    
print(m)