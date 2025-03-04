class Stack:
    def __init__(self):
        self.items = []
        self.count = 0

    def isEmpty(self):
        return self.items == []

    def push(self, item):
        if self.isEmpty():
            self.items.append((item, 1))
        else:
            if self.items[-1][0] == item:
                last = self.items.pop()
                self.items.append((item, last[1] + 1))
            else:
                if self.items[-1][1] >= 3:
                    elem = self.items.pop()
                    self.count += elem[1]

                if not self.isEmpty() and self.items[-1][0] == item:
                    last = self.items.pop()
                    self.items.append((item, last[1] + 1))
                else:
                    self.items.append((item, 1))

    def get_count(self):
        return self.count


n = int(input())
a = list(map(int, input().split()))
s = Stack()

for i in range(len(a)):
    s.push(a[i])

s.push(10)
ans = s.get_count()
print(ans)