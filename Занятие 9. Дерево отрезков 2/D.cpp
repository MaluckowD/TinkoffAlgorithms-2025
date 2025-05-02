#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

struct Event {
    int x;
    int y1, y2;
    bool is_start;
};

struct Node {
    int max_val;
    int max_pos;
    int add;
};

bool compareEvents(const Event& a, const Event& b) {
    return (a.x < b.x) || (a.x == b.x && a.is_start && !b.is_start);
}

class SegmentTree {
private:
    vector<Node> tree;
    int size;
    int offset;
    
    void push(int v, int l, int r) {
        if (tree[v].add == 0) return;
        
        tree[v].max_val += tree[v].add;
        
        if (l != r) {
            tree[2*v+1].add += tree[v].add;
            tree[2*v+2].add += tree[v].add;
        }
        
        tree[v].add = 0;
    }
    
    void update(int v, int l, int r, int ql, int qr, int val) {
        push(v, l, r);
        
        if (qr < l || r < ql) return;
        
        if (ql <= l && r <= qr) {
            tree[v].add += val;
            push(v, l, r);
            return;
        }
        
        int mid = (l + r) / 2;
        update(2*v+1, l, mid, ql, qr, val);
        update(2*v+2, mid+1, r, ql, qr, val);
        
        if (tree[2*v+1].max_val >= tree[2*v+2].max_val) {
            tree[v].max_val = tree[2*v+1].max_val;
            tree[v].max_pos = tree[2*v+1].max_pos;
        } else {
            tree[v].max_val = tree[2*v+2].max_val;
            tree[v].max_pos = tree[2*v+2].max_pos;
        }
    }
    
public:
    SegmentTree(int min_y, int max_y) {
        offset = -min_y;
        size = 1;
        int range = max_y - min_y + 1;
        while (size < range) size <<= 1;
        tree.resize(2*size);
        
        for (int i = 0; i < size; ++i) {
            tree[size-1+i].max_pos = i;
        }
        
        for (int i = size-2; i >= 0; --i) {
            tree[i].max_pos = tree[2*i+1].max_pos;
        }
    }
    
    void add(int y1, int y2, int val) {
        update(0, 0, size-1, y1 + offset, y2 + offset, val);
    }
    
    pair<int, int> get_max() {
        return {tree[0].max_val, tree[0].max_pos - offset};
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<Event> events;
    int min_y = INT_MAX, max_y = INT_MIN;
    
    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        
        // Учитываем, что y увеличивается сверху вниз
        // Поэтому y1 - верхняя координата (меньшее значение y)
        // y2 - нижняя координата (большее значение y)
        if (y1 > y2) swap(y1, y2);
        
        events.push_back({x1, y1, y2, true});  // Левая граница (начало)
        events.push_back({x2, y1, y2, false}); // Правая граница (конец)
        
        min_y = min(min_y, y1);
        max_y = max(max_y, y2);
    }
    
    sort(events.begin(), events.end(), compareEvents);
    
    SegmentTree st(min_y, max_y);
    
    int max_count = 0;
    int result_x = 0, result_y = 0;
    
    for (const auto& e : events) {
        st.add(e.y1, e.y2, e.is_start ? 1 : -1);
        
        auto current = st.get_max();
        if (current.first > max_count) {
            max_count = current.first;
            result_x = e.x;
            // Для y берем верхнюю границу (минимальное y)
            result_y = e.y1;
        }
    }
    
    cout << max_count << "\n";
    cout << result_x << " " << result_y << "\n";
    
    return 0;
}