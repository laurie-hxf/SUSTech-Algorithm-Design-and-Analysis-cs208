#include <iostream>
#include <vector>
using namespace std;

const int MOD = 99824353;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    dp[0][0] = 1;

    // 枚举每一把扇子
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (j < i - m || j > i + m) continue;
            for (int k = 0; k <= j; ++k) {
                dp[i][j] = (dp[i][j] + dp[i - 1][k]) % MOD;
            }
        }
    }

    int res = 0;
    for (int j = 0; j <= n; ++j) {
        res = (res + dp[n][j]) % MOD;
    }
    cout << res << endl;
    return 0;
}


