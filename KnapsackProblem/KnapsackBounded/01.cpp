/* UTF-8 */
#include <bits/stdc++.h>

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    // 获取看花总时间
    int h, m;  // 记录时间的小时和分钟
    std::scanf(" %d:%d", &h, &m);
    int start = h * 60 + m;  // 开始时间
    std::scanf(" %d:%d", &h, &m);
    int end = h * 60 + m;        // 结束时间
    int duration = end - start;  // 看花结束时间

    int n;  // 记录多少樱花树
    std::scanf(" %d", &n);

    std::vector<int> dp(duration + 1);
    for (int i = 0; i < n; i++) {
        int t, c, p;  // 时间，美学值，次数
        std::scanf(" %d %d %d", &t, &c, &p);
        if (p == 0) {  // 如果是完全背包
            for (int j = t; j <= duration; j++) {
                dp[j] = std::max(dp[j - t] + c, dp[j]);
            }
            continue;
        }
        // p不为0,此时为多重背包
        /* 进行二进制优化 */
        // 每次循环结束 剩余次数-=j, j*=2
        for (int j = 1; j <= p; p -= j, j <<= 1) {
            int now_time = j * t;   // 这组数据的时间
            int now_count = j * c;  // 这组数据的美学值
            // 进行一次01背包
            for (int k = duration; k >= now_time; k--) {
                dp[k] = std::max(dp[k - now_time] + now_count, dp[k]);
            }
        }
        // 如果剩余次数为0,则进行下次循环
        if (p == 0) continue;

        // 剩余次数不为0,在再来一次01背包
        int time = p * t;
        int count = p * c;
        for (int j = duration; j >= time; j--) {
            dp[j] = std::max(dp[j - time] + count, dp[j]);
        }
    }
    std::printf("%d\n", dp[duration]);
    return 0;
}