#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> coins(n);
    coins[0] = 0;
    coins[n-1] = 0;
    for (int i = 1; i < n-1; ++i) {
        cin >> coins[i];
    }

    vector<int> dp(n, -1e9);  // dp[i] - максимальное количество монет до i-го столбика
    vector<int> prev(n, -1);   // prev[i] - предыдущий столбик в оптимальном пути
    dp[0] = coins[0];
    
    deque<int> q;  // Очередь для хранения индексов (sliding window minimum)
    q.push_back(0);

    for (int i = 1; i < n; ++i) {
        // Удаляем элементы, которые уже вне окна k
        while (!q.empty() && q.front() < i - k) {
            q.pop_front();
        }
        
        if (!q.empty()) {
            int best_prev = q.front();
            dp[i] = dp[best_prev] + coins[i];
            prev[i] = best_prev;
        }
        
        // Поддерживаем очередь в порядке убывания dp[j]
        while (!q.empty() && dp[i] >= dp[q.back()]) {
            q.pop_back();
        }
        q.push_back(i);
    }

    cout << dp[n-1] << endl;
    
    // Восстанавливаем путь
    vector<int> path;
    for (int cur = n-1; cur != -1; cur = prev[cur]) {
        path.push_back(cur + 1);  // +1 для 1-based индексации
    }
    reverse(path.begin(), path.end());
    
    cout << path.size() - 1 << endl;
    for (int x : path) {
        cout << x << ' ';
    }
    cout << endl;

    return 0;
}