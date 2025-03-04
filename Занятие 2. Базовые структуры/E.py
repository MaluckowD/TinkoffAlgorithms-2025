from collections import deque

class Stack:
    def __init__(self):
        self.stack = []

    def push(self, num):
        self.stack.append(num)

    def pop(self):
        return self.stack.pop()

    def is_empty(self):
        return len(self.stack) == 0

    def peek(self):
        return self.stack[-1] if not self.is_empty() else None


def solve():
    answer = []
    stack = Stack()
    dq = deque()
    num = 1  
    total_operations = 0 

    for val in tr:
        if not stack.is_empty() and val > stack.peek():
            print(0)
            return

        dq.append(1)
        stack.push(val)

        while not stack.is_empty() and stack.peek() == num:
            dq.append(2)
            stack.pop()
            num += 1

    if not dq:
        print(0)
        return

    current_operation = dq.popleft()
    count = 1
    while dq:
        next_operation = dq.popleft()
        if next_operation == current_operation:
            count += 1
        else:
            total_operations += 1
            answer.append((current_operation, count))
            current_operation = next_operation
            count = 1

    total_operations += 1
    answer.append((current_operation, count))

    print(total_operations)
    for operation, cnt in answer:
        print(operation, cnt)


n = int(input())
tr = list(map(int, input().split()))

solve()