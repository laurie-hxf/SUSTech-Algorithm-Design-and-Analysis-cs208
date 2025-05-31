//
// Created by laurie on 25-5-28.
//
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <climits>

using namespace std;

const int MAX_V = 1e4 + 5;

struct Edge {
    int to, rev;
    long long cap;
    Edge(int _to, long long _cap, int _rev) : to(_to), cap(_cap), rev(_rev) {}
};

vector<Edge> G[MAX_V];
int level[MAX_V];  // 节点层次
int iter[MAX_V];   // 当前弧指针，减少重复遍历

void add_edge(int from, int to, long long cap) {
    G[from].push_back(Edge(to, cap, (int)G[to].size()));
    G[to].push_back(Edge(from, 0, (int)G[from].size() - 1));
}

// BFS 建立分层图，level[v] = 源点到v的层数
void bfs(int s) {
    memset(level, -1, sizeof(level));
    queue<int> que;
    level[s] = 0;
    que.push(s);

    while (!que.empty()) {
        int v = que.front(); que.pop();
        for (auto &e : G[v]) {
            if (e.cap > 0 && level[e.to] < 0) {
                level[e.to] = level[v] + 1;
                que.push(e.to);
            }
        }
    }
}

// 在分层图中用DFS寻找增广路径
long long dfs(int v, int t, long long flow) {
    if (v == t) return flow;

    for (int &i = iter[v]; i < (int)G[v].size(); ++i) {
        Edge &e = G[v][i];
        if (e.cap > 0 && level[v] < level[e.to]) {
            long long d = dfs(e.to, t, min(flow, e.cap));
            if (d > 0) {
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

long long max_flow(int s, int t) {
    long long flow = 0;
    while (true) {
        bfs(s);
        if (level[t] < 0) return flow;  // 没有增广路径了
        memset(iter, 0, sizeof(iter));
        long long f;
        while ((f = dfs(s, t, LLONG_MAX)) > 0) {
            flow += f;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, s, t;
    cin >> n >> m >> s >> t;

    const long long INF = LLONG_MAX / 2;

    // 拆点：v_in = v, v_out = v + n
    for (int v = 1; v <= n; ++v) {
        if (v == s || v == t) continue; // s 和 t 不拆点
        add_edge(v, v + n, 1); // v_in -> v_out
    }

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;

        int from_u = (u == s || u == t) ? u : u + n;
        int to_v = (v == s || v == t) ? v : v;

        add_edge(from_u, to_v, INF);

        int from_v = (v == s || v == t) ? v : v + n;
        int to_u = (u == s || u == t) ? u : u;

        add_edge(from_v, to_u, INF);
    }
    long long ans = max_flow(s, t);
    cout << (ans==INF?0:ans) << endl;
    return 0;
}

