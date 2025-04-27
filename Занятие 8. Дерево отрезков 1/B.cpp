#include <iostream>
#include <vector>
#include <climits>

using namespace std;

pair<int, int> combine(pair<int, int> a, pair<int, int> b) {
    if (a.first < b.first) return a;
    if (a.first > b.first) return b;
    return make_pair(a.first, a.second + b.second);
}

void build(vector<pair<int, int>> &tree, vector<int> &a, int v, int tl, int tr) {
    if (tl == tr) {
        tree[v] = make_pair(a[tl], 1);
    } else {
        int tm = (tl + tr) / 2;
        build(tree, a, v * 2, tl, tm);
        build(tree, a, v * 2 + 1, tm + 1, tr);
        tree[v] = combine(tree[v * 2], tree[v * 2 + 1]);
    }
}

pair<int, int> get_min(vector<pair<int, int>> &tree, int v, int tl, int tr, int l, int r) {
    if (l > r) return make_pair(INT_MAX, 0);
    if (l == tl && r == tr) return tree[v];

    int tm = (tl + tr) / 2;
    return combine(
        get_min(tree, v * 2, tl, tm, l, min(r, tm)),
        get_min(tree, v * 2 + 1, tm + 1, tr, max(l, tm + 1), r)
    );
}

void update(vector<pair<int, int>> &tree, int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr) {
        tree[v] = make_pair(new_val, 1);
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm) {
            update(tree, v * 2, tl, tm, pos, new_val);
        } else {
            update(tree, v * 2 + 1, tm + 1, tr, pos, new_val);
        }
        tree[v] = combine(tree[v * 2], tree[v * 2 + 1]);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    vector<pair<int, int>> tree(n * 4);
    build(tree, a, 1, 0, n - 1);

    char req_type;
    int i, v, l, r;
    pair<int, int> result;
    for (int req = 0; req < m; ++req) {
        cin >> req_type;
        if (req_type == '1') {
            cin >> i >> v;
            update(tree, 1, 0, n - 1, i, v);
        } else {
            cin >> l >> r;
            result = get_min(tree, 1, 0, n - 1, l, r - 1);
            cout << result.first << ' ' << result.second << '\n';
        }
    }
    
    return 0;
}