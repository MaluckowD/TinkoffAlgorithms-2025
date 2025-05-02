#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Event {
    int x;
    int type; 
    int y1, y2;

    bool operator<(const Event& other) const {
        if (x != other.x) return x < other.x;
        return type > other.type;
    }
};

struct SegmentTree {
    int size;
    vector<int> tree;
    vector<int> lazy;
    vector<int> pos;

    void init(int n) {
        size = 1;
        while (size < n) size *= 2;
        tree.assign(2 * size, 0);
        lazy.assign(2 * size, 0);
        pos.assign(2 * size, 0);
        for (int i = 0; i < size; ++i) pos[size + i] = i;
        for (int i = size - 1; i > 0; --i) pos[i] = pos[2 * i];
    }

    void push(int node, int l, int r) {
        if (lazy[node] == 0) return;
        tree[node] += lazy[node];
        if (l != r) {
            lazy[2 * node] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
        }
        lazy[node] = 0;
    }

    void range_add(int l, int r, int val, int node, int lx, int rx) {
        push(node, lx, rx);
        if (r < lx || l > rx) return;
        if (l <= lx && rx <= r) {
            lazy[node] += val;
            push(node, lx, rx);
            return;
        }
        int mid = (lx + rx) / 2;
        range_add(l, r, val, 2 * node, lx, mid);
        range_add(l, r, val, 2 * node + 1, mid + 1, rx);
        if (tree[2 * node] >= tree[2 * node + 1]) {
            tree[node] = tree[2 * node];
            pos[node] = pos[2 * node];
        } else {
            tree[node] = tree[2 * node + 1];
            pos[node] = pos[2 * node + 1];
        }
    }

    void range_add(int l, int r, int val) {
        range_add(l, r, val, 1, 0, size - 1);
    }

    pair<int, int> get_max() {
        push(1, 0, size - 1);
        return {tree[1], pos[1]};
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<Event> events;
    vector<int> ys;

    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 > x2) swap(x1, x2); 
        if (y1 > y2) swap(y1, y2); 
        events.push_back({x1, 1, y1, y2});
        events.push_back({x2, -1, y1, y2});
        ys.push_back(y1);
        ys.push_back(y2);
    }

    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    auto get_compressed = [&](int y) {
        return lower_bound(ys.begin(), ys.end(), y) - ys.begin();
    };

    sort(events.begin(), events.end());

    SegmentTree st;
    st.init(ys.size());

    int global_max = 0;
    int best_x = 0, best_y = 0;

    for (const auto& event : events) {
        int x = event.x;
        int type = event.type;
        int y1 = get_compressed(event.y1);
        int y2 = get_compressed(event.y2);

        auto [current_max, current_pos] = st.get_max();
        if (current_max > global_max) {
            global_max = current_max;
            best_x = x;
            best_y = ys[current_pos];
        }

        st.range_add(y1, y2 - 1, type);
    }

    auto [current_max, current_pos] = st.get_max();
    if (current_max > global_max) {
        global_max = current_max;
        best_y = ys[current_pos];
    }

    cout << global_max << "\n";
    cout << best_y << " " << best_x << "\n"; 

    return 0;
}