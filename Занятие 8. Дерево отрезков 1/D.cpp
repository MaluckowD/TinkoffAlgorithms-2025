#include <iostream>
#include <vector>
#include <climits>

using namespace std;

void build(vector<int>& tree, vector<int>& a, int v, int tl, int tr) {
    if (tl == tr) {
        tree[v] = a[tl];
    } else {
        int tm = (tl + tr) / 2;
        build(tree, a, v * 2, tl, tm);
        build(tree, a, v * 2 + 1, tm + 1, tr);
        tree[v] = max(tree[v * 2], tree[v * 2 + 1]);
    }
}

int query(vector<int>& tree, int v, int tl, int tr, int l, int r, int x) {
    if (l > r || tree[v] <= x) {
        return INT_MAX;
    }
    if (tl == tr) {
        return tl;
    }
    int tm = (tl + tr) / 2;
    // Сначала проверяем левое поддерево, если оно пересекается с запросом
    if (l <= tm) {
        int left_res = query(tree, v * 2, tl, tm, l, min(r, tm), x);
        if (left_res != INT_MAX) {
            return left_res;
        }
    }
    // Только если в левом поддереве не нашли, проверяем правое
    return query(tree, v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, x);
}

void update(vector<int>& tree, int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr) {
        tree[v] = new_val;
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm) {
            update(tree, v * 2, tl, tm, pos, new_val);
        } else {
            update(tree, v * 2 + 1, tm + 1, tr, pos, new_val);
        }
        tree[v] = max(tree[v * 2], tree[v * 2 + 1]);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<int> tree(4 * n);
    build(tree, a, 1, 0, n - 1);

    char req_type;
    int i, v, x, l;
    for (int req = 0; req < m; ++req) {
        cin >> req_type;
        if (req_type == '1') {
            cin >> i >> v;
            update(tree, 1, 0, n - 1, i, v);
        } else {
            cin >> x >> l;
            int res = query(tree, 1, 0, n - 1, l + 1, n - 1, x);
            cout << (res == INT_MAX ? -1 : res) << '\n';
        }
    }
    
    return 0;
}