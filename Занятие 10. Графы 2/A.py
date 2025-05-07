n, m = map(int, input().split())

class DisjointSetUnion:
    def __init__(self, size):
        self.parent = list(range(size + 1))
        self.rank = [0] * (size + 1)
        self.set_size = [1] * (size + 1)
        self.min_val = list(range(size + 1))
        self.max_val = list(range(size + 1))
    
    def find(self, x):
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]
    
    def unite(self, x, y):
        x_root = self.find(x)
        y_root = self.find(y)
        
        if x_root == y_root:
            return
        
        if self.rank[x_root] < self.rank[y_root]:
            x_root, y_root = y_root, x_root
        
        self.parent[y_root] = x_root
        self.set_size[x_root] += self.set_size[y_root]
        self.min_val[x_root] = min(self.min_val[x_root], self.min_val[y_root])
        self.max_val[x_root] = max(self.max_val[x_root], self.max_val[y_root])
        
        if self.rank[x_root] == self.rank[y_root]:
            self.rank[x_root] += 1

dsu = DisjointSetUnion(n)

for _ in range(m):
    parts = input().split()
    cmd = parts[0]
    
    if cmd == 'union':
        x, y = map(int, parts[1:])
        dsu.unite(x, y)
    elif cmd == 'get':
        x = int(parts[1])
        root = dsu.find(x)
        print(dsu.min_val[root], dsu.max_val[root], dsu.set_size[root])