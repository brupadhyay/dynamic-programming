#include <bits/stdc++.h>
using namespace std;

/**
 * Memoization - Top-Down
 * One transaction is buy and sell
 * after sell, move to (i+2)th day to buy again
 * TC - O(N x 2)
 * SC - O(N) + O(N x 2)
 * Reason - Recursive stack space
*/

int find(int i, int buy, vector<int> &prices, vector<vector<int>> &dp){
    if(i >= prices.size()) return 0;
    if(dp[i][buy] != -1) return dp[i][buy];
    int profit = 0;
    if(buy){
        profit = max(-prices[i] + find(i+1, 0, prices, dp), 0 + find(i+1,1,prices, dp));
    } else {
        profit = max(prices[i] + find(i+2, 1, prices, dp), 0 + find(i+1, 0, prices, dp));
    }
    return dp[i][buy] = profit;
}

int stockProfit(vector<int> &prices){
    int n = prices.size();
    vector<vector<int>> dp(n, vector<int> (2, -1));
    return find(0, 1, prices, dp);
}

/**
 * Tabulation - Bottom-Up
 * TC - O(N x 2)
 * SC - O(N x 2)
*/

int stockProfit(vector<int> &prices){
    int n = prices.size();
    vector<vector<int>> dp(n+2, vector<int> (2, 0));
    for(int i = n-1; i >= 0; i--){
        for(int buy = 0; buy <= 1; buy++){
            int profit = 0;
            if(buy){
                profit = max(-prices[i] + dp[i+1][0], dp[i+1][1]);
            } else {
                profit = max(prices[i] + dp[i+2][1], 0 + dp[i+1][0]);
            }
            dp[i][buy] = profit;
        }
    }
    return dp[0][1];
}

/**
 * Space Optimisation - 2D to 1D
 * TC - O(N x 2)
 * SC - O(1) { almost constant }
*/

int stockProfit(vector<int> &prices){
    int n = prices.size();
    vector<int> front(2, 0);
    vector<int> curr(2, 0);
    vector<int> next(2, 0);
    for(int i = n-1; i >= 0; i--){
        for(int buy = 0; buy <= 1; buy++){
            int profit = 0;
            if(buy){
                profit = max(-prices[i] + front[0], front[1]);
            } else {
                profit = max(prices[i] + next[1], 0 + front[0]);
            }
            curr[buy] = profit;
        }
        next = front;
        front = curr;
    }
    return front[1];
}