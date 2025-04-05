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

    vector<int> dp(n, -1e9); 
    vector<int> prev(n, -1);  
    dp[0] = coins[0];
    
    deque<int> q;  
    q.push_back(0);

    for (int i = 1; i < n; ++i) {
        while (!q.empty() && q.front() < i - k) {
            q.pop_front();
        }
        
        if (!q.empty()) {
            int best_prev = q.front();
            dp[i] = dp[best_prev] + coins[i];
            prev[i] = best_prev;
        }
        
        while (!q.empty() && dp[i] >= dp[q.back()]) {
            q.pop_back();
        }
        q.push_back(i);
    }

    cout << dp[n-1] << endl;

    vector<int> path;
    for (int cur = n-1; cur != -1; cur = prev[cur]) {
        path.push_back(cur + 1); 
    }
    reverse(path.begin(), path.end());
    
    cout << path.size() - 1 << endl;
    for (int x : path) {
        cout << x << ' ';
    }
    cout << endl;

    return 0;
}