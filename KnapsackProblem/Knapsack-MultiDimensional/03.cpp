/* UTF-8 */
#include <algorithm>
#include <cctype>
#include <concepts>
#include <cstring>
#include <functional>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>
using ll = long long;
template <std::integral T>
T QuickRead();
template <std::integral T>
void QuickWrite(T num);

ll dp[41][41][41][41];

int main() {
    std::function qr = QuickRead<ll>;
    ll num_squares = qr(), num_cards = qr();  // 棋盘格子数和卡片数
    std::vector<ll> points_square;            // 记录格子的点数
    points_square.reserve(num_squares);
    // 记录格子的点数
    for (ll i = 0; i < num_squares; i++) {
        points_square.emplace_back(qr());
    }
    std::vector<ll> num_each_cards(5);  // 记录1,2,3,4的数量
    // 记录每类牌的数量
    for (int i = 0; i < num_cards; i++) {
        num_each_cards[qr()]++;
    }
    dp[0][0][0][0] = points_square[0];
    // 四重循环，枚举每类卡牌的个数
    for (ll i = 0; i <= num_each_cards[1]; i++) {
        for (ll j = 0; j <= num_each_cards[2]; j++) {
            for (ll k = 0; k <= num_each_cards[3]; k++) {
                for (ll h = 0; h <= num_each_cards[4]; h++) {
                    // 计算此时到达的格子数
                    ll squares = i + 2 * j + 3 * k + 4 * h;
                    // 四种情况，有四种转移可能
                    if (i != 0) {
                        dp[i][j][k][h] = std::max(
                            dp[i - 1][j][k][h] + points_square[squares],
                            dp[i][j][k][h]
                        );
                    }
                    if (j != 0) {
                        dp[i][j][k][h] = std::max(
                            dp[i][j - 1][k][h] + points_square[squares],
                            dp[i][j][k][h]
                        );
                    }
                    if (k != 0) {
                        dp[i][j][k][h] = std::max(
                            dp[i][j][k - 1][h] + points_square[squares],
                            dp[i][j][k][h]
                        );
                    }
                    if (h != 0) {
                        dp[i][j][k][h] = std::max(
                            dp[i][j][k][h - 1] + points_square[squares],
                            dp[i][j][k][h]
                        );
                    }
                }
            }
        }
    }
    QuickWrite(dp[num_each_cards[1]][num_each_cards[2]][num_each_cards[3]]
                 [num_each_cards[4]]);
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