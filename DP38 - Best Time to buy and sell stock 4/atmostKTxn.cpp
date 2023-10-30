#include <bits/stdc++.h>
using namespace std;

/**
 * Memoization - Top-Down
 * One transaction is buy and sell
 * K transaction is (buy and sell) K times
 * Eg - K = 3
 * B S B S B S
 * 0 1 2 3 4 5 
 * even => buy else sell
 * TC - O(N x 2*K)
 * SC - O(N) + O(N x 2*K)
 * Reason - Recursive stack space
*/

int earnedProfit(int i, int k, int txn, vector<int> &prices, vector<vector<int>> &dp){
    if(i == prices.size() || txn == 2*k) return 0;

    if(dp[i][txn] != -1) return dp[i][txn];

    int profit = 0;
    if(txn % 2 == 0){
        // buy
        profit = max(-prices[i] + earnedProfit(i+1, k, txn+1, prices, dp), 0 + earnedProfit(i+1, k, txn, prices, dp));
    } else {
        // sell
        profit = max(prices[i] + earnedProfit(i+1, k, txn+1, prices, dp), 0 + earnedProfit(i+1, k, txn, prices, dp));
    }
    return dp[i][txn] = profit;
}

int maxProfit(int k, vector<int>& prices) {
    int n = prices.size();
    vector<vector<int>> dp(n, vector<int> (2*k+1, -1));
    return earnedProfit(0, k, 0, prices, dp);
}

/**
 * Tabulation - Bottom-Up
 * TC - O(N x 2*K)
 * SC - O(N x 2*K)
 * Reason - dp array of size n x 2*K
*/

int maxProfit(int k, vector<int>& prices) {
    int n = prices.size();
    vector<vector<int>> dp(n+1, vector<int> (2*k+1, 0));
    for(int i = n-1; i >= 0; i--){
        for(int j = 0; j < 2*k; j++){
            int profit = 0;
            if(j % 2 == 0){
                // buy
                profit = max(-prices[i] + dp[i+1][j+1], 0 + dp[i+1][j]);
            } else {
                // sell
                profit = max(prices[i] + dp[i+1][j+1], 0 + dp[i+1][j]);
            }
            dp[i][j] = profit;
        }
    }
    return dp[0][0];
}

/**
 * Space Optimisation - 2D to 1D
 * TC - O(N x 2*K)
 * SC - O(2*K) + O(2*K)
*/

int maxProfit(int k, vector<int>& prices) {
    int n = prices.size();
    vector<int> front(2*k+1, 0);
    vector<int> curr(2*k+1, 0);
    for(int i = n-1; i >= 0; i--){
        for(int j = 0; j < 2*k; j++){
            int profit = 0;
            if(j % 2 == 0){
                // buy
                profit = max(-prices[i] + front[j+1], 0 + front[j]);
            } else {
                // sell
                profit = max(prices[i] + front[j+1], 0 + front[j]);
            }
            curr[j] = profit;
        }
        front = curr;
    }
    return front[0];
}

/**
 * Single Array Space Optimised
 * TC - O(N x 2*K)
 * SC - O(2*K)
*/

int maxProfit(int k, vector<int>& prices) {
    int n = prices.size();
    vector<int> curr(2*k+1, 0);
    for(int i = n-1; i >= 0; i--){
        for(int j = 0; j < 2*k; j++){
            int profit = 0;
            if(j % 2 == 0){
                // buy
                profit = max(-prices[i] + curr[j+1], 0 + curr[j]);
            } else {
                // sell
                profit = max(prices[i] + curr[j+1], 0 + curr[j]);
            }
            curr[j] = profit;
        }
    }
    return curr[0];
}