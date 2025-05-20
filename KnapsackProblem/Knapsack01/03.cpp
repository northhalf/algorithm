/* UTF-8 */
#include <algorithm>
#include <iostream>
int dp[100001];
int main() {
    int n, m;  // 菜的种类和可用钱数
    std::cin >> n >> m;
    dp[0] = 1;  // 钱数为0的取法只有1种
    // 依次枚举菜
    for (int i = 1; i <= n; i++) {
        int cost;  // 记录这道菜的花费
        std::cin >> cost;
        for (int j = m; j >= cost; j--) {
            dp[j] += dp[j - cost];
        }
    }
    std::cout << dp[m] << std::endl;
    return 0;
}
