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
    // 总钱数和物品总数
    ll total_money = qr(), total_num_items = qr();
    // item[i][j]表示编号为i的大物品的第j个附属小物品
    // item[i][0]表示编号为i的大物品的 价格和重要度
    std::vector<std::vector<std::pair<ll, ll>>> items(
        total_num_items + 1, std::vector<std::pair<ll, ll>>(3, {0, 0})
    );
    for (ll i = 1; i <= total_num_items; i++) {
        // 价格，重要度和对应主件
        ll cost = qr(), importance = qr(), main_item = qr();
        if (main_item == 0) {
            // 如果这个物品是主件
            items[i][0] = std::make_pair(cost, importance);
        } else {
            // 这个物品是附属物
            if (items[main_item][1].second == 0) {
                // 如果该主件还没有第一个附属物，那么这就是第一个
                items[main_item][1] = std::make_pair(cost, importance);
            } else {  // 否则这是第二个
                items[main_item][2] = std::make_pair(cost, importance);
            }
        }
    }
    std::vector<ll> dp(total_money + 1);
    // 枚举物品编号
    for (ll i = 1; i <= total_num_items; i++) {
        // 如果该编号是附属物则跳过
        if (items[i][0].second == 0) {
            continue;
        }

        // 枚举钱数
        for (ll j = total_money; j > 0; j--) {
            // 如果主件都买不起那么就停止枚举钱数
            if (j < items[i][0].first) {
                break;
            }
            // 分别计算不同购买情况的花费和价值
            // 只购买主件
            ll only_main = items[i][0].first;
            ll only_main_value = items[i][0].first * items[i][0].second;
            // 购买主件+第一个附属物
            ll main_first_aux = items[i][0].first + items[i][1].first;
            ll main_first_aux_value =
                only_main_value + items[i][1].first * items[i][1].second;
            // 购买主件+第二个附属物
            ll main_second_aux = items[i][0].first + items[i][2].first;
            ll main_second_aux_value =
                only_main_value + items[i][2].first * items[i][2].second;
            // 购买主件+两个附属物
            ll main_two_aux =
                items[i][0].first + items[i][1].first + items[i][2].first;
            ll main_two_aux_value =
                main_first_aux_value + main_second_aux_value - only_main_value;

            // 四种情况分别判断
            // 只买主件
            dp[j] = std::max(dp[j - only_main] + only_main_value, dp[j]);
            // 主件+第一个附属物
            if (j >= main_first_aux) {
                dp[j] = std::max(
                    dp[j - main_first_aux] + main_first_aux_value, dp[j]
                );
            }
            // 主件+第二个附属物
            if (j >= main_second_aux) {
                dp[j] = std::max(
                    dp[j - main_second_aux] + main_second_aux_value, dp[j]
                );
            }
            // 主件+两个附属物
            if (j >= main_two_aux) {
                dp[j] =
                    std::max(dp[j - main_two_aux] + main_two_aux_value, dp[j]);
            }
        }
    }
    QuickWrite(dp[total_money]);
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