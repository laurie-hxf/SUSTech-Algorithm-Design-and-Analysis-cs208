//
// Created by laurie on 25-5-24.
//
#include <iostream>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n,m;
    cin>>n>>m;
    vector<int> dp(n+1,-1);
    dp[0]=0;
    for (int i=0;i<m;i++) {
        int op;
        cin>>op;
        if (op==0) {
            int c,v;
            cin>>c>>v;
            for (int j=c;j<=n;j++) {
                if (dp[j-c]!=-1) {
                    dp[j] = max(dp[j],dp[j-c]+v);
                }
            }
        }else if (op==1) {
            int c,v;
            cin>>c>>v;
            for (int j=n;j>=c;j--) {
                if (dp[j-c]!=-1) {
                    dp[j] = max(dp[j],dp[j-c]+v);
                }
            }
        }else if (op==2) {
            int x,c,v;
            cin>>x>>c>>v;
            for (int k = 1; x > 0; k <<= 1) {
                int use = min(k, x);
                int cost = use * c;
                int val = use * v;
                for (int j = n; j >= cost; --j) {
                    if (dp[j - cost] != -1) {
                        dp[j] = max(dp[j], dp[j - cost] + val);
                    }
                }
                x -= use;
            }
        }
    }
    cout << max(0, dp[n]) << '\n';
}
