#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

struct Edge {
    long long u, v;
    long long w;
    Edge(long long _u, long long _v, long long _w): u(_u), v(_v), w(_w) {}
};

struct Node {
    long long id;
    long long dist = LLONG_MAX;
    bool visited = false;
    bool inHeap = false;
    vector<Edge> outEdges; // 正向边
    vector<Edge> inEdges;  // 反向边
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->dist > b->dist;
    }
};

int main() {
    long long n, m;
    cin >> n >> m;
    vector<Node*> nodes(n + 1);
    for (long long i = 1; i <= n; ++i) {
        nodes[i] = new Node();
        nodes[i]->id = i;
    }

    for (long long i = 0; i < m; ++i) {
        long long u, v;
        long long w;
        cin >> u >> v >> w;
        nodes[u]->outEdges.emplace_back(u, v, w);
        nodes[v]->inEdges.emplace_back(v, u, w);
    }

    // Dijkstra
    priority_queue<Node*, vector<Node*>, Compare> pq;
    nodes[1]->dist = 0;
    pq.push(nodes[1]);
    nodes[1]->inHeap = true;

    while (!pq.empty()) {
        Node* curr = pq.top(); pq.pop();
        curr->visited = true;

        for (const Edge& e : curr->outEdges) {
            Node* next = nodes[e.v];
            if (curr->dist + e.w < next->dist) {
                next->dist = curr->dist + e.w;
                if (next->inHeap) {
                    // 重进堆（C++ priority_queue 不支持 decrease key，所以简单 push）
                    pq.push(next);
                } else {
                    pq.push(next);
                    next->inHeap = true;
                }
            }
        }
    }

    // 回溯找最小合法入边
    long long total = 0;
    for (long long i = 2; i <= n; ++i) {
        long long minCost = LLONG_MAX;
        for (const Edge& e : nodes[i]->inEdges) {
            if (nodes[e.v]->dist + e.w == nodes[i]->dist) {
                minCost = min(minCost, e.w);
            }
        }

//        total += minCost!=LLONG_MAX?minCost:0;
        total += minCost;
    }

    cout << total << endl;
    return 0;
}
