#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

long long get_min(vector<pair<long long, long long>> &tree, int v, int tl, int tr, int l, int r) {
    if (l > r) return LLONG_MAX;

    long long additional = tree[v].second;

    if (l == tl && tr == r) return tree[v].first + additional;

    int tm = (tl + tr) / 2;
    return min(
        get_min(tree, v * 2, tl, tm, l, min(r, tm)),
        get_min(tree, v * 2 + 1, tm + 1, tr, max(l, tm + 1), r)
    ) + additional;
}

void update(vector<pair<long long, long long>> &tree, int v, int tl, int tr, int l, int r, int value) {
    if (l > r) return;

    if (l == tl && tr == r) {
        tree[v].second += value;
    } else {
        int tm = (tl + tr) / 2;
        update(tree, v * 2, tl, tm, l, min(r, tm), value);
        update(tree, v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, value);
        tree[v].first = min(
            tree[v * 2].first + tree[v * 2].second,
            tree[v * 2 + 1].first + tree[v * 2 + 1].second
        );
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<pair<long long, long long>> tree(n * 4);
    for (size_t i = 0; i < tree.size(); ++i) {
        tree[i].first = 0ll;
        tree[i].second = 0ll;
    }

    char req_type;
    int l, r, v;
    for (int req = 0; req < m; ++req) {
        cin >> req_type;
        if (req_type == '1') {
            cin >> l >> r >> v;
            update(tree, 1, 0, n - 1, l, r - 1, v);
        } else {
            cin >> l >> r;
            cout << get_min(tree, 1, 0, n - 1, l, r - 1) << '\n';
        }
    }
    return 0;
}