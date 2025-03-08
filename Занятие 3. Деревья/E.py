class MinHeap:
    def __init__(self):
        self.heap = [0]
        self.size = 0
    
    def shiftUp(self, i):
        while i // 2 > 0 and self.heap[i] < self.heap[i // 2]:
            self.heap[i], self.heap[i // 2] = self.heap[i // 2], self.heap[i]
            i = i // 2
    
    def insert(self, x):
        self.heap.append(x)
        self.size += 1
        self.shiftUp(self.size)
    
    def shiftDown(self, i):
        while i * 2 <= self.size:
            j = self.indMinChild(i)
            if self.heap[i] > self.heap[j]:
                self.heap[i], self.heap[j] = self.heap[j], self.heap[i]
            i = j
    
    def indMinChild(self, i):
        if i * 2 + 1 > self.size:
            return i * 2
        if self.heap[i * 2] < self.heap[i * 2 + 1]:
            return i * 2
        return i * 2 + 1
    def delMin(self):
        if self.size == 0:
            return None
        removed = self.heap[1]
        self.heap[1] = self.heap[self.size]
        self.size -= 1
        self.heap.pop()
        self.shiftDown(1)
        return removed
    def getMin(self):
        if self.size == 0:
            return None
        return self.heap[1]

heap = MinHeap()
n = int(input())
lst = list(map(int, input().split()))

for i in range(n):
    heap.insert(lst[i])
    
for i in range(n):
    print(heap.getMin(), end = " ")
    heap.delMin()