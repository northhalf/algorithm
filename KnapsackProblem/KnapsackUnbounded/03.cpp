/* UTF-8 */
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

int main() {
    int s, n, d;  // 最初总资产，年数和债券种类
    std::cin >> s >> n >> d;

    std::vector<std::pair<int, int>> bond;  // 存储债券
    bond.reserve(d);                        // 预留内存
    // 将总资产表示为 s*1000+temp 的形式
    int temp = s % 1000;
    s /= 1000;
    // 获取债券
    for (int i = 0; i < d; i++) {
        int invest, interest;  // 投资额和年利息
        std::cin >> invest >> interest;
        bond.emplace_back(invest / 1000, interest);
    }

    std::vector<int> dp(46 * s);  // dp数组用于完全背包，最大利率不超过46倍
    // 枚举年数
    for (int i = 0; i < n; i++) {
        // 完全背包的二重循环
        for (int j = 0; j < d; j++) {                   // 枚举物品
            for (int k = bond[j].first; k <= s; k++) {  // 枚举容量
                dp[k] = std::max(dp[k - bond[j].first] + bond[j].second, dp[k]);
            }
        }
        // 一年结束，更新背包容量
        temp += dp[s];     // 获得的利息加入余量中
        s += temp / 1000;  // 判断是否有效s*1000+temp的s可以更新
        temp %= 1000;      // temp不超过1000
    }

    std::cout << (s * 1000 + temp) << std::endl;
    return 0;
}