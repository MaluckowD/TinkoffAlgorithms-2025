

def f1(s):
  n = len(s)
  ans = {}
  for el in s:
      ans[el] = 0

  for i in range(len(s)):
      ans[s[i]] += (i + 1) * (len(s) - i)

  return sorted(ans.items())


def f2(s):
  n = len(s)
  counts = {}
  for i in range(n):
    for j in range(i, n):
      for k in range(i, j+1):
        if s[k] not in counts:
            counts[s[k]] = 0
        counts[s[k]] += 1

  return sorted(counts.items())

s = input()
if f1(s) == f2(s):
  print("YES")
else:
  print("NO")


