#include <iostream>
#include <vector>

using namespace std;

struct Node {
    long long summ, add;
    int replace;

    Node() {
        summ = add = 0ll;
        replace = -1;
    }
};

void push_tree(vector<Node> &tree, int v, int tl, int tr) {
    int tm = (tl + tr) / 2;
    int left_len = tm - tl + 1;
    int right_len = tr - (tm + 1) + 1;

    if (tree[v].replace != -1) {
        tree[v*2].replace = tree[v*2+1].replace = tree[v].replace;
        tree[v*2].add = tree[v*2+1].add = 0;
        tree[v*2].summ = (long long)tree[v].replace * left_len;
        tree[v*2+1].summ = (long long)tree[v].replace * right_len;
        tree[v].replace = -1;
    }

    if (tree[v].add != 0) {
        tree[v*2].add += tree[v].add;
        tree[v*2+1].add += tree[v].add;
        tree[v*2].summ += tree[v].add * left_len;
        tree[v*2+1].summ += tree[v].add * right_len;
        tree[v].add = 0;
    }
}

long long get_sum(vector<Node> &tree, int v, int tl, int tr, int l, int r) {
    if (l > r) return 0;

    if (l == tl && tr == r) {
        return tree[v].summ;
    }

    push_tree(tree, v, tl, tr);
    int tm = (tl + tr) / 2;
    return get_sum(tree, v*2, tl, tm, l, min(r, tm)) + 
           get_sum(tree, v*2+1, tm+1, tr, max(l, tm+1), r);
}

void update_replace(vector<Node> &tree, int v, int tl, int tr, int l, int r, int value) {
    if (l > r) return;

    if (l == tl && tr == r) {
        tree[v].replace = value;
        tree[v].add = 0;
        tree[v].summ = (long long)value * (tr - tl + 1);
    } else {
        push_tree(tree, v, tl, tr);
        int tm = (tl + tr) / 2;
        update_replace(tree, v*2, tl, tm, l, min(r, tm), value);
        update_replace(tree, v*2+1, tm+1, tr, max(l, tm+1), r, value);
        tree[v].summ = tree[v*2].summ + tree[v*2+1].summ;
    }
}

void update_add(vector<Node> &tree, int v, int tl, int tr, int l, int r, int value) {
    if (l > r) return;

    if (l == tl && tr == r) {
        tree[v].add += value;
        tree[v].summ += (long long)value * (tr - tl + 1);
    } else {
        push_tree(tree, v, tl, tr);
        int tm = (tl + tr) / 2;
        update_add(tree, v*2, tl, tm, l, min(r, tm), value);
        update_add(tree, v*2+1, tm+1, tr, max(l, tm+1), r, value);
        tree[v].summ = tree[v*2].summ + tree[v*2+1].summ;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<Node> tree(n * 4);

    char req_type;
    int l, r, v;
    for (int req = 0; req < m; ++req) {
        cin >> req_type;
        if (req_type == '1') {
            cin >> l >> r >> v;
            update_replace(tree, 1, 0, n-1, l, r-1, v);
        } else if (req_type == '2') {
            cin >> l >> r >> v;
            update_add(tree, 1, 0, n-1, l, r-1, v);
        } else {
            cin >> l >> r;
            cout << get_sum(tree, 1, 0, n-1, l, r-1) << '\n';
        }
    }
    return 0;
}