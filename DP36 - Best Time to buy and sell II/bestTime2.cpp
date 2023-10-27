#include <bits/stdc++.h>
using namespace std;

/**
 * Memoization - Top-down
 * TC - O(N x 2)
 * SC - O(N x 2) + O(N) { recursive stack space }
*/

long maxProfit(int i, int buy, long *values, int n, vector<vector<long>> &dp){
    if(i == n) return 0;
    
    if(dp[i][buy] != -1) return dp[i][buy];
    
    long profit = 0;
    if(buy){
        // on a particular day even if we are legible to buy
        // we will either buy or not buy
        // because in future we may find stock with less value
        profit = max(-values[i] + maxProfit(i+1, 0, values, n, dp), 0 + maxProfit(i+1, 1, values, n, dp));
    } else {
        // on a particular day even if we are legibe to sell
        // we will either sell or not sell
        // because in future we may acquire more profit by selling
        profit = max(values[i] + maxProfit(i+1, 1, values, n, dp), 0 + maxProfit(i+1, 0, values, n, dp));
    }
    // transaction = selling price - cost price (alternatively => -buy + sell)
    return dp[i][buy] = profit;
}

long getMaximumProfit1(long *values, int n)
{
    // buy - 1, not buy - 0
    vector<vector<long>> dp(n, vector<long> (2, -1));
    return maxProfit(0, 1, values, n, dp);
}

/**
 * Tabulation - Bottom-Up
 * TC - O(N x 2)
 * SC - O(N x 2)
*/

long getMaximumProfit2(long *values, int n)
{
    vector<vector<long>> dp(n+1, vector<long> (2, 0));

    for(int i = n-1; i >= 0; i--){
        for(int buy = 0; buy <= 1; buy++){
            long profit = 0;
            if(buy){
                profit = max(-values[i] + dp[i+1][0], dp[i+1][1]);
            } else {
                profit = max(values[i] + dp[i+1][1], 0 + dp[i+1][0]);
            }
            dp[i][buy] = profit;
        }
    }
    // return 0th day buy value
    return dp[0][1];
}

/**
 * Space Optimisation - 1D Array (constant space)
 * TC - O(N x 2)
 * SC - O(4)
*/

long getMaximumProfit3(long *values, int n)
{
    vector<long> front(2, 0);
    vector<long> curr(2, 0);

    for(int i = n-1; i >= 0; i--){
        for(int buy = 0; buy <= 1; buy++){
            long profit = 0;
            if(buy){
                profit = max(-values[i] + front[0], front[1]);
            } else {
                profit = max(values[i] + front[1], 0 + front[0]);
            }
            curr[buy] = profit;
        }
        front = curr;
    }
    return front[1];
}

/**
 * Space Optimisation - constant space
 * TC - O(N)
 * SC - O(1)
*/

long getMaximumProfit4(long *values, int n)
{
    long frontBuy = 0, frontNotBuy = 0;
    long currBuy, currNotBuy;

    for(int i = n-1; i >= 0; i--){
        currBuy = max(-values[i] + frontNotBuy, frontBuy);
        currNotBuy = max(values[i] + frontBuy, frontNotBuy);
        frontNotBuy = currNotBuy;
        frontBuy = currBuy;
    }
    return frontBuy;
}