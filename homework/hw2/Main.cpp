//
// Created by laurie on 25-3-21.
//
#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

bool is_block(vector<bool>& block,int i) {
    return block[i];
}

int main() {
    int n;
    int m;
    cin >> n >> m;
    int a;
    int b;
    cin >> a >> b;
    vector<int> graph[n+1];
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    vector<bool> visited(n+1, false); // 访问标记数组
    vector<bool> block(n+1, false); // 创建一个大小为 n+1 的 vector<bool>，初始值为 false
    set<int> a_result;
    set<int> b_result;


    block[b] = true;
    queue<int> q;
    q.push(a);
    visited[a] = true;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        // 遍历 node 的所有邻接点
        for (int neighbor : graph[node]) {
            if (!visited[neighbor]&&(!block[neighbor])) {
                a_result.insert(neighbor);
                q.push(neighbor);
                visited[neighbor] = true; // 标记已访问
            }
        }
    }


    for(int i = 0; i < n+1; i++) {
        visited[i] = false;
    }
    block[b] = false;
    block[a] = true;
    q.push(b);
    visited[b] = true;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        // 遍历 node 的所有邻接点
        for (int neighbor : graph[node]) {
            if (!visited[neighbor]&&(!block[neighbor])) {
                b_result.insert(neighbor);
                q.push(neighbor);
                visited[neighbor] = true; // 标记已访问
            }
        }
    }
    set<int> intersection;
    for (int num : a_result) {
        if (b_result.count(num)) { // 如果 s2 中包含 num
            intersection.insert(num);
        }
    }
    for(int num : intersection) {
        a_result.erase(num);
        b_result.erase(num);
    }

    long long ans = a_result.size()*b_result.size();
    cout << ans << endl;

}
