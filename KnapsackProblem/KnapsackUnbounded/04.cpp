#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

int main() {
    int n, h;  // 干草公司的数目和需要多少干草
    std::cin >> n >> h;
    std::vector<std::pair<int, int>> item;  // 记录干草包的价格和质量
    item.reserve(n);
    // 获取每个公司的干草包质量和价格
    for (int i = 0; i < n; i++) {
        int weight, cost;
        std::cin >> weight >> cost;
        item.emplace_back(cost, weight);
    }
    // dp数组，并确定容量最大值: 以第一个物品为基准，假设全部购买第一个物品
    // 看需要花费多少钱
    int capablity = (h / item[0].second + 1) * item[0].first;
    std::vector<int> dp(capablity);
    // 完全背包二重循环
    for (int i = 0; i < n; i++) {
        for (int j = item[i].first; j <= capablity; j++) {
            dp[j] = std::max(dp[j - item[i].first] + item[i].second, dp[j]);
        }
    }
    // 查询最少开销
    auto res = std::lower_bound(dp.begin(), dp.end(), h);
    std::cout << std::distance(dp.begin(), res) << std::endl;
    return 0;
}