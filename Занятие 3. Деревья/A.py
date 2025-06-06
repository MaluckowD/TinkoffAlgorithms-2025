def diameter(tree):
    start_node = next(iter(tree))
    farthest_node, _ = dfs(tree, start_node)
    _, diameter = dfs(tree, farthest_node)
    return diameter

def dfs(tree, start):
    visited = set()
    stack = [(start, 0)]
    
    max_distance = 0
    farthest_node = start

    while stack:
        node, distance = stack.pop()
        if node not in visited:
            visited.add(node)
            if distance > max_distance:
                max_distance = distance
                farthest_node = node

            for child in tree[node]:
                stack.append((child, distance + 1))

    return farthest_node, max_distance


n = int(input())
p = list(map(int, input().split()))

cur_num = 0
d = {0: 1}
h = {cur_num: 0}
adj = {0: []}
ans = [0]
H = 0

for i in range(n - 1):
    cur_num += 1
    parent = p[i]

    if parent in adj:
        adj[parent].append(cur_num)
    else:
        adj[parent] = [cur_num]

    if cur_num in adj:
        adj[cur_num].append(parent)
    else:
        adj[cur_num] = [parent]

    h_i = h[parent] + 1
    h[cur_num] = h_i
    ans.append(h_i)
    H = max(H, h_i)

D = diameter(adj)

print(H, D)
print(*ans)