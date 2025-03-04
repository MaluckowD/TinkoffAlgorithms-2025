from collections import deque

N, K = map(int,input().split())

lst = list(map(int,input().split()))

class Queue:
    def __init__(self):
        self.queue = deque([])
        self.min_stack = deque([float(1000000000000)])

    def push(self, item):
        self.queue.append(item)

        while self.min_stack and item < self.min_stack[-1]:
            self.min_stack.pop()
        self.min_stack.append(item)

    def pop(self):
        if self.queue:
            item = self.queue.popleft()
            if item == self.min_stack[0]:
                self.min_stack.popleft()
            return item
        else:
            return None

    def back(self):
        if self.queue:
            return self.queue[0]
        else:
            return None

    def is_empty(self):
        return len(self.queue) == 0

    def size(self):
        return len(self.queue)

    def minn(self):
        if self.min_stack:
            return self.min_stack[0]
        else:
            return None

q = Queue()
ind = 0
for i in range(K):
  q.push(lst[i])
  ind = i

print(q.minn(), end = " ")
count = 0
while (count != (N - K)):
  ind += 1
  q.pop()
  q.push(lst[ind])
  print(q.minn(), end = " ")
  count += 1