//
// Created by purple on 25-2-20.
//
#include <iostream>
using namespace std;
int tileWays(int n) {

    if (n == 0) return 0;
    if (n == 1) return 1;
    int dp[n + 1];
    dp[0] = 1;
    dp[1] = 1;
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
}

int main() {
    int n;
    cout << "Enter the value of n: ";
    cin >> n;
    cout << "Number of ways to tile a 2*" << n << " rectangle: " << tileWays(n) << endl;
    return 0;
}


