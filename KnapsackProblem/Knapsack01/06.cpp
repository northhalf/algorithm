/* UTF-8 */
#include <algorithm>
#include <cctype>
#include <concepts>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using ll = long long;
template <std::integral T>
T QuickRead();
template <std::integral T>
void QuickWrite(T num);

int main() {
    std::function qr = QuickRead<ll>;
    ll num_items = qr();         // 物品的数量
    ll capacity = qr();          // 背包的容量
    std::vector<ll> weights{0};  // 物品的重量
    weights.reserve(capacity + 1);
    // 记录物品的重量
    for (ll i = 1; i <= num_items; i++) {
        weights.emplace_back(qr());
    }
    std::vector<ll> dp(capacity + 1, 0);
    dp[0] = 1;
    // 先记录不同容量的最大选择种类可能
    // 枚举物品
    for (ll i = 1; i <= num_items; i++) {
        // 枚举容量
        for (ll j = capacity; j >= weights[i]; j--) {
            dp[j] = (dp[j] + dp[j - weights[i]]) % 10;
        }
    }
    // 将不选某个物品的种类减去
    std::vector<ll> res(capacity + 1, 0);
    res[0] = 1;
    // 枚举失去的物品
    for (ll i = 1; i <= num_items; i++) {
        // 枚举背包的容量
        for (ll j = 1; j <= capacity; j++) {
            // 如果物品比这个容量还大，那么失去它对这个容量的背包选法没有影响
            if (weights[i] > j) {
                res[j] = dp[j];
            } else {  // 容量可以装下这个物品，需要将因其产生的选择方法减去
                res[j] = (dp[j] - res[j - weights[i]] + 10) % 10;
            }
            QuickWrite(res[j]);
        }
        std::putchar('\n');
    }
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
}
