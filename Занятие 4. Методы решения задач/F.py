def calculate_total_length(segments):
    if not segments:
        return 0

    total_length = 0
    current_end = segments[0][1]
    total_length += current_end - segments[0][0]

    for start, end in segments[1:]:
        if start > current_end:
            total_length += end - start
            current_end = end
        else:
            total_length += max(0, end - current_end)
            current_end = max(current_end, end)

    return total_length


n = int(input())
segments = []
for _ in range(n):
    start, end = map(int, input().split())
    segments.append((start, end))

segments.sort()

total_length = calculate_total_length(segments)
print(total_length)