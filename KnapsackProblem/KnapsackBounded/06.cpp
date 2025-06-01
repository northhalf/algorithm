/* UTF-8 */
#include <algorithm>
#include <cctype>
#include <concepts>
#include <functional>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>
/**
 * @brief 快速读取输入的整数
 * @return 读取到的数字
 */
template <std::integral T>
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

    // 根据负数标记决定返回负号
    return minus ? (-res) : res;
}
/**
 * @brief 快速输出整数
 * @param num 需要输出的整数
 */
template <std::integral T>
void QuickWrite(T num) {
    // 栈来存储数字的各位字符，先进后出
    static unsigned char stack[20];
    char top = 0;
    // 原类型的无符号类型
    using unsigned_T = std::make_unsigned_t<T>;
    unsigned_T abs;  // 存储原类型的无符号转换结果

    // 如果数字为负数则输出负号和符号反转
    if (num < 0) {
        std::putchar('-');
        // 将原来数字转化为绝对值
        if (num == std::numeric_limits<T>::min()) {
            // 如果这个数字是原来有符号数字最小值，那么其绝对值为最大值+1
            abs = static_cast<unsigned_T>(std::numeric_limits<T>::max()) + 1;
        } else {
            abs = static_cast<unsigned_T>(-num);
        }
    } else {  // 原来数字为正数的话直接转化为绝对值
        abs = static_cast<unsigned_T>(num);
    }

    // 往栈内放入数字字符
    do {
        stack[static_cast<size_t>(top++)] =
            static_cast<unsigned char>(abs % 10) + '0';
        abs /= 10;
    } while (abs != 0);
    // 不断弹出字符直到顶部索引为0
    while (top > 0) {
        std::putchar(stack[static_cast<int>(--top)]);
    }
    // 换行并刷新缓冲区
    std::putchar('\n');
}
int main() {
    std::function qr = QuickRead<long long>;  // 快速读取long long类型

    long long n = qr(), m = qr(), C = qr();  // 普通物品数，奇货数，背包总容量
    std::vector<std::pair<long, long>> items{{0, 0}};  // 记录物品
    items.reserve(n * 1000);
    for (long long i = 0; i < n; i++) {
        long long weight = qr(), value = qr(),
                  num = qr();  // 物品的价值和重量，数目
        // 二进制拆分
        for (long long j = 1; j <= num; num -= j, j <<= 1) {
            items.emplace_back(weight * j, value * j);
        }
        if (num != 0) {
            items.emplace_back(weight * num, value * num);
        }
    }
    std::vector<long long> dp(C + 1);
    // 01背包
    for (size_t i = 1; i < items.size(); i++) {
        for (long long j = C; j >= items[i].first; j--) {
            dp[j] = std::max(dp[j - items[i].first] + items[i].second, dp[j]);
        }
    }
    std::vector<long long> value(C + 1);
    // 处理奇货
    for (long long i = 0; i < m; i++) {
        long long a = qr(), b = qr(), c = qr();
        // 计算对应容量的价值
        for (long long k = 0; k <= C; k++) {
            value[k] = (a * k + b) * k + c;
        }
        // 完全背包
        // 枚举背包容量
        for (long long j = C; j >= 0; j--) {
            // 枚举给予容量
            for (long long k = 0; k <= j; k++) {
                // 如果价值不大于0则跳过
                if (value[k] <= 0) {
                    continue;
                }
                if (long long total_value = dp[j - k] + value[k];
                    total_value > dp[j]) {
                    dp[j] = total_value;
                }
            }
        }
    }
    QuickWrite(dp[C]);
    return 0;
}