//
// Created by laurie on 25-5-28.
//
#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
using namespace std;

const int MAX_V = 1e4 + 5;

struct Edge {
    long to, cap, rev;
    Edge(long _to, long _cap, long _rev): to(_to), cap(_cap), rev(_rev) {}
};

vector<Edge> G[MAX_V];
bool used[MAX_V];

void add_edge(long from, long to, long cap) {
    G[from].push_back(Edge(to, cap, G[to].size()));
    G[to].push_back(Edge(from, 0, G[from].size() - 1));
}

long dfs(long c, long t, long f) {
    if (c == t) {
        return f;
    }
    used[c] = true;
    for (long i = 0; i < long(G[c].size()); ++ i) {
        Edge &e = G[c][i];
        if (!used[e.to] && e.cap > 0) {
            long d = dfs(e.to, t, min(f, e.cap));
            if (d > 0) {
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

int main() {
    long n, m,s,t;
    cin >> n >> m >> s >> t;
    for (long i = 0; i < m; ++ i) {
        long a, b,c;
        cin >> a >> b >> c;
        add_edge(a,b,c);
    }
    long flow = 0;
    for (;;) {
        memset(used, 0, sizeof(used));
        long f = dfs(s, t, INT_MAX);
        if (f == 0) {
            cout << flow << endl; // 23 验证通过
            return 0;
        }
        flow += f;
    }
}