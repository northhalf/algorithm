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

/**
 * @brief 记录管道信息的结构体
 */
struct Pipe {
    ll pos;                         // 位置
    ll lower_height, upper_height;  // 低和高位置
};

int main() {
    std::function qr = QuickRead<ll>;
    ll length_window = qr();  // 游戏界面的长度
    ll height_window = qr();  // 游戏界面的高度
    ll num_pipe = qr();       // 水管的数量
    // 玩家是否点击造成的高度变化
    std::vector<std::pair<ll, ll>> height_change;
    height_change.reserve(length_window);
    // 读取每个地方的高度变化情况
    for (ll i = 0; i < length_window; i++) {
        ll add_height = qr();    // 可增加的高度
        ll minus_height = qr();  // 可减小的高度
        height_change.emplace_back(add_height, minus_height);
    }
    std::deque<Pipe> pipes;  // 记录管道信息
    std::vector<bool> is_pipe(
        length_window + 1
    );  // 快速查找某些位置是否存在管道
    for (ll i = 0; i < num_pipe; i++) {
        ll pos = qr(), lower_height = qr(), upper_height = qr();
        pipes.emplace_back(pos, lower_height, upper_height);
        is_pipe[pipes.back().pos] = true;
    }
    std::ranges::sort(pipes, [](const Pipe &p1, const Pipe &p2) {
        return p1.pos < p2.pos;
    });
    // 两个dp数组记录处于不同位置的最小点击次数
    std::vector<ll> temp_dp(2 * height_window + 5);
    std::vector<ll> res_dp(2 * height_window + 5);
    // 枚举所处的位置
    for (ll i = 1; i <= length_window; i++) {
        // 先将结果dp数组初始化为较大值
        std::uninitialized_fill(
            res_dp.begin(), res_dp.begin() + height_window + 1,
            std::numeric_limits<int>::max()
        );
        // 先来一个完全背包，因为单位时间可以点击多次
        for (ll j = 1 + height_change[i - 1].first;
             j <= height_window + height_change[i - 1].first; j++) {
            res_dp[j] = std::min(
                res_dp[j - height_change[i - 1].first] + 1,
                temp_dp[j - height_change[i - 1].first] + 1
            );
        }
        // 高度超出窗口的当成同一种情况取其中最小值
        res_dp[height_window] = *std::min_element(
            res_dp.begin() + height_window,
            res_dp.begin() + height_change[i - 1].first + height_window + 1
        );
        // 01背包，判断是否下降抵达该高度所用的操作次数会更少
        for (ll j = 1; j <= height_window - height_change[i - 1].second; j++) {
            res_dp[j] =
                std::min(res_dp[j], temp_dp[j + height_change[i - 1].second]);
        }
        // 如果这个地方存在管道
        if (is_pipe[i]) {
            // 将管道的位置数值重新初始化
            std::uninitialized_fill(
                res_dp.begin(), res_dp.begin() + pipes.front().lower_height + 1,
                std::numeric_limits<int>::max()
            );
            std::uninitialized_fill(
                res_dp.begin() + pipes.front().upper_height,
                res_dp.begin() + height_window + 1,
                std::numeric_limits<int>::max()
            );
            // 查找其中最小值
            ll min_ctr = *std::min_element(
                res_dp.begin() + 1, res_dp.begin() + height_window + 1
            );
            // 如果值为初始值说明不可抵达
            if (min_ctr == std::numeric_limits<int>::max()) {
                QuickWrite(0);
                QuickWrite(num_pipe - pipes.size());
                return 0;
            }
            pipes.pop_front();
        }
        // 当i不为最后一个位置的时候，交换数组
        if (i != length_window) {
            res_dp.swap(temp_dp);
        }
    }
    // 成功抵达
    QuickWrite(1);
    // 统计最小次数
    auto min_ctr_it = std::ranges::min_element(
        res_dp.begin() + 1, res_dp.begin() + height_window + 1
    );
    QuickWrite(*min_ctr_it);
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
