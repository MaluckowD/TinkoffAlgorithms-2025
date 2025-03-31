from collections import deque

m = int(input())
reactions = {}

for _ in range(m):
    line = input().strip()
    src, dst = line.split('->')
    src = src.strip()
    dst = dst.strip()
    if src not in reactions:
        reactions[src] = []
    reactions[src].append(dst)

start = input().strip()
target = input().strip()

if start == target:
    print(0)
else:
    queue = deque()
    queue.append((start, 0))
    visited = set()
    visited.add(start)
    found = -1

    while queue:
        current, steps = queue.popleft()
        if current in reactions:
            for neighbor in reactions[current]:
                if neighbor == target:
                    found = steps + 1
                    queue = deque()
                    break
                if neighbor not in visited:
                    visited.add(neighbor)
                    queue.append((neighbor, steps + 1))
            if found != -1:
                break

    print(found)