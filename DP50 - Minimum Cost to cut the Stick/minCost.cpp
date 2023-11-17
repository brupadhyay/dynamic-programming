#include <bits/stdc++.h>
using namespace std;

/**
 * Memoization - Top-Down
 * TC -> O(C^3) where C is the size of cuts array
 * SC -> O(C x C) + O(C) { recursive stack space }
*/

int f(int i, int j, vector<int> &cuts, vector<vector<int>> &dp){
    if(i > j) return 0;
    if(dp[i][j] != -1) return dp[i][j];

    int mini = 1e9;
    for(int k = i; k <= j; k++){
        int cost = cuts[j+1] - cuts[i-1] + f(i, k-1, cuts, dp) + f(k+1, j, cuts, dp);
        mini = min(mini, cost);
    }
    return dp[i][j] = mini;
}
int minCost(int n, vector<int>& cuts) {
    int c = cuts.size();
    cuts.push_back(n);
    cuts.insert(cuts.begin(), 0);
    sort(cuts.begin(), cuts.end());
    vector<vector<int>> dp(c+1, vector<int> (c+1, -1));
    return f(1, c, cuts, dp);
}

/**
 * Tabulation - Bottom-Up
 * TC - O(C^3)
 * SC - O(C^2)
*/

int minCost(int n, vector<int>& cuts) {
    int c = cuts.size();
    cuts.push_back(n);
    cuts.insert(cuts.begin(), 0);
    sort(cuts.begin(), cuts.end());
    vector<vector<int>> dp(c+2, vector<int> (c+2, 0));
    for(int i = c; i >= 1; i--){
        for(int j = 1; j <= c; j++){
            if(i > j) continue;
            int mini = 1e9;
            for(int k = i; k <= j; k++){
                // i = n so i + 1 might overflow hence c + 2 size
                int cost = cuts[j+1] - cuts[i-1] + dp[i][k-1] + dp[k+1][j];
                mini = min(mini, cost);
            }
            dp[i][j] = mini;
        }
    }
    return dp[1][c];
}