#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <array>
#include <climits>

using namespace std;

const int MAX_TIME = 1440;
const int SPECIAL_CASE_CUPS = 10000000;

struct Road {
    int to;
    int time;
    int cups;
};

class CupOptimizer {
private:
    int n, m;
    vector<vector<Road>> graph;
    set<int> uniqueCups;

public:
    CupOptimizer(int nodes, int edges) : n(nodes), m(edges) {
        graph.resize(n + 1);
    }

    void addRoad(int from, int to, int time, int weight) {
        int cups = (weight - 3000000) / 100;
        if (cups > 0) {
            graph[from].push_back({to, time, cups});
            graph[to].push_back({from, time, cups});
            uniqueCups.insert(cups);
        }
    }

    int findShortestPathWithCups(int cups) {
        vector<bool> visited(n + 1, false);
        priority_queue<pair<int, int>> pq; // (-time, node)
        pq.push({0, 1}); // Start from node 1 with time 0

        while (!pq.empty()) {
            auto [negativeTime, node] = pq.top();
            pq.pop();
            int currentTime = -negativeTime;

            if (currentTime > MAX_TIME) return 0;
            if (node == n) return currentTime;
            if (visited[node]) continue;
            
            visited[node] = true;

            for (const auto& road : graph[node]) {
                if (road.cups >= cups && !visited[road.to]) {
                    int newTime = currentTime + road.time;
                    if (newTime <= MAX_TIME) {
                        pq.push({-newTime, road.to});
                    }
                }
            }
        }
        return 0;
    }

    int findMaximumCups() {
        if (n == 1) return SPECIAL_CASE_CUPS;

        vector<int> cupsList(uniqueCups.begin(), uniqueCups.end());
        int left = 0;
        int right = cupsList.size() - 1;
        int maxCups = 0;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            int result = findShortestPathWithCups(cupsList[mid]);

            if (result > 0) {
                maxCups = max(maxCups, cupsList[mid]);
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return maxCups;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    CupOptimizer optimizer(n, m);

    for (int i = 0; i < m; ++i) {
        int from, to, time, weight;
        cin >> from >> to >> time >> weight;
        optimizer.addRoad(from, to, time, weight);
    }

    cout << optimizer.findMaximumCups() << endl;

    return 0;
}