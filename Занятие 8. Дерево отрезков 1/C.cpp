#include <iostream>
#include <vector>

using namespace std;

void build(vector<int>& tree, vector<int>& src, int v, int tl, int tr) {
    if (tl == tr) {
        tree[v] = src[tl];
    } else {
        int tm = (tl + tr) / 2;
        build(tree, src, v * 2, tl, tm);
        build(tree, src, v * 2 + 1, tm + 1, tr);
        tree[v] = tree[v * 2] + tree[v * 2 + 1];
    }
}

int get_kth(vector<int>& tree, int v, int tl, int tr, int k) {
    if (tl == tr) {
        return tl;
    }
    int tm = (tl + tr) / 2;
    if (k < tree[v * 2]) {
        return get_kth(tree, v * 2, tl, tm, k);
    } else {
        return get_kth(tree, v * 2 + 1, tm + 1, tr, k - tree[v * 2]);
    }
}

void update(vector<int>& tree, int v, int tl, int tr, int pos) {
    if (tl == tr) {
        tree[v] ^= 1;  // Инвертируем значение (0->1 или 1->0)
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm) {
            update(tree, v * 2, tl, tm, pos);
        } else {
            update(tree, v * 2 + 1, tm + 1, tr, pos);
        }
        tree[v] = tree[v * 2] + tree[v * 2 + 1];
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
    int i, k;
    for (int req = 0; req < m; ++req) {
        cin >> req_type;
        if (req_type == '1') {
            cin >> i;
            update(tree, 1, 0, n - 1, i);
        } else {
            cin >> k;
            cout << get_kth(tree, 1, 0, n - 1, k) << '\n';
        }
    }
    
    return 0;
}