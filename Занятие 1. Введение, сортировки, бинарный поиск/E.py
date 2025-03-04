def f(x, a, b, c, d):
  return a * x ** 3 + b * x ** 2 + c * x + d

a, b, c, d = map(int, input().split())
l = -100000
r = 100000

eps = 1e-13
for i in range(100):
  m = (r + l) / 2
  if abs(f(m, a, b, c, d)) <= eps:
    print(m)
    exit(0)
  if f(m, a, b, c, d) * f(r, a, b, c, d) < 0:
    l = m
  else:
    r = m

print(m)