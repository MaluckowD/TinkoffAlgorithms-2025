import sys
input = sys.stdin.read
from bisect import bisect_left
from collections import defaultdict

class SegmentTree:
    def __init__(self, size):
        self.N = size
        self.tree = [0] * (4 * size)
        self.lazy = [0] * (4 * size)
        self.max_val = 0
        self.max_pos = 0

    def _push(self, v):
        self.tree[v*2] += self.lazy[v]
        self.lazy[v*2] += self.lazy[v]
        self.tree[v*2+1] += self.lazy[v]
        self.lazy[v*2+1] += self.lazy[v]
        self.lazy[v] = 0

    def _update(self, v, tl, tr, l, r, add):
        if l > r:
            return
        if l == tl and r == tr:
            self.tree[v] += add
            self.lazy[v] += add
        else:
            self._push(v)
            tm = (tl + tr) // 2
            self._update(v*2, tl, tm, l, min(r, tm), add)
            self._update(v*2+1, tm+1, tr, max(l, tm+1), r, add)
            if self.tree[v*2] >= self.tree[v*2+1]:
                self.tree[v] = self.tree[v*2]
            else:
                self.tree[v] = self.tree[v*2+1]

    def update(self, l, r, add):
        self._update(1, 0, self.N-1, l, r, add)

    def _query_max(self, v, tl, tr):
        if tl == tr:
            return (self.tree[v], tl)
        self._push(v)
        tm = (tl + tr) // 2
        if self.tree[v*2] >= self.tree[v*2+1]:
            return self._query_max(v*2, tl, tm)
        else:
            return self._query_max(v*2+1, tm+1, tr)

    def query_max(self):
        return self._query_max(1, 0, self.N-1)

def main():
    data = input().split()
    n = int(data[0])
    idx = 1
    rects = []
    y_coords = set()
    events = []

    for _ in range(n):
        x1 = int(data[idx])
        y1 = int(data[idx+1])
        x2 = int(data[idx+2])
        y2 = int(data[idx+3])
        idx += 4

        if x1 > x2: x1, x2 = x2, x1
        if y1 > y2: y1, y2 = y2, y1

        rects.append((x1, y1, x2, y2))
        y_coords.add(y1)
        y_coords.add(y2)
        events.append((x1, 1, y1, y2))
        events.append((x2 + 1, -1, y1, y2))

    y_list = sorted(y_coords)
    y_map = {v: i for i, v in enumerate(y_list)}
    size = len(y_list)

    events.sort()
    st = SegmentTree(size)

    max_cover = 0
    best_x = 0
    best_y = 0

    for x, typ, y1, y2 in events:
        l = y_map[y1]
        r = y_map[y2]
        st.update(l, r, typ)
        current_max, pos = st.query_max()
        if current_max > max_cover:
            max_cover = current_max
            best_x = x
            best_y = y_list[pos]

    print(max_cover)
    print(best_x, best_y)

main()
