ls = input().split()

oper = {'+': lambda x, y: x + y,
        '-': lambda x, y: x - y,
        '*': lambda x, y: x * y,
        '/': lambda x, y: x / y,}

stack = []
for item in ls:
  if item in oper:
    b, a = stack.pop(), stack.pop()
    stack.append(oper[item](a, b))
  else:
    stack.append(int(item))

print(stack[0])