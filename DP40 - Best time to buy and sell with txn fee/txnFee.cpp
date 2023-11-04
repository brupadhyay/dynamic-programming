#include <bits/stdc++.h>
using namespace std;

/**
 * Memoization - Top-Down
 * One transaction is buy and sell
 * TC - O(N x 2)
 * SC - O(N) + O(N x 2)
 * Reason - Recursive stack space
*/

int find(int i, int buy, vector<int> &prices, int fee, vector<vector<int>> &dp){
    if(i == prices.size()) return 0;
    if(dp[i][buy] != -1) return dp[i][buy];

    int profit = 0;
    if(buy){
        profit = max(-prices[i] + find(i+1, 0, prices, fee, dp), 0 + find(i+1, 1, prices, fee, dp));
    } else {
        profit = max(prices[i] - fee + find(i+1, 1, prices, fee, dp), 0 + find(i+1, 0, prices, fee, dp));
    }
    return dp[i][buy] = profit;
}

int maxProfit(vector<int>& prices, int fee) {
    int n = prices.size();
    vector<vector<int>> dp(n, vector<int> (2, -1));
    return find(0, 1, prices, fee, dp);
}

/**
 * Tabulation - Bottom-Up
 * TC - O(N x 2)
 * SC - O(N x 2)
*/

int maxProfit(vector<int>& prices, int fee) {
    int n = prices.size();
    vector<vector<int>> dp(n+1, vector<int> (2, 0));
    for(int i = n-1; i >= 0; i--){
        for(int j = 0; j <= 1; j++){
            int profit = 0;
            if(j){
                profit = max(-prices[i] + dp[i+1][0], 0 + dp[i+1][1]);
            } else {
                profit = max(prices[i] - fee + dp[i+1][1], 0 + dp[i+1][0]);
            }
            dp[i][j] = profit;
        }
    }
    return dp[0][1];
}

/**
 * Space Optimisation - 2D to 1D array
 * TC - O(N x 2)
 * SC - O(1)
*/

int maxProfit(vector<int>& prices, int fee) {
    int n = prices.size();
    vector<int> curr(2, 0);
    vector<int> front(2, 0);
    for(int i = n-1; i >= 0; i--){
        for(int j = 0; j <= 1; j++){
            int profit = 0;
            if(j){
                profit = max(-prices[i] + front[0], 0 + front[1]);
            } else {
                profit = max(prices[i] - fee + front[1], 0 + front[0]);
            }
            curr[j] = profit;
        }
        front = curr;
    }
    return front[1];
}

/**
 * Single Array Space Optimisation - 1D array
 * TC - O(N x 2)
 * SC - O(1)
*/

int maxProfit(vector<int>& prices, int fee) {
    int n = prices.size();
    vector<int> curr(2, 0);
    for(int i = n-1; i >= 0; i--){
        for(int j = 0; j <= 1; j++){
            int profit = 0;
            if(j){
                profit = max(-prices[i] + curr[0], 0 + curr[1]);
            } else {
                profit = max(prices[i] - fee + curr[1], 0 + curr[0]);
            }
            curr[j] = profit;
        }
    }
    return curr[1];
}