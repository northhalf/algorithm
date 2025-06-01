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
    // 货币种类和预期价值
    ll sorts_currency = qr(), aid_value = qr();
    // 存储货币金额种类
    std::vector<ll> currency(sorts_currency + 1);
    // 存储二进制拆分结果
    std::vector<std::pair<ll, ll>> binary_currency;
    binary_currency.reserve(sorts_currency * 100);
    // 记录最大金额
    ll max_currency = 0;

    // 记录货币金额
    for (ll i = 1; i <= sorts_currency; i++) {
        currency[i] = qr();
        max_currency = std::max(max_currency, currency[i]);
    }
    // 记录各货币的张数，并进行二进制拆分
    for (ll i = 1; i <= sorts_currency; i++) {
        ll num = qr();
        for (ll j = 1; j <= num; num -= j, j <<= 1) {
            binary_currency.emplace_back(j, j * currency[i]);
        }
        if (num != 0) {
            binary_currency.emplace_back(num, num * currency[i]);
        }
    }

    constexpr ll max_ll = 0x3f3f3f3f3f3f3f3f;  // 设定一个long long较大值
    // 最大上届为T+max_V^2
    ll upper_bound = aid_value + max_currency * max_currency;
    // 两个dp数组分别记录John和店主付出不同金额的最小张数
    std::vector<ll> dp1(upper_bound + 1, max_ll), dp2(upper_bound + 1, max_ll);
    dp1[0] = dp2[0] = 0;

    // 对Johb使用多次01背包
    // 枚举物品
    for (size_t i = 0; i < binary_currency.size(); i++) {
        // 枚举使出钱数
        for (ll j = upper_bound; j >= binary_currency[i].second; j--) {
            dp1[j] = std::min(
                dp1[j - binary_currency[i].second] + binary_currency[i].first,
                dp1[j]
            );
        }
    }
    // 对店主使用完全背包
    // 枚举物品
    for (ll i = 0; i < sorts_currency; i++) {
        for (ll j = currency[i]; j <= upper_bound; j++) {
            dp2[j] = std::min(dp2[j - currency[i]] + 1, dp2[j]);
        }
    }

    // 查找最小组合
    ll ans = max_ll;
    for (ll i = aid_value; i <= upper_bound; i++) {
        ans = std::min(ans, dp1[i] + dp2[i - aid_value]);
    }
    // 根据ans值是否有变化判断是否存在解
    (ans == max_ll) ? (QuickWrite(-1)) : (QuickWrite(ans));
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