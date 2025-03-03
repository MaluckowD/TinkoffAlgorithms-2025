class Stack:
    def __init__(self):
        self.items = []
    
    def push(self, item):
        if len(self.items) == 0:
            self.items.append((item, item))
        else:
            self.items.append((item, min(self.items[-1][1], item)))
    
    def pop(self):
        if len(self.items) == 0:
            return None
        return self.items.pop()
    
    def top(self):
        if len(self.items) == 0:
            return None
        return self.items[-1]

n = int(input())
stack = Stack()
for i in range(n):
    inp = input()
    if inp[0] == "1":
        b = int(inp.split()[1])
        stack.push(b)
    elif inp[0] == "2":
        stack.pop()
    elif inp[0] == "3":
        x, mn = stack.top()
        print(mn)