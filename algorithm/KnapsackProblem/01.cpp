#include <algorithm>
#include <iostream>
int dp[10001][10001];
int main() {
    int t, m;
    std::cin >> t >> m;
    for (int i = 1; i <= m; i++) {
        int a, b;
        std::cin >> a >> b;
        // 枚举背包容量
        for (int j = 0; j <= t; j++) {
            if (j >= a)
                dp[i][j] = std::max(dp[i - 1][j - a] + b, dp[i - 1][j]);
            else  // 如果容量不够装下这个物体，则放置之前获得的最大价值
                dp[i][j] = dp[i - 1][j];
        }
    }
    std::cout << dp[m][t] << std::endl;
    return 0;
}
