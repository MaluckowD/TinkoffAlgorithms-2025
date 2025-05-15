#include <algorithm>
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

void build(vector<vector<pair<int, int>>> &graph, vector<int> &depth, vector<vector<pair<int, int>>> &dp, int max_i, int v, int p = -1, int c = INT_MAX) {
    if (p != -1) depth[v] = depth[p] + 1;

    if (p == -1) p = v;
    dp[v][0] = make_pair(p, c);
    for (int i = 1; i <= max_i; ++i) {
        dp[v][i].first = dp[dp[v][i - 1].first][i - 1].first;
        dp[v][i].second = min(dp[v][i - 1].second, dp[dp[v][i - 1].first][i - 1].second);
    }

    for (auto next : graph[v]) {
        build(graph, depth, dp, max_i, next.first, v, next.second);
    }
}

int min_lca(vector<int> &depth, vector<vector<pair<int, int>>> &dp, int max_i, int u, int v) {
    int res = INT_MAX;

    if (depth[v] > depth[u]) swap(v, u);

    for (int i = max_i; i >= 0; --i) {
        if (depth[u] - (1 << i) >= depth[v]) {
            res = min(res, dp[u][i].second);
            u = dp[u][i].first;
        }
    }

    if (v == u) return res;

    for (int i = max_i; i >= 0; --i) {
        if (dp[v][i].first != dp[u][i].first) {
            res = min(res, dp[v][i].second);
            v = dp[v][i].first;
            res = min(res, dp[u][i].second);
            u = dp[u][i].first;
        }
    }

    res = min(res, dp[u][0].second);
    res = min(res, dp[v][0].second);

    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m, x, y, u, v;
    cin >> n;

    vector<vector<pair<int, int>>> graph(n);
    for (int i = 1; i < n; ++i) {
        cin >> x >> y;
        graph[x].emplace_back(i, y);
    }

    vector<int> depth(n, 0);
    vector<vector<pair<int, int>>> dp(n);
    int max_i = 0;
    while ((1 << (max_i + 1)) <= n) ++max_i;
    for (int i = 0; i < n; ++i) dp[i].resize(max_i + 1);

    build(graph, depth, dp, max_i, 0);

    cin >> m;
    for (int req = 0; req < m; ++req) {
        cin >> u >> v;
        cout << min_lca(depth, dp, max_i, u, v) << '\n';
    }
}