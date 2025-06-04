from collections import deque


ptr = 0
N, M = map(int, input().split())
ptr += 1
grid = []
for _ in range(N):
    line = input().strip()
    grid.append(line)
    ptr += 1

visited = [[False for _ in range(M)] for _ in range(N)]
directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
intact = 0
hit = 0
destroyed = 0

for i in range(N):
    for j in range(M):
        if not visited[i][j] and (grid[i][j] == '#' or grid[i][j] == 'X'):
            queue = deque()
            queue.append((i, j))
            visited[i][j] = True
            has_intact = False
            has_hit = False

            while queue:
                x, y = queue.popleft()
                if grid[x][y] == '#':
                    has_intact = True
                elif grid[x][y] == 'X':
                    has_hit = True

                for dx, dy in directions:
                    nx, ny = x + dx, y + dy
                    if 0 <= nx < N and 0 <= ny < M:
                        if not visited[nx][ny] and (grid[nx][ny] == '#' or grid[nx][ny] == 'X'):
                            visited[nx][ny] = True
                            queue.append((nx, ny))

            if has_intact and not has_hit:
                intact += 1
            elif has_intact and has_hit:
                hit += 1
            elif not has_intact and has_hit:
                destroyed += 1
print(intact, hit, destroyed)


