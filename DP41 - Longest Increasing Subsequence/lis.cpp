#include <bits/stdc++.h>
using namespace std;

/**
 * Memoization - Top-Down
 * TC - O(N x N)
 * SC - O(N) + O(N x N)
 * O(N) for recursive stack space
*/

int lis(int i, int prev, vector<int>& nums, vector<vector<int>> &dp){
    if(i == nums.size()) return 0;

    if(dp[i][prev+1] != -1) return dp[i][prev+1];

    int len = 0 + lis(i+1, prev, nums, dp);
    if(prev == -1 || nums[i] > nums[prev]){
        len = max(len, 1 + lis(i+1, i, nums, dp));
    }
    return dp[i][prev+1] = len;
}

int lengthOfLIS1(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> dp(n, vector<int> (n+1, -1));
    return lis(0, -1, nums, dp);
}

/**
 * Tabulation - Bottom-Up
 * TC - O(N x N)
 * SC - O(N x N)
*/

int lengthOfLIS2(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> dp(n+1, vector<int> (n+1, 0));
    for(int i = n-1; i >= 0; i--){
        for(int j = i-1; j >= -1; j--){
            int len = 0 + dp[i+1][j+1];
            if(j == -1 || nums[i] > nums[j]){
                len = max(len, 1 + dp[i+1][i+1]);
            }
            dp[i][j+1] = len;
        }
    }
    return dp[0][0];
}

/**
 * Space Optimisation - 2D to 1D array Bottom-Up
 * TC - O(N x N)
 * SC - O(N) x 2
*/

int lengthOfLIS3(vector<int>& nums) {
    int n = nums.size();
    vector<int> curr(n+1, 0);
    vector<int> next(n+1, 0);
    for(int i = n-1; i >= 0; i--){
        for(int j = i-1; j >= -1; j--){
            int len = 0 + next[j+1];
            if(j == -1 || nums[i] > nums[j]){
                len = max(len, 1 + next[i+1]);
            }
            curr[j+1] = len;
        }
        next = curr;
    }
    return curr[0];
}

/**
 * Single Array Space Solution 
 * Not much intuitive
 * TC - O(N x N)
 * SC - O(N)
*/

int lengthOfLIS4(vector<int>& nums) {
    int n = nums.size();
    vector<int> dp(n, 1);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < i; j++){
            if(nums[i] > nums[j]) dp[i] = max(dp[i], 1 + dp[j]);
        }
    }
    return *max_element(begin(dp), end(dp));
}


