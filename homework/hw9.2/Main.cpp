//
// Created by laurie on 25-5-22.
//
#include<iostream>
#include<vector>
using namespace std;

int main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    long n,m;
    cin>>n>>m;
    vector<long> price(m,0);
    vector<long>  sugar_content(m,0);
    vector<long>  pre(n+1,-1);
    vector<long>  dp(n+1,0);
    for (int i = 0; i < m; i++) {
        cin>>price[i]>>sugar_content[i];
    }
    for (int i = 0; i < m; i++) {
        for (int j = price[i]; j <= n; j++) {
            if (dp[j-price[i]] + sugar_content[i] > dp[j]) {
                dp[j] = dp[j - price[i]] + sugar_content[i];
                pre[j] = i;
            }
        }
    }
    cout<<dp[n]<<endl;

    vector<long> count(m,0);
    long j = n;
    while (j > 0 && pre[j] != -1) {
        long i = pre[j];
        count[i]++;
        j -= price[i];
    }

    // 输出购买数量
    for (int i = 0; i < m; i++) {
        cout << count[i] << endl;
    }

    return 0;
}
