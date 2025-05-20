/* UTF-8 */
#include <algorithm>
#include <iostream>
int dp[100001];
int main() {
    int capability, num_of_item;  // 记录箱子的容量和物品的数量
    std::cin >> capability >> num_of_item;
    // 枚举物品
    for (int i = 1; i <= num_of_item; i++) {
        // 记录这个物品的信息
        int volume;
        std::cin >> volume;
        // 枚举容量
        for (int j = capability; j >= volume; j--) {
            dp[j] = std::max(dp[j - volume] + volume, dp[j]);
        }
    }
    std::cout << capability - dp[capability] << std::endl;
    return 0;
}