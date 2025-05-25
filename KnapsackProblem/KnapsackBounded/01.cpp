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
    // 获取看花总时间
    ll h = qr(), m = qr();  // 记录时间的小时和分钟
    // std::scanf(" %d:%d", &h, &m);
    ll start = h * 60 + m;  // 开始时间
    h = qr(), m = qr();
    ll end = h * 60 + m;        // 结束时间
    ll duration = end - start;  // 看花结束时间

    ll n = qr();  // 记录多少樱花树

    std::vector<ll> dp(duration + 1);
    for (ll i = 0; i < n; i++) {
        ll t = qr(), c = qr(), p = qr();  // 时间，美学值，次数
        if (p == 0) {                     // 如果是完全背包
            for (ll j = t; j <= duration; j++) {
                dp[j] = std::max(dp[j - t] + c, dp[j]);
            }
            continue;
        }
        /* 单调队列优化 */
        std::deque<ll> que;
        std::vector<ll> c_dp(dp);
        // 枚举对时间的余数
        for (ll j = 0; j < t; j++) {
            // 先清空之前的队列
            que.clear();
            // 在当前余数基础上，枚举可能的时间
            for (ll k = j; k <= duration; k += t) {
                // 将下标不在窗口范围内的值弹出
                while (not que.empty() and que.front() < k - p * t) {
                    que.pop_front();
                }
                // 当队列存在元素的时候，用队首元素更新dp数组
                if (not que.empty()) {
                    // 原来的值+选择的观看次数加上的美学值
                    dp[k] = std::max(
                        c_dp[que.front()] + (k - que.front()) / t * c, dp[k]
                    );
                }
                /*
                 当前美学值与队尾元素比较，如果比队尾好，则前移
                 比较基准值，即是需要将因次数导致的美学值加成减去
                 因为比如2 4 6序列，对应美学值数组为3 4 4，则此时的基准值
                 (若该樱花树美学值为2)为：3 2 0。
                 对于6来说，选2+美学值*次数 > 4+美学值*次数
                 因为不能光考虑显性的美学值，还要考虑次数带来的加成
                */
                while (not que.empty() and
                       c_dp[que.back()] - (que.back() - j) / t * c <=
                           c_dp[k] - (k - j) / t * c) {
                    que.pop_back();
                }
                // 将当前下标入队
                que.emplace_back(k);
            }
        }
    }
    QuickWrite(dp[duration]);
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