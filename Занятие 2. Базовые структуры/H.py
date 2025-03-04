class Stack:
    def __init__(self):
        self.stack = []

    def push(self, num):
        self.stack.append(num)

    def pop(self):
        return self.stack.pop()

    def empty(self):
        return len(self.stack) == 0

    def top(self):
        return self.stack[-1][0]

    def get_last(self):
        return self.stack[-1][1]


def prefix_sums(arr):
    result = [0] * (len(arr) + 1)
    for i in range(len(arr)):
        result[i + 1] = result[i] + arr[i]
    return result


def get_prev_smaller(arr):
    n = len(arr)
    stack = Stack()
    result = [[-1, n] for _ in range(n)]

    for i in range(n):
        while not stack.empty() and stack.top() >= arr[i]:
            stack.pop()
        if not stack.empty():
            result[i][0] = stack.get_last()
        stack.push((arr[i], i))

    stack = Stack()

    for i in range(n - 1, -1, -1):
        while not stack.empty() and stack.top() >= arr[i]:
            stack.pop()
        if not stack.empty():
            result[i][1] = stack.get_last()
        stack.push((arr[i], i))

    return result


def main():
    n = int(input())
    a = list(map(int, input().split()))
    segments = get_prev_smaller(a)
    ps = prefix_sums(a)
    max_product = -10 ** 28

    for i in range(n):
        num = a[i]
        left = segments[i][0]
        right = segments[i][1]

        if left != -1:
            current_sum = ps[right] - ps[left + 1]
        else:
            current_sum = ps[right]

        current_product = current_sum * num
        max_product = max(max_product, current_product)

    print(max_product)


if __name__ == "__main__":
    main()