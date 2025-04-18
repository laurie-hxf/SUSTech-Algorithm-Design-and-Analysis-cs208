//
// Created by laurie on 25-4-16.
//
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

const long long INF = LLONG_MAX;

struct Edge {
    long long u, v;
    long long w;
};

long long n, m;
vector<Edge> edges;
vector<vector<pair<long long, long long>>> graph; // 邻接表 graph[u] = {v, w}
vector<long long> dist;

void dijkstra(long long start) {
    dist.assign(n + 1, INF);
    dist[start] = 0;
    priority_queue<pair<long long, long long>, vector<pair<long long, long long> >, greater<pair<long long, long long> > > pq;
    pq.push(make_pair(0, start));

    while (!pq.empty()) {
        pair<long long, long long> cur = pq.top(); pq.pop();
        long long d = cur.first, u = cur.second;
        if (d > dist[u]) continue;

        for (long long i = 0; i < graph[u].size(); ++i) {
            long long v = graph[u][i].first;
            long long w = graph[u][i].second;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
}

// struct DSU {
//     vector<long long> fa;
//     DSU(long long n) {
//         fa.resize(n + 1);
//         for (long long i = 0; i <= n; ++i) {
//             fa[i] = i;
//         }
//     }
//
//     long long find(long long x) {
//         if (fa[x] != x)
//             fa[x] = find(fa[x]);
//         return fa[x];
//     }
//
//     bool unite(long long x, long long y) {
//         long long fx = find(x), fy = find(y);
//         if (fx == fy) return false;
//         fa[fx] = fy;
//         return true;
//     }
// };

int main() {
    cin >> n >> m;
    graph.resize(n + 1);
    vector<vector<Edge>> in_edge(n+1);
    for (long long i = 0; i < m; ++i) {
        long long u, v;
        long long w;
        cin >> u >> v >> w;
        graph[u].push_back(make_pair(v, w));
        Edge e = {u, v, w};
        edges.push_back(e);
    }

    dijkstra(1);

    // vector<Edge> valid;
    for (long long i = 0; i < edges.size(); ++i) {
        long long u = edges[i].u;
        long long v = edges[i].v;
        long long  w = edges[i].w;
        if (dist[u] != INF && dist[u] + w == dist[v]) {
            // valid.push_back(edges[i]);
            in_edge[v].push_back(edges[i]);
        }
    }


    long long res = 0;
    // long long count = 0;
    for (long long i = 1; i <= n; ++i) {
        long long temp = INF;
        for (long long j = 0; j < in_edge[i].size(); ++j) {
            if (in_edge[i][j].w<temp) {
                temp = in_edge[i][j].w;
            }
        }
        res += (temp!=INF?temp:0);
    }


    cout << res << endl;
    return 0;
}
