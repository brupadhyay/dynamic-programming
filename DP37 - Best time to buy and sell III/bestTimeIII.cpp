#include <bits/stdc++.h>
using namespace std;

/**
 * Memoization - Top-Down
 * TC - O(N x 2 x 3)
 * SC - O(N) + O(N x 2 x 3)
 * Reason - Recursive stack space
*/

int transaction(int i, int buy, int txn, int n, vector<int> &prices, vector<vector<vector<int>>> &dp){
    if(i == n || txn == 2) return 0;
    if(dp[i][buy][txn] != -1) return dp[i][buy][txn];

    int profit = 0;
    if(buy){
        profit = max(-prices[i] + transaction(i+1, 0, txn, n, prices, dp), 0 + transaction(i+1, 1, txn, n, prices, dp));
    } else {
        profit = max(prices[i] + transaction(i+1, 1, txn+1, n, prices, dp), 0 + transaction(i+1, 0,txn,n, prices, dp));
    }
    return dp[i][buy][txn] = profit;
}

int maxProfit(vector<int>& prices) {
    int n = prices.size();
    vector<vector<vector<int>>> dp(n, vector<vector<int>> (2, vector<int> (3, -1)));
    return transaction(0, 1, 0, n, prices, dp);
}

/**
 * Tabulation - Bottom-Up
 * TC - O(N x 2 x 3)
 * SC - O(N x 2 x 3)
 * Reason - dp array of size n x 2 x 3
*/


int maxProfit(vector<int>& prices) {
    int n = prices.size();
    vector<vector<vector<int>>> dp(n+1, vector<vector<int>> (2, vector<int> (3, 0)));
    for(int i = n-1; i >= 0; i--){
        for(int buy = 0; buy <= 1; buy++){
            for(int txn = 0; txn < 2; txn++){
                int profit = 0;
                if(buy){
                    profit = max(-prices[i] + dp[i+1][0][txn], 0 + dp[i+1][1][txn]);
                } else {
                    profit = max(prices[i] + dp[i+1][1][txn+1], 0 + dp[i+1][0][txn]);
                }
                dp[i][buy][txn] = profit;
            }
        }
    }
    return dp[0][1][0];
}

/**
 * Space Optimisation - Bottom-Up
 * TC - O(N x 2 x 3)
 * SC - O(1)
 * Reason - front/curr array of constant space
*/

int maxProfit(vector<int>& prices) {
    int n = prices.size();
    vector<vector<int>> front(2, vector<int> (3, 0));
    vector<vector<int>> curr(2, vector<int> (3, 0));

    for(int i = n-1; i >= 0; i--){
        for(int buy = 0; buy <= 1; buy++){
            for(int txn = 0; txn < 2; txn++){
                int profit = 0;
                if(buy){
                    profit = max(-prices[i] + front[0][txn], 0 + front[1][txn]);
                } else {
                    profit = max(prices[i] + front[1][txn+1], 0 + front[0][txn]);
                }
                curr[buy][txn] = profit;
            }
        }
        front = curr;
    }
    return front[1][0];
}

/**
 * Another approach for this question would be 
 * 2 transactions => 
 * Buy Sell Buy Sell
 * 0    1   2   3   4(end)
 * base case if(txn == 4 or i >= n) return 0
 * if txn is even then buy else sell the stocks other things same
*/

/**
 * Memoization - Top-Down
 * TC - O(N x 4)
 * SC - O(N) + O(N x 4)
 * Reason - Recursive stack space
*/

int earnedProfit(int i, int txn, vector<int> &prices, vector<vector<int>> &dp){
    if(i == prices.size() || txn == 4) return 0;

    if(dp[i][txn] != -1) return dp[i][txn];

    int pro = 0;
    if(txn % 2 == 0){
        pro = max(-prices[i] + earnedProfit(i+1, txn+1, prices, dp), 0 + earnedProfit(i+1, txn, prices, dp));
    } else {
        pro = max(prices[i] + earnedProfit(i+1, txn+1, prices, dp), 0 + earnedProfit(i+1, txn, prices, dp));
    }
    return dp[i][txn] = pro;
}

int maxProfit(vector<int>& prices) {
    int n = prices.size();
    vector<vector<int>> dp(n, vector<int> (4, -1));
    return earnedProfit(0, 0, prices, dp);
}

/**
 * Tabulation - Bottom-Up
 * TC - O(N x 4)
 * SC - O(N x 5)
 * Reason - dp array of n x 5 due to shifting of index
*/

int maxProfit(vector<int>& prices) {
    int n = prices.size();
    vector<vector<int>> dp(n+1, vector<int> (5, 0));
    for(int i = n-1; i >= 0; i--){
        for(int txn = 0; txn < 4; txn++){
            int profit = 0;
            if(txn % 2 == 0){
                profit = max(-prices[i] + dp[i+1][txn+1], 0 + dp[i+1][txn]);
            } else {
                profit = max(prices[i] + dp[i+1][txn+1], 0 + dp[i+1][txn]);
            }
            dp[i][txn] = profit;
        }
        
    }
    return dp[0][0];
}

/**
 * Space Optimisation -
 * TC - O(N x 4)
 * SC - O(1)
 * Reason - 5-sized array almost a constant space
*/

int maxProfit(vector<int>& prices) {
    int n = prices.size();
    vector<int> front(5, 0);
    vector<int> curr(5, 0);
    for(int i = n-1; i >= 0; i--){
        for(int txn = 0; txn < 4; txn++){
            int profit = 0;
            if(txn % 2 == 0){
                profit = max(-prices[i] + front[txn+1], 0 + front[txn]);
            } else {
                profit = max(prices[i] + front[txn+1], 0 + front[txn]);
            }
            curr[txn] = profit;
        }
        front = curr;
    }
    return front[0];
}

/**
 * Single Array Space Optimised Solution -
 * if we closely observe, we just need front[txn+1] and front[txn]
 * meaning one cell down and one cell down right
 * so instead of 2 x 1-D we can use 1-D array to fill cell from 0 to 3 for transaction
 * this will keep every value intact because current value depends on further values
 * TC - O(N x 4)
 * SC - O(1)
*/

int maxProfit(vector<int>& prices) {
    int n = prices.size();
    vector<int> curr(5, 0);
    for(int i = n-1; i >= 0; i--){
        for(int txn = 0; txn < 4; txn++){
            int profit = 0;
            if(txn % 2 == 0){
                profit = max(-prices[i] + curr[txn+1], 0 + curr[txn]);
            } else {
                profit = max(prices[i] + curr[txn+1], 0 + curr[txn]);
            }
            curr[txn] = profit;
        }
    }
    return curr[0];
}