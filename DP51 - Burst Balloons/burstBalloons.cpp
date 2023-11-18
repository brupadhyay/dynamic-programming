#include <bits/stdc++.h>
using namespace std;

/**
 * Memoization Approach - top-down
 * Time Complexity: O(N^3), 
 * There are total N^2 no. of states. And for each state, we are running
 * partitioning loop roughly for N times.
 * Space Complexity: O(N^2) + Auxiliary stack space of O(N), N^2 for the dp array
 * we are using. 
*/

int f(int i, int j, vector<int> &nums, vector<vector<int>> &dp){
    if(i > j) return 0;
    if(dp[i][j] != -1) return dp[i][j];
    
    int maxi = -1e9;
    for(int k = i; k <= j; k++){
        int cost = nums[i-1]*nums[k]*nums[j+1] + f(i,k-1,nums,dp) + f(k+1,j,nums,dp);
        maxi = max(maxi, cost);
    }
    return dp[i][j] = maxi;
}

int maxCoins1(vector<int>& nums) {
    int n = nums.size();
    nums.push_back(1);
    nums.insert(begin(nums), 1);
    vector<vector<int>> dp(n+2, vector<int> (n+2, -1));
    return f(1, n, nums, dp);
}

/**
 * Tabulation - bottom-up
 * Time Complexity: O(N^3), There are total N^2 no. of states. 
 * And for each state, we are running a partitioning loop roughly for N times.
 * Space Complexity: O(N^2), N^2 for the dp array we are using.
*/

int maxCoins2(vector<int>& nums) {
    int n = nums.size();
    nums.push_back(1);
    nums.insert(begin(nums), 1);
    vector<vector<int>> dp(n+2, vector<int> (n+2, 0));
    for(int i = n; i >= 1; i--){
        for(int j = 1; j <= n; j++){
            if(i > j) continue;
            int maxi = -1e9;
            for(int k = i; k <= j; k++){
                int cost = nums[i-1]*nums[k]*nums[j+1] + dp[i][k-1] + dp[k+1][j];
                maxi = max(maxi, cost);
            }
            dp[i][j] = maxi;
        }
    }
    return dp[1][n];
}

int main() {
    vector<int> nums = {3, 1, 5, 8};
    int maxCoinsResult = maxCoins2(nums);
    cout << "Maximum coins obtained: " << maxCoinsResult << "\n";
    
    return 0;
}