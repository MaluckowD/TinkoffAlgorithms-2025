
def calculate_rectangle_sum(prefix_sums, y1, x1, y2, x2):
    rectangle_sum = 0
    for row in range(y1, y2 + 1):
        rectangle_sum += prefix_sums[row][x2] - prefix_sums[row][x1 - 1] if x1 > 0 else prefix_sums[row][x2]
    return rectangle_sum


n, m, k = map(int, input().split())

prefix_sums = [[0] * m for _ in range(n)]
for i in range(n):
    row_values = list(map(int, input().split()))
    row_sum = 0
    for j in range(m):
        row_sum += row_values[j]
        prefix_sums[i][j] = row_sum

for i in range(k):
    y1, x1, y2, x2 = map(lambda x: int(x) - 1, input().split())
    rectangle_sum = calculate_rectangle_sum(prefix_sums, y1, x1, y2, x2)
    print(rectangle_sum)