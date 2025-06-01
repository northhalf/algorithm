/* UTF-8 */
#include <cctype>
#include <iostream>
#include <type_traits>
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
int main() {
    int n = QuickRead<int>();                 // n种花
    int m = QuickRead<int>();                 // 共m盆
    int mod_num = static_cast<int>(1e6 + 7);  // 取模数字

    std::vector<int> dp(m + 1);       // 记录m盆的组合数量
    std::vector<int> pre_sum(m + 1);  // 前缀和用于优化
    pre_sum[0] = dp[0] = 1;
    // 枚举物品
    for (int i = 1; i <= n; i++) {
        int a = QuickRead<int>();  // 读取第i种有几个
        // 枚举盆的总数
        for (int j = m; j >= 1; j--) {
            // 计算前缀和
            for (int k = 1; k <= m; k++) {
                pre_sum[k] = (pre_sum[k - 1] + dp[k]) % mod_num;
            }
            // 计算最大取多少盆，盆数不超过当前种类的花的盆数和枚举的盆的总数
            int upper = std::min(a, j);

            // 如果取的盆数和当前枚举的盆的总数相同
            // 那么加上[0,j-1]区间的种类和
            if (j == upper) {
                dp[j] = (dp[j] + pre_sum[j - 1]) % mod_num;
                continue;
            }

            // 加上[j-1,j-upper]区间的组合种类和
            dp[j] =
                (dp[j] + pre_sum[j - 1] - pre_sum[j - upper - 1] + mod_num) %
                mod_num;
        }
    }
    QuickWrite(dp[m]);
    return 0;
}