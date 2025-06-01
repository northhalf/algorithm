/* UTF-8 */
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    int m, n;
    std::cin >> m >> n;
    std::vector<int> dp(m + 1);
    // 枚举物品
    for (int i = 1; i <= n; i++) {
        int value, weight;
        std::cin >> value >> weight;
        // 枚举容量
        for (int j = weight; j <= m; j++) {
            dp[j] = std::max(dp[j - weight] + value, dp[j]);
        }
    }
    std::cout << dp[m] << std::endl;
    return 0;
}