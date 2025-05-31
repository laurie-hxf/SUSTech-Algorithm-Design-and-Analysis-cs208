//
// Created by laurie on 25-5-20.
//
#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    const int INF = 1e9;
    int n,L;
    cin>>n>>L;
    int m1,x1,c1,m2,x2,c2;
    cin>>m1>>x1>>c1>>m2>>x2>>c2;
    unordered_set<int> valid_positions;  // 可落脚的点
    valid_positions.insert(0);
    for(int i=0;i<n;i++) {
        int x;
        cin>>x;
        valid_positions.insert(x);
    }
    valid_positions.insert(L);
    vector<vector<int> > dp(x1,vector<int>(x2+1,INF));
    dp[0][0]=0;
    int answer = INF;
    for(int i=0;i<x1;i++) {
        for(int j=0;j<x2;j++) {
            int pos = i*m1+j*m2;
            if (valid_positions.find(pos) == valid_positions.end()) {
                continue;
            }
            if (i > 0 && dp[i - 1][j] != INF) {
                dp[i][j] = min(dp[i][j], dp[i - 1][j] + c1);
            }
            if (j > 0 && dp[i][j - 1] != INF) {
                dp[i][j] = min(dp[i][j], dp[i][j - 1] + c2);
            }

            if (pos == L) {
                answer = min(answer, dp[i][j]);
            }
        }
    }

    if (answer == INF) cout << -1 << endl;
    else cout << answer << endl;
}