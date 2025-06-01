/* UTF-8 */
#include <algorithm>
#include <iostream>
int dp[100001];
int main() {
    int n, m;  // 总容量和物品个数
    std::cin >> n >> m;
    // 枚举物品
    for (int i = 1; i <= m; i++) {
        int weight, b;
        std::cin >> weight >> b;
        int value = weight * b;  // 物品价值
        // 枚举容量
        for (int j = n; j >= weight; j--) {
            dp[j] = std::max(dp[j - weight] + value, dp[j]);
        }
    }
    std::cout << dp[n] << std::endl;
    return 0;
}