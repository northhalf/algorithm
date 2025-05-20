/* UTF-8 */
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

int main() {
    int n, h;  // 干草公司的数目和需要多少干草
    std::cin >> n >> h;
    std::vector<std::pair<int, int>> item;  // 记录干草包的价格和质量
    item.reserve(n);
    int max_weight = 0;  // 记录最大质量
    // 获取每个公司的干草包质量和价格
    for (int i = 0; i < n; i++) {
        int weight, cost;
        std::cin >> weight >> cost;
        max_weight = std::max(max_weight, weight);
        item.emplace_back(cost, weight);
    }
    // dp数组，因为所有的价格都不大于5000,所以可设10000为无穷大
    std::vector<int> dp(h + max_weight + 1, 0x77777777);
    dp[0] = 0;  // 价格为0对应的最小质量为0
    // 完全背包的二重循环
    for (int i = 0; i < n; i++) {
        for (int j = item[i].second; j <= (h + max_weight); j++) {
            dp[j] = std::min(dp[j - item[i].second] + item[i].first, dp[j]);
        }
    }
    // 获取最小元素
    auto min_ele = std::min_element(dp.begin() + h, dp.end());
    std::cout << (*min_ele) << std::endl;
    return 0;
}