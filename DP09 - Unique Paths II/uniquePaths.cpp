#include <bits/stdc++.h> 
using namespace std;

int mod = (int)1e9+7;

/**
 * Memoization - Top-down approach
 * TC - O(M x N)
 * SC - O(M + N - 2) { recursive stack space } + O(M x N) { dp array }
*/

int count(int i, int j, int n, int m, vector<vector<int>> &dp, vector<vector<int>> mat){
    if(i >= n || j >= m) return 0;
    if(mat[i][j] == -1) return 0;
    if(i == n-1 && j == m-1) return 1;
    if(dp[i][j] != 0) return dp[i][j];

    int down = count(i + 1, j, n, m, dp, mat);
    int right = count(i, j + 1, n, m, dp, mat);
    return dp[i][j] = (down + right)%mod;
}

int mazeObstacles1(int n, int m, vector< vector< int> > &mat) {
    vector<vector<int>> dp(n, vector<int> (m, 0));
    return count(0, 0, n, m, dp, mat)%mod;
}

/**
 * Tabulation - bottom-up approach
 * TC - O(M x N)
 * SC - O(M x N) { dp matrix }
*/

int mazeObstacles2(int n, int m, vector< vector< int> > &mat) {
    vector<vector<int>> dp(n, vector<int> (m, 0));
    for(int i = n-1;i>=0;i--){
        for(int j = m-1;j>=0;j--){
            if(mat[i][j] == -1){
                dp[i][j] = 0;
            } else if(i == n-1 && j == m-1){
                dp[i][j] = 1;
            } else {
                int down = 0;
                if(i + 1 < n) down += dp[i+1][j];
                int right = 0;
                if(j + 1 < m) right += dp[i][j+1];
                dp[i][j] = (down + right)%mod;
            }
        }
    }
    return dp[0][0];
}

/**
 * Space Optimisation - 
 * TC - O(N x M)
 * SC - O(M) where M - no.of cols
*/

int mazeObstacles(int n, int m, vector< vector< int> > &mat) {
    vector<int> next(m, 0);
    for(int i = n-1;i>=0;i--){
        vector<int> temp(m, 0);
        for(int j = m-1;j>=0;j--){
            if(mat[i][j] == -1){
                temp[j] = 0;
            } else if(i == n-1 && j == m-1){
                temp[j] = 1;
            } else {
                int down = 0;
                if(i + 1 < n) down += next[j];
                int right = 0;
                if(j + 1 < m) right += temp[j+1];
                temp[j] = (down + right)%mod;
            }
        }
        next = temp;
    }
    return next[0];
}