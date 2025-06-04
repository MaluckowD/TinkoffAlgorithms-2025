def square(heights):
    stack = []
    max_square = 0
    heights.append(0)

    for i, h in enumerate(heights):
        while stack and heights[stack[-1]] > h:
            height = heights[stack.pop()]
            width = i if not stack else i - stack[-1] - 1
            max_square = max(max_square, height * width)
        stack.append(i)

    return max_square


n = int(input())
a = list(map(int, input().split()))
print(square(a))