/* UTF-8 */
#include <algorithm>
#include <array>
#include <cctype>
#include <concepts>
#include <functional>
#include <iostream>
#include <limits>
#include <ranges>
#include <unordered_map>
#include <utility>
#include <vector>
using ll = long long;
template <std::integral T>
T QuickRead();
template <std::integral T>
void QuickWrite(T num);

ll dp[6][6][6][6][6];
/**
 * @struct discount
 * @brief 表示优惠的结构体
 */
struct discount {
    ll num_item;                      // 该优惠需要的物品组合数
    ll cost;                          // 该优惠的价格
    std::vector<ll> id;               // 物品id
    std::vector<ll> nums;             // 物品所需数目
    std::array<ll, 6> mark_to_num{};  // 映射物品的对应1-5数字的对应数目
};

int main() {
    std::function qr = QuickRead<ll>;
    ll num_discount_plan = qr();      // 优惠方案数
    std::vector<discount> discounts;  // 记录优惠信息
    discounts.reserve(num_discount_plan);
    // 获取优惠信息
    for (ll i = 0; i < num_discount_plan; i++) {
        ll num_item = qr();  // 优惠由几种商品构成
        discount temp;       // 临时存储本次优惠信息
        temp.num_item = num_item;
        temp.id.reserve(num_item);
        temp.nums.reserve(num_item);

        // 获取该优惠的商品组成
        for (int j = 0; j < num_item; j++) {
            temp.id.emplace_back(qr());
            temp.nums.emplace_back(qr());
        }
        // 获取该优惠的总价
        temp.cost = qr();
        discounts.push_back(std::move(temp));
    }
    ll num_sorts_plan = qr();  // 记录计划购买的商品种数

    std::vector<ll> num_items_plan(6);     // 记录各商品需要多少个
    std::vector<ll> cost_each_item(6);     // 记录每个物品的单价
    std::unordered_map<ll, ll> id_to_num;  // 映射id到1-5的数字

    // 开始记录物品的原来信息，即计划购买的个数，单价
    for (int i = 1; i <= num_sorts_plan; i++) {
        ll id = qr();              // 记录这个物品的对应id
        id_to_num[id] = i;         // 记录对应映射
        num_items_plan[i] = qr();  // 记录这个物品预期的购买个数
        cost_each_item[i] = qr();  // 记录这个物品的原来单价
    }
    // 映射优惠方案中的物品id对应映射数字的对应数目
    for (size_t i = 0; i < discounts.size(); i++) {
        for (ll j = 0; j < discounts[i].num_item; j++) {
            discounts[i].mark_to_num[id_to_num[discounts[i].id[j]]] =
                discounts[i].nums[j];
        }
    }

    // 如果按照原本单价购买
    for (ll n1 = 0; n1 <= num_items_plan[1]; n1++) {
        for (ll n2 = 0; n2 <= num_items_plan[2]; n2++) {
            for (ll n3 = 0; n3 <= num_items_plan[3]; n3++) {
                for (ll n4 = 0; n4 <= num_items_plan[4]; n4++) {
                    for (ll n5 = 0; n5 <= num_items_plan[5]; n5++) {
                        dp[n1][n2][n3][n4][n5] =
                            n1 * cost_each_item[1] + n2 * cost_each_item[2] +
                            n3 * cost_each_item[3] + n4 * cost_each_item[4] +
                            n5 * cost_each_item[5];
                    }
                }
            }
        }
    }
    // 使用优惠方案，完全背包
    // 枚举优惠方案
    for (size_t i = 0; i < discounts.size(); i++) {
        for (ll n1 = discounts[i].mark_to_num[1]; n1 <= num_items_plan[1];
             n1++) {
            for (ll n2 = discounts[i].mark_to_num[2]; n2 <= num_items_plan[2];
                 n2++) {
                for (ll n3 = discounts[i].mark_to_num[3];
                     n3 <= num_items_plan[3]; n3++) {
                    for (ll n4 = discounts[i].mark_to_num[4];
                         n4 <= num_items_plan[4]; n4++) {
                        for (ll n5 = discounts[i].mark_to_num[5];
                             n5 <= num_items_plan[5]; n5++) {
                            dp[n1][n2][n3][n4][n5] = std::min(
                                dp[n1 - discounts[i].mark_to_num[1]]
                                  [n2 - discounts[i].mark_to_num[2]]
                                  [n3 - discounts[i].mark_to_num[3]]
                                  [n4 - discounts[i].mark_to_num[4]]
                                  [n5 - discounts[i].mark_to_num[5]] +
                                    discounts[i].cost,
                                dp[n1][n2][n3][n4][n5]
                            );
                        }
                    }
                }
            }
        }
    }
    QuickWrite(dp[num_items_plan[1]][num_items_plan[2]][num_items_plan[3]]
                 [num_items_plan[4]][num_items_plan[5]]);
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