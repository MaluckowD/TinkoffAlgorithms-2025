#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int mx = 1e5 + 6;

int n;
ll a[mx], cnt_less[mx];
ll sorted[mx];
int pos_in_sorted[mx];

struct Fenwick {
    ll tree[mx];
    int size;
    
    void init(int sz) {
        size = sz;
        memset(tree, 0, sizeof(tree));
    }
    
    void update(int idx, ll val) {
        for(; idx <= size; idx += idx & -idx)
            tree[idx] += val;
    }
    
    ll query(int idx) {
        ll ret = 0;
        for(; idx > 0; idx -= idx & -idx)
            ret += tree[idx];
        return ret;
    }
};

Fenwick fw_right, fw_left;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        sorted[i] = a[i];
    }

    sort(sorted + 1, sorted + n + 1);
    int sz = unique(sorted + 1, sorted + n + 1) - sorted - 1;
    
    for(int i = 1; i <= n; i++) {
        pos_in_sorted[i] = lower_bound(sorted + 1, sorted + sz + 1, a[i]) - sorted;
    }

    fw_right.init(sz);
    
    for(int i = n; i >= 1; i--) {
        int pos = pos_in_sorted[i];
        cnt_less[i] = fw_right.query(pos - 1);
        fw_right.update(pos, 1);
    }

    fw_left.init(sz);
    ll ans = 0;

    for(int i = 1; i <= n; i++) {
        int pos = pos_in_sorted[i];
        ll cnt_greater = fw_left.query(sz) - fw_left.query(pos);
        ans += cnt_greater * cnt_less[i];
        fw_left.update(pos, 1);
    }

    cout << ans << '\n';

    return 0;
}