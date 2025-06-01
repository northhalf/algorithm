/* UTF-8 */
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    int t, m;  // 箱子容量和物体种类
    std::cin >> t >> m;
    std::vector<long long> dp(t + 1);
    // 枚举物品
    for (int i = 1; i <= m; i++) {
        int weight, value;  // 物品的重量和价值
        std::cin >> weight >> value;
        for (int j = weight; j <= t; j++) {
            dp[j] = std::max(dp[j - weight] + value, dp[j]);
        }
    }
    std::cout << dp[t] << std::endl;
    return 0;
}