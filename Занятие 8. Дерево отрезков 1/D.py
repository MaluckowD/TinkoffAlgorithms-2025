n, m = map(int, input().split())
a = list(map(int, input().split()))

size = 1
while size < n:
    size <<= 1
tree = [0] * (2 * size)

for i in range(n):
    tree[size + i] = a[i]
for i in range(size - 1, 0, -1):
    tree[i] = max(tree[2 * i], tree[2 * i + 1])

def update(pos, value):
    pos += size
    tree[pos] = value
    pos >>= 1
    while pos >= 1:
        new_val = max(tree[2 * pos], tree[2 * pos + 1])
        if tree[pos] == new_val:
            break
        tree[pos] = new_val
        pos >>= 1

def find_first(x, l, node=1, node_l=0, node_r=size - 1):
    if node_r < l or tree[node] < x:
        return -1
    if node_l == node_r:
        return node_l
    mid = (node_l + node_r) // 2
    left = find_first(x, l, 2 * node, node_l, mid)
    if left != -1:
        return left
    return find_first(x, l, 2 * node + 1, mid + 1, node_r)

output = []
for _ in range(m):
    parts = input().split()
    if not parts:
        continue
    cmd = parts[0]
    if cmd == "1":
        i, v = int(parts[1]), int(parts[2])
        update(i, v)
    elif cmd == "2":
        x, l = int(parts[1]), int(parts[2])
        res = find_first(x, l)
        output.append(str(res))

print("\n".join(output))

