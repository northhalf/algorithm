/* UTF-8 */
#include <algorithm>
#include <cctype>
#include <iostream>
#include <type_traits>
#include <utility>
#include <vector>

/**
 * @brief 快速读取输入的整数
 */
template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
T QuickRead() {
    bool minus = false;  // 记录该数字是否为负数
    T res = 0;
    // 获取第一个字符
    unsigned char ch = std::getchar();
    // 直到读取到数字字符
    while (!isdigit(ch)) {
        // 如果字符为负号则标注负数
        if (ch == '-') minus = true;
        ch = std::getchar();
    }
    // 读取数字字符
    while (isdigit(ch)) {
        res = res * 10 + (ch - '0');  // 不断累加
        ch = std::getchar();
    }

    // 判断是否为负数
    if (minus)
        return -res;
    else
        return res;
}
/**
 * @brief 快速输出整数
 */
template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
void QuickWrite(T num) {
    static unsigned char stack[20];
    char top = 0;
    // 如果数字为负数则输出负号和符号反转
    if (num < 0) {
        std::putchar('-');
        num = -num;
    }
    do {
        stack[static_cast<int>(top++)] =
            static_cast<unsigned char>(num % 10) + '0';
        num /= 10;
    } while (num > 0);
    while (top > 0) {
        std::putchar(stack[static_cast<int>(--top)]);
    }
    std::putchar('\n');
}
using ull = unsigned long long;

int main() {
    int n = QuickRead<int>();                       // 英雄的数目
    ull m = QuickRead<ull>();                       // 预期的组合种类
    std::vector<std::pair<int, int>> items(n + 1);  // 英雄的皮肤数量和价格
    ull max_cost = 0;  // 记录如果皮肤全部买下需要多少钱
    // 记录皮肤数量
    for (int i = 1; i <= n; i++) {
        items[i].first = QuickRead<int>();
    }
    // 记录皮肤价格
    for (int i = 1; i <= n; i++) {
        items[i].second = QuickRead<int>();
        // 将这个英雄皮肤总价加入买下所有皮肤所需的价格
        max_cost += items[i].first * items[i].second;
    }

    std::vector<ull> dp(max_cost + 1);
    dp[0] = 1;  // 基准种类，可视为没花钱只有一种展示方式
    // 枚举英雄
    for (int i = 1; i <= n; i++) {
        // 枚举花费价格
        for (int j = max_cost; j >= items[i].second; j--) {
            // 枚举选取的数目
            for (int k = 1, cost = k * items[i].second;
                 k <= items[i].first && cost <= j;
                 k++, cost = k * items[i].second) {
                dp[j] = std::max(dp[j - cost] * k, dp[j]);
            }
        }
    }
    int index = 1;
    while (dp[index] < m) index++;
    QuickWrite(index);
    return 0;
}