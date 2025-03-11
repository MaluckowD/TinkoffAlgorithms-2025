from functools import lru_cache
import sys

sys.setrecursionlimit(10 ** 9)

class Node:
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None

def height(node):
    if node is None:
        return 0
    return 1 + max(height(node.left), height(node.right))

def is_balanced(node):
    if node is None:
        return True
    lh = height(node.left)
    rh = height(node.right)
    return abs(lh - rh) <= 1 and is_balanced(node.left) and is_balanced(node.right)

def is_bst(node, min_val=float('-inf'), max_val=float('inf')):
    if node is None:
        return True
    if not (min_val < node.key < max_val):
        return False
    return (is_bst(node.left, min_val, node.key) and
           (is_bst(node.right, node.key, max_val)))

def is_avl_tree(root):
    if root is None:
        return True
    return is_balanced(root) and is_bst(root)

n, r = map(int, input().split())

nodes = [Node(i) for i in range(n)]
for i in range(n):
    li, ri = map(int, input().split())
    if li != -1:
        nodes[i].left = nodes[li]
    if ri != -1:
        nodes[i].right = nodes[ri]

if is_avl_tree(nodes[r]):
    print(1)
else:
    print(0)