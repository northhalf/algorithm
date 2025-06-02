class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        vector<unsigned long long> dp(target + 1);
        dp[0] = 1;
        // 枚举背包容量
        for (int i = 1; i <= target; i++) {
            // 枚举选择的物品
            for (int j = 0; j < nums.size(); j++) {
                // 如果能装下则选取
                if (i >= nums[j]) {
                    dp[i] += dp[i - nums[j]];
                }
            }
        }

        return dp[target];
    }
};