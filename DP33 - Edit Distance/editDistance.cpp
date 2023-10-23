#include <bits/stdc++.h>
using namespace std;

/**
 * Memoization - Top-Down
 * Time Complexity: O(N*M)
 * Reason: There are two nested loops for memoization 
 * Space Complexity: O(N*M) + O(N + M)
 * Reason: We are using an external array of size (N*M) and recursive stack space.
*/

int minCost(int i, int j, int n, int m, string s, string t, vector<vector<int>> &dp){
    if(i >= n) return m - j;
    if(j >= m) return n - i;

    if(dp[i][j] != -1) return dp[i][j];

    if(s[i] == t[j]) return dp[i][j] = minCost(i+1,j+1,n,m,s,t,dp);
    else {
        int insert = 1 + minCost(i,j+1,n,m,s,t,dp);
        int del = 1 + minCost(i+1,j,n,m,s,t,dp);
        int replace = 1 + minCost(i+1,j+1,n,m,s,t,dp);
        return dp[i][j] = min(insert, min(del, replace));
    }
}

int editDistance1(string s, string t)
{
    int n = s.length();
    int m = t.length();
    vector<vector<int>> dp(n, vector<int> (m, -1));
    return minCost(0, 0, n, m, s, t, dp);
}

/**
 * Tabulation - Bottom-Up
 * Time Complexity: O(N*M) + O(N) + O(M) { for pre-filling }
 * Reason: There are two nested loops for tabulation 
 * Space Complexity: O(N*M)
 * Reason: We are using an external array of size (N*M).
*/

int editDistance2(string s, string t)
{
    int n = s.length();
    int m = t.length();
    vector<vector<int>> dp(n+1, vector<int> (m+1, 0));

    for(int i = 0; i <= m; i++){
        dp[n][i] = m - i;
    }

    for(int i = 0; i <= n; i++){
        dp[i][m] = n - i;
    }

    for(int i = n - 1; i >= 0; i--){
        for(int j = m-1; j >= 0; j--){
            if(s[i] == t[j]){
                dp[i][j] = dp[i+1][j+1];
            } else {
                int insert = 1 + dp[i][j+1];
                int del = 1 + dp[i+1][j];
                int replace = 1 + dp[i+1][j+1];
                dp[i][j] = min(insert, min(del, replace));
            }
        }
    }

    return dp[0][0];
}

/**
 * Space Optimisation - 2 x 1D Array
 * TC - O(N x M)
 * SC - O(M) + O(M)
*/

int editDistance3(string s, string t)
{
    int n = s.length();
    int m = t.length();
    vector<int> front(m+1, 0);
    vector<int> curr(m+1, 0);    
        
    for(int i = 0;i<=m;i++){
        front[i] = m - i;
    }
        
    for(int i = n - 1; i >= 0; i--){
        curr[m] = n-i;
        for(int j = m-1; j >= 0; j--){
            if(s[i] == t[j]){
                curr[j] = front[j+1];
            } else {
                int insert = 1 + curr[j+1];
                int del = 1 + front[j];
                int replace = 1 + front[j+1];
                curr[j] = min(insert, min(del, replace));
            }
        }
        front = curr;
    }

    return front[0];
}