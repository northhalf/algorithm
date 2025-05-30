/* UTF-8 */
#include <algorithm>
#include <cctype>
#include <concepts>
#include <cstring>
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
    ll num_day = qr();       // 天数
    ll num_souvenir = qr();  // 纪念品的数目
    ll num_coins = qr();     // 金币数目
    // 记录不同花费赚取的钱数
    std::vector<ll> dp(10001);
    // 记录不同天的物品价格
    std::vector<std::vector<ll>> price(
        num_day + 2, std::vector<ll>(num_souvenir + 2, 0)
    );
    // 枚举天数
    for (ll i = 1; i <= num_day; i++) {
        // 枚举第几个纪念品
        for (ll j = 1; j <= num_souvenir; j++) {
            // 获取这个纪念品的价格
            price[i][j] = qr();
        }
    }
    // 枚举天数
    for (ll i = 1; i <= num_day; i++) {
        std::ranges::for_each(dp, [](ll& x) { x = 0; });
        // 枚举第几个物品
        for (ll j = 1; j <= num_souvenir; j++) {
            // 枚举花多少钱，完全背包
            for (ll k = price[i][j]; k <= num_coins; k++) {
                dp[k] = std::max(
                    dp[k], dp[k - price[i][j]] + price[i + 1][j] - price[i][j]
                );
            }
        }
        // 将这天赚取的最大钱数加到总钱数上
        num_coins += dp[num_coins];
    }
    QuickWrite(num_coins);
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
