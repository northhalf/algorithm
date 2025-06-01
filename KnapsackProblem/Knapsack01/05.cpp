/* UTF-8 */
#include <algorithm>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

int main() {
    int num_of_items, total_money;  // 物品个数和总钱数
    std::cin >> num_of_items >> total_money;

    std::vector<std::pair<int, int>> items;  // 用来记录物品的花费和价值键对
    items.reserve(num_of_items + 1);  // 提前预留内存
    items.emplace_back(0, 0);         // 将[0]下标位置填充

    int min_money = std::numeric_limits<int>::max();  // 记录最小钱数
    // 接收数据，并获取最小钱数
    for (int i = 1; i <= num_of_items; i++) {
        int cost, importance;
        std::cin >> cost >> importance;
        min_money = std::min(min_money, cost);
        items.emplace_back(cost, importance);
    }
    // 记录每种价格的物品的重要度序列，因为价格只有四种，所以
    std::vector<std::vector<int>> importance_of_each_cost(
        4, std::vector<int>(101)
    );
    // 记录每种价格的物品个数
    std::vector<int> num_of_each_money(4);
    // 统计四种价格的物品个数，以及记录重要度序列
    for (int i = 1; i <= num_of_items; i++) {
        switch (items[i].first - min_money) {
            case 0:  // 根据物品价格和最小价格的关系放入重要度序列
                importance_of_each_cost[0][++num_of_each_money[0]] =
                    items[i].second;
                break;
            case 1:
                importance_of_each_cost[1][++num_of_each_money[1]] =
                    items[i].second;
                break;
            case 2:
                importance_of_each_cost[2][++num_of_each_money[2]] =
                    items[i].second;
                break;
            case 3:
                importance_of_each_cost[3][++num_of_each_money[3]] =
                    items[i].second;
                break;
            default:
                break;
        }
    }
    // 将相同价格的价值序列按从大到小的顺序排列
    for (int i = 0; i < 4; i++) {
        std::sort(
            importance_of_each_cost[i].begin() + 1,
            importance_of_each_cost[i].begin() + num_of_each_money[i] + 1,
            std::greater<int>{}
        );
    }

    // 记录前缀和的数组
    std::vector<std::vector<int>> sum_of_prefix(4, std::vector<int>(100));
    // 计算前缀和方便后面直接获取前n个重要度相加的值
    for (int i = 0; i < 4; i++) {
        for (int j = 1; j <= num_of_each_money[i]; j++) {
            sum_of_prefix[i][j] =
                sum_of_prefix[i][j - 1] + importance_of_each_cost[i][j];
        }
    }

    int ans = 0;  // 记录获取的最大重要度
    // 三层循环依次枚举前三种价格的物品个数
    // (重要度序列已经按从大到小排序，在价格相同的情况下，优先挑选重要度大的)
    for (int i = 0; i <= num_of_each_money[0]; i++) {
        for (int j = 0; j <= num_of_each_money[1]; j++) {
            for (int k = 0; k <= num_of_each_money[2]; k++) {
                // 计算此时取出前三种价格的物品，的总金额
                int sum =
                    i * min_money + j * (min_money + 1) + k * (min_money + 2);
                // 如果总金额大于预算，则停止枚举第三种价格的物品
                if (sum > total_money) break;

                // 计算此时第四种价格的物品数量，为 剩余金额/该物品价格
                int l = (total_money - sum) / (min_money + 3);
                // 判断这种取法是否更新最大价值
                ans = std::max(
                    ans, sum_of_prefix[0][i] + sum_of_prefix[1][j] +
                             sum_of_prefix[2][k] + sum_of_prefix[3][l]
                );
            }
        }
    }
    std::cout << ans << std::endl;
    return 0;
}