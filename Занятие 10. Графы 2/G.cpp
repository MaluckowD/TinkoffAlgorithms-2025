#include <iostream>
#include <vector>
#include <set>
#include <climits>
#include <algorithm>

using namespace std;

const long long INF = LLONG_MAX;

class GraphProcessor {
private:
    int n, m;
    vector<vector<pair<int, long long>>> graph;
    int pointA, pointB, pointC;

    vector<long long> computeShortestPaths(int start) {
        vector<long long> distances(n, INF);
        distances[start] = 0;
        
        set<pair<long long, int>> priority_queue;
        priority_queue.insert({0, start});
        
        while (!priority_queue.empty()) {
            auto [current_dist, u] = *priority_queue.begin();
            priority_queue.erase(priority_queue.begin());
            
            for (auto [v, weight] : graph[u]) {
                if (distances[v] > current_dist + weight) {
                    if (priority_queue.count({distances[v], v})) {
                        priority_queue.erase({distances[v], v});
                    }
                    distances[v] = current_dist + weight;
                    priority_queue.insert({distances[v], v});
                }
            }
        }
        
        return distances;
    }

    long long calculateOptimalMeetingPoint(const vector<long long>& distA,
                                         const vector<long long>& distB,
                                         const vector<long long>& distC) {
        long long min_total = INF;
        
        for (int x = 0; x < n; x++) {
            if (distA[x] == INF || distB[x] == INF || distC[x] == INF) {
                continue;
            }
            
            long long min_dist = min({distA[x], distB[x], distC[x]});
            long long total;
            
            if (min_dist == distA[x]) {
                total = 2 * min_dist + distB[x] + distC[x];
            } else if (min_dist == distB[x]) {
                total = 2 * min_dist + distA[x] + distC[x];
            } else {
                total = 2 * min_dist + distA[x] + distB[x];
            }
            
            min_total = min(min_total, total);
        }
        
        return min_total;
    }

public:
    void readInput() {
        cin >> n >> m;
        graph.resize(n);
        
        for (int i = 0; i < m; i++) {
            int u, v;
            long long w;
            cin >> u >> v >> w;
            u--; v--;
            graph[u].emplace_back(v, w);
            graph[v].emplace_back(u, w);
        }
        
        cin >> pointA >> pointB >> pointC;
        pointA--; pointB--; pointC--;
    }
    
    long long findOptimalMeetingPoint() {
        auto distA = computeShortestPaths(pointA);
        auto distB = computeShortestPaths(pointB);
        auto distC = computeShortestPaths(pointC);
        
        long long result = calculateOptimalMeetingPoint(distA, distB, distC);
        return result == INF ? -1 : result;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    GraphProcessor processor;
    processor.readInput();
    cout << processor.findOptimalMeetingPoint() << endl;
    
    return 0;
}