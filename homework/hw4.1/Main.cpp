//
// Created by laurie on 25-4-16.
//
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <climits>

using namespace std;

typedef pair<int, int> PII;
const int INF = INT_MAX;

int n, m;

// Dijkstra 算法，从 start 点出发
vector<int> dijkstra(int start, const vector<vector<PII>>& graph) {
    vector<int> dist(n + 1, INF);
    priority_queue<PII, vector<PII>, greater<PII>> pq;
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        pair<int, int> p = pq.top();
        auto [d, u] = pq.top(); pq.pop();

        if (d > dist[u]) continue;

        for (auto [v, w] : graph[u]) {
            if (dist[v] > d + w) {
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

int main() {
    cin >> n >> m;
    vector<vector<PII>> graph(n + 1);
    vector<tuple<int, int, int>> edges;

    // 建图
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
        edges.emplace_back(u, v, w);
    }

    // 预处理最短路径
    vector<int> distFrom1 = dijkstra(1, graph);
    vector<int> distToN   = dijkstra(n, graph);

    // 前 n 天：路径必须经过点 i
    for (int i = 1; i <= n; ++i) {
        if (distFrom1[i] == INF || distToN[i] == INF)
            cout << -1 << endl;
        else
            cout << distFrom1[i] + distToN[i] << endl;
    }

    // 后 m 天：路径必须经过边 j (u, v)
    for (int j = 0; j < m; ++j) {
        auto [u, v, w] = edges[j];
        int option1 = (distFrom1[u] != INF && distToN[v] != INF) ? distFrom1[u] + w + distToN[v] : INF;
        int option2 = (distFrom1[v] != INF && distToN[u] != INF) ? distFrom1[v] + w + distToN[u] : INF;
        int res = min(option1, option2);
        cout << (res == INF ? -1 : res) << endl;
    }

    return 0;
}
