//
// Created by laurie on 25-4-17.
//
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 100005;
vector<int> tree[MAXN];
int val[MAXN];
bool visited[MAXN];
int maxSum = INT32_MIN;

int dfs(int node) {
    visited[node] = true;
    vector<int> childGains;

    for (int neighbor : tree[node]) {
        if (!visited[neighbor]) {
            int gain = dfs(neighbor);
            childGains.push_back(gain);
        }
    }


    vector<int> validGains;
    for (int g : childGains) {
        if (g > 0) validGains.push_back(g);
    }

    sort(validGains.rbegin(), validGains.rend());

    int currentMax = val[node];
    if (validGains.size() >= 2) {
        currentMax += validGains[0] + validGains[1];
    } else if (validGains.size() == 1) {
        currentMax += validGains[0];
    }

    maxSum = max(maxSum, currentMax);


    int returnGain = val[node];
    if (!validGains.empty()) returnGain += validGains[0];
    return max(returnGain, 0);  // 如果负数，就不返回
}

int main() {
    int n;
    cin >> n;


    for (int i = 0; i < n; ++i) {
        cin >> val[i];
    }


    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    dfs(0);

    cout << maxSum << endl;
    return 0;
}
