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
    // 玩家人物，城堡数，士兵数
    ll num_people = qr(), num_castle = qr(), num_soldier = qr();
    // 记录每个城堡，每个玩家投入多少士兵
    std::vector<std::vector<ll>> soldier_each_castle(
        num_castle + 1, std::vector<ll>(num_people + 1)
    );
    // 记录玩家兵力信息
    // 枚举玩家
    for (ll i = 1; i <= num_people; i++) {
        // 枚举城堡
        for (ll j = 1; j <= num_castle; j++) {
            soldier_each_castle[j][i] = qr();
        }
    }
    // 将每座城堡，玩家投入的兵力进行排序
    // 并将兵力改为攻占所需兵力
    for (ll i = 1; i <= num_castle; i++) {
        std::sort(
            soldier_each_castle[i].begin() + 1,
            soldier_each_castle[i].begin() + num_people + 1
        );
        for (ll j = 1; j <= num_people; j++) {
            soldier_each_castle[i][j] = 2 * soldier_each_castle[i][j] + 1;
        }
    }
    std::vector<ll> dp(num_soldier + 1);
    // 分组背包
    // 枚举城堡
    for (ll i = 1; i <= num_castle; i++) {
        // 枚举士兵使用数
        for (ll j = num_soldier; j > 0; j--) {
            // 枚举攻下哪个人的这座城堡
            for (ll k = 1; k <= num_people; k++) {
                // 如果需要士兵数比使用士兵数多，则结束枚举
                if (soldier_each_castle[i][k] > j) {
                    break;
                }
                dp[j] =
                    std::max(dp[j - soldier_each_castle[i][k]] + k * i, dp[j]);
            }
        }
    }
    QuickWrite(dp[num_soldier]);
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