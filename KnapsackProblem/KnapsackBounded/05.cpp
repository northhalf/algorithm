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
    std::function<int()> qr = QuickRead<int>;  // 快速读取int类型

    int num_kinds = qr();                            // 宝物的总数
    int max_weights = qr();                          // 采集车的最大载重
    std::vector<std::pair<int, int>> items{{0, 0}};  // 记录物品
    items.reserve(num_kinds * 1000);
    // 枚举宝物种类
    for (int i = 0; i < num_kinds; i++) {
        // 价值，重量和数目
        int value = qr(), weight = qr(), num = qr();
        // 二进制拆分
        for (int j = 1; j <= num; num -= j, j <<= 1) {
            items.emplace_back(weight * j, value * j);
        }
        if (num != 0) {
            items.emplace_back(weight * num, value * num);
        }
    }
    std::vector<int> dp(max_weights + 1);
    // 当作多个01背包看待
    // 枚举物品
    for (size_t i = 1; i < items.size(); i++) {
        for (int j = max_weights; j >= items[i].first; j--) {
            dp[j] = std::max(dp[j - items[i].first] + items[i].second, dp[j]);
        }
    }
    QuickWrite(dp[max_weights]);
    return 0;
}