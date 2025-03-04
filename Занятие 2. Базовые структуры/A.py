class Stack:
    def __init__(self):
        self.items = []
    
    def is_empty(self):
        return len(self.items) == 0
    
    def push(self, item):
        if self.is_empty():
            self.items.append((item, item))
        else:
            self.items.append((item, min(self.items[-1][1], item)))
    
    def pop(self):
        if self.is_empty():
            return None
        return self.items.pop()
    
    def top(self):
        if self.is_empty() == 0:
            return None
        return self.items[-1][0]
    
    def size(self):
        return len(self.items)
    
    def clear(self):
        self.items = []
    
    def get_min(self):
        if self.is_empty():
            return None
        return self.items[-1][1]

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
        mn = stack.get_min()
        print(mn)