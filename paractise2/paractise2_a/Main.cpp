//
// Created by laurie on 25-3-20.
//
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph {
    int V;  // 顶点数
    vector<vector<int>> adj;  // 邻接表

public:
    Graph(int v) : V(v), adj(v) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    void topologicalSort() {
        vector<int> inDegree(V, 0);

        // 计算所有节点的入度
        for (int u = 1; u < V; u++) {
            for (int v : adj[u]) {
                inDegree[v]++;
            }
        }

        //  使用小顶堆（priority_queue）保证字典序最小
        priority_queue<int, vector<int>, greater<int>> pq;
        for (int i = 1; i < V; i++) {
            if (inDegree[i] == 0) pq.push(i);
        }

        vector<int> topoOrder;
        while (!pq.empty()) {
            int u = pq.top();
            pq.pop();
            topoOrder.push_back(u);

            // 遍历 u 的邻居 v，移除 u → v 边
            for (int v : adj[u]) {
                if (--inDegree[v] == 0) {
                    pq.push(v);  // 保证优先选择字典序最小的节点
                }
            }
        }

        // 如果拓扑排序数量不等于顶点数，说明图中有环
        if (topoOrder.size() != V-1) {
            cout << "Graph has a cycle! No topological order possible." << endl;
            return;
        }

        // 输出字典序最小的拓扑排序
        for (int node : topoOrder) {
            cout << node << " ";
        }
        cout << endl;
    }
};

int main() {
    int V;
    int edge;
    cin >> V >> edge;
    Graph g(V+1);
    for(int i = 0; i < edge; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }
    g.topologicalSort();
    return 0;
}
