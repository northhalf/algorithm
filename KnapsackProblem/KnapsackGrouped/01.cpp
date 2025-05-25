/* UTF-8 */
#include <algorithm>
#include <cctype>
#include <concepts>
#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <stack>
#include <utility>
#include <vector>
using ll = long long;
template <std::integral T>
T QuickRead();
template <std::integral T>
void QuickWrite(T num);

int main() {
    std::function qr = QuickRead<ll>;
    // 物品的总重量和数目
    ll total_weight = qr(), num_items = qr();
    // 记录每组的物品
    std::vector<std::vector<std::pair<ll, ll>>> items_each_group(101);
    for (int i = 0; i < num_items; i++) {
        // 物品的重量，利用价值，所属祖师
        ll weight = qr(), value = qr(), group = qr();
        items_each_group[group].emplace_back(weight, value);
    }
    std::vector<ll> dp(total_weight + 1);
    // 对组的01背包
    // 枚举组数
    for (ll i = 1; i <= 100; i++) {
        // 枚举重量
        for (ll j = total_weight; j >= 1; j--) {
            // 枚举当前组内物品
            for (size_t k = 0; k < items_each_group[i].size(); k++) {
                // 如果当前物品质量大于枚举容量则跳过
                if (items_each_group[i][k].first > j) {
                    continue;
                }

                dp[j] = std::max(
                    dp[j - items_each_group[i][k].first] +
                        items_each_group[i][k].second,
                    dp[j]
                );
            }
        }
    }
    QuickWrite(dp[total_weight]);
    return 0;
}

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