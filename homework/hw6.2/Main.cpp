//
// Created by laurie on 25-5-3.
//
#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;


const int N = 100005; // 最大节点数
bool answer = false;
int n,k;
struct Edge {
    int to;
    int weight;
};

vector<Edge> tree[N];

void add_edge(int u, int v, int w) {
    tree[u].push_back({v, w});
}
// void getDistances(int u, int curr_dist, vector<int>& dists) {
//     dists.push_back(curr_dist);
//
//     for (auto& [v, w] : tree[u]) {
//         getDistances(v,  curr_dist + w, dists);
//     }
// }
//
//
// void calc(int u) {
//     set<int> flag;
//     set<int>seq;
//     for (auto& v : tree[u]) {
//         vector<int> dis;
//         getDistances(v.to,  v.weight, dis);
//
//         for (auto& j : dis) {
//             if (flag.find(k-j)!=flag.end()) {
//                 answer = true;
//                 break;
//             }
//             flag.insert(j);
//             seq.insert(j);
//         }
//     }
//
// }
//
// void divide(int u) {
//     calc(u);
//     for (Edge i : tree[u]) {
//         divide(i.to);
//     }
// }
//
// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(0);cout.tie(0);
//     cin>>n>>k;
//     for(int i=1;i<n;i++) {
//         int u,v,w;
//         cin>>u>>v>>w;
//         add_edge(u,v,w);
//     }
//     divide(1);
//     if(answer) {
//         cout<<"Yes"<<endl;
//     }
//     else {
//         cout<<"No"<<endl;
//     }
// }

int subtree_size[N];
bool visited[N];

void get_size(int u, int parent) {
    subtree_size[u] = 1;
    for (auto& e : tree[u]) {
        int v = e.to;
        if (v == parent || visited[v]) continue;
        get_size(v, u);
        subtree_size[u] += subtree_size[v];
    }
}

int find_centroid(int u, int parent, int total_size) {
    for (auto& e : tree[u]) {
        int v = e.to;
        if (v == parent || visited[v]) continue;
        if (subtree_size[v] > total_size / 2) return find_centroid(v, u, total_size);
    }
    return u;
}

void getDistances(int u, int parent, int dist, vector<int>& dists) {
    dists.push_back(dist);
    for (auto& [v, w] : tree[u]) {
        if (v == parent || visited[v]) continue;
        getDistances(v, u, dist + w, dists);
    }
}

void calc(int u) {
    unordered_set<int> flag;
    flag.insert(0);
    for (auto& e : tree[u]) {
        int v = e.to;
        if (visited[v]) continue;

        vector<int> dists;
        getDistances(v, u, e.weight, dists);


        for (int d : dists) {
            if (flag.count(k - d)) {
                answer = true;
                return;
            }
        }


        for (int d : dists) flag.insert(d);
    }
}

void divide(int u) {
    get_size(u, -1);
    int centroid = find_centroid(u, -1, subtree_size[u]);

    calc(centroid);
    visited[centroid] = true;

    for (auto& e : tree[centroid]) {
        int v = e.to;
        if (!visited[v]) divide(v);
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> k;
    for (int i = 1; i < n; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        add_edge(u, v, w);
        add_edge(v, u, w);
    }

    divide(1);
    cout << (answer ? "Yes" : "No") << '\n';
}




