/* UTF-8 */
#include <algorithm>
#include <iostream>
int dp[100001];
int main() {
    int t, n;
    std::cin >> t >> n;
    for (int i = 0; i < n; i++) {
        int a, b;
        std::cin >> a >> b;
        for (int j = t; j >= a; j--) {
            dp[j] = std::max(dp[j], dp[j - a] + b);
        }
    }
    std::cout << dp[t] << std::endl;
    return 0;
}