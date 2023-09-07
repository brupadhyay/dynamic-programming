#include <bits/stdc++.h> 
using namespace std;

/**
 * Recursive Approach - TC ~ O(2^n)
*/

int maxSum(int ind, vector<int> nums, int n){
    if(ind == n-1) return nums[ind];
    if(ind >= n) return 0;

    int pick = nums[ind] + maxSum(ind + 2, nums, n);
    int nonpick = 0 + maxSum(ind + 1, nums, n);
    return max(pick, nonpick);
}

int maximumNonAdjacentSum1(vector<int> &nums){
    int n = nums.size();
    return maxSum(0, nums, n);
}

/**
 * Memoization - 
 * TC - O(N)
 * SC - O(N) { rec.stack space} + O(N) { dp array }
*/

int maxSum(int ind, vector<int> nums, int n, vector<int> &dp){
    if(ind == n-1) return nums[ind];
    if(ind >= n) return 0;
    if(dp[ind] != -1) return dp[ind];

    int pick = nums[ind] + maxSum(ind + 2, nums, n, dp);
    int nonpick = 0 + maxSum(ind + 1, nums, n, dp);
    return dp[ind] = max(pick, nonpick);
}

int maximumNonAdjacentSum2(vector<int> &nums){
    int n = nums.size();
    vector<int> dp(n, -1);
    return maxSum(0, nums, n, dp);
}

/**
 * Tabulation - Bottom-Up
 * TC - O(N)
 * SC - O(N)
*/

int maximumNonAdjacentSum3(vector<int> &nums){
    int n = nums.size();
    vector<int> dp(n, -1);
    dp[n-1] = nums[n-1];
    for(int i = n-2;i>=0;i--){
        int take = nums[i];
        if(i < n-2) take += dp[i + 2];
        int nontake = dp[i+1];
        dp[i] = max(take, nontake);
    }
    return dp[0];
}

/**
 * Space Optimisation - using previous two conditions
 * TC - O(N)
 * SC - O(1)
*/

int maximumNonAdjacentSum4(vector<int> &nums){
    int n = nums.size();
    int prev2 = 0;
    int prev1 = nums[n-1];
    for(int i = n-2;i>=0;i--){
        int pick = nums[i] + prev2; // if considering ind then we take (ind + 2)th element
        int nonpick = prev1; // or if we don't pick ind then we can take (ind + 1)th element
        int currMax = max(pick, nonpick);
        prev2 = prev1;
        prev1 = currMax;
    }
    return prev1;
}

int main(){
    vector<int> nums = {1, 2, 3, 1, 3, 5, 8, 1, 9};
    cout << "the maximum non-adjacent sum is " << maximumNonAdjacentSum4(nums) << endl;
}