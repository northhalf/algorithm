/* UTF-8 */
#include <algorithm>
#include <cctype>
#include <chrono>
#include <concepts>
#include <deque>
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
 * @struct Edge
 * @brief 记录一条边相关信息
 */
struct Edge {
    ll end;              // 终点
    ll cost;             // 边权
    ll last_edge_index;  // 同一顶点的上一条边在边数组中的位置
};

int main() {
    std::function qr = QuickRead<ll>;
    // 有线电视网节点数和用户终端数
    ll n = qr(), m = qr();
    // 记录边的数组，填充0下标
    std::vector<Edge> edges{{0, 0, 0}};
    // 存储边的数量为节点数量
    edges.reserve(n);

    // 记录顶点的最后一条边在edges数组中的下标
    std::vector<ll> last_edge_index(n + 1);

    // 获取转播站数据,转播站编号为i
    for (ll i = 1; i <= n - m; i++) {
        // 这个转播站的节点数
        ll num_nodes = qr();

        // 获取边信息
        for (ll j = 1; j <= num_nodes; j++) {
            ll end = qr();   // 边的终点
            ll cost = qr();  // 边的权重
            // 这条边插入到边数组中
            edges.emplace_back(end, cost, last_edge_index[i]);
            // 更新i顶点对应的最后一条边在边数组中的索引
            last_edge_index[i] = static_cast<ll>(edges.size() - 1);
        }
    }
    // 记录不同编号的用户愿意付费的钱数
    std::vector<ll> cost_each_user(n + 1);
    // 获取用户愿意的付费钱数
    for (ll i = n - m + 1; i <= n; i++) {
        cost_each_user[i] = qr();
    }
    // 记录不同顶点，满足不同个用户要求赚取的最大钱数，初始值为负数
    std::vector<std::vector<ll>> dp(
        n + 1, std::vector<ll>(n + 1, std::numeric_limits<int>::min())
    );
    // 将dp[i][0]的值赋值为0,表示不满足任何用户的赚取钱数最大为0
    for (ll i = 1; i <= n; i++) {
        dp[i][0] = 0;
    }

    std::function<ll(ll)> dfs = [&](ll vertex) -> ll {
        // 判断是否此节点为叶子节点
        if (vertex > n - m) {
            // 如果是叶子节点，那么此节点的赚取钱数就是用户付费数
            dp[vertex][1] = cost_each_user[vertex];
            // 算作一个节点
            return 1;
        }
        ll num_leaves = 0;  // 记录该节点的叶子节点个数
        // 遍历这个顶点的所有边
        for (ll i = last_edge_index[vertex]; i != 0;
             i = edges[i].last_edge_index) {
            ll end = edges[i].end;         // 记录这条边的终点
            ll num_leaves_son = dfs(end);  // 记录子节点的叶子节点个数

            num_leaves += num_leaves_son;
            // 枚举取多少个叶子节点，也就是满足多少用户需求
            for (ll j = num_leaves; j > 0; j--) {
                // 枚举满足多少个 此时end节点的用户
                for (ll k = 1; k <= std::min(j, num_leaves_son); k++) {
                    dp[vertex][j] = std::max(
                        dp[vertex][j],
                        dp[vertex][j - k] + dp[end][k] - edges[i].cost
                    );
                }
            }
        }
        return num_leaves;
    };
    dfs(1);
    // 枚举满足的用户数量
    for (ll i = m; i >= 1; i--) {
        // 找到第一个不亏钱的用户数量
        if (dp[1][i] >= 0) {
            QuickWrite(i);
            return 0;
        }
    }
    return 0;
}

/**s
 * @brief 快速读取输入的整数
 * @return 读取到的数字
 */
template <std::integral T>
T QuickRead() {
    bool minus = false;  // 记录该数字是否为负数送
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
