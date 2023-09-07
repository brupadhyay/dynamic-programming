#include <bits/stdc++.h> 
using namespace std;

/**
 * Memoization - Top-down approach
 * TC - O(M x N)
 * SC - O(M + N - 2) { recursive stack space } + O(M x N) { dp array }
*/

int f(int i, int j, int m, int n, vector<vector<int>> &dp){
    if(i == m-1 && j == n-1) return 1;
    if(i >= m || j >= n) return 0;
    if(dp[i][j] != -1) return dp[i][j];

    return dp[i][j] = f(i, j + 1, m, n, dp) + f(i + 1, j, m, n, dp);
}

int uniquePaths1(int m, int n) {
    vector<vector<int>> dp(m, vector<int> (n, -1));
    return f(0, 0, m, n, dp);
}

/**
 * Tabulation - bottom-up approach
 * TC - O(M x N)
 * SC - O(M x N) { we eliminated recursive stack space }
*/

int uniquePaths2(int n, int m) {
    vector<vector<int>> dp(n, vector<int> (m, 0));
    dp[n-1][m-1] = 1;
    for(int row = n-1;row>=0;row--){
        for(int col = m-1;col>=0;col--){
            if(row == n-1 && col == m-1) continue;
            int right = (col + 1 >= m) ? 0 : dp[row][col + 1];
            int down = (row + 1 >= n) ? 0 : dp[row + 1][col];
            dp[row][col] = right + down;
        }
    }
    return dp[0][0];
}

/**
 * Space Optimisation - using down element and right element values
 * TC - O(N x M)
 * SC - O(M) + O(M) ~ O(M)
*/

int uniquePaths3(int n, int m) {
    vector<int> next(m, 0);
    for(int row = n-1;row>=0;row--){
        vector<int> curr(m, 0);
        for(int col = m-1;col>=0;col--){
            if(row == n-1 && col == m-1) {
                curr[m-1] = 1;
                continue;
            }
            int right = 0;
            // just check if it's safe to take right element
            if(col < m-1) right = curr[col + 1];
            // down element is just below but same column
            int down = next[col];
            curr[col] = right + down;
        }
        next = curr; // assign next to curr for further rows
    }
    return next[0];
}

int main(){
    int n = 3;
    int m = 7;
    cout << uniquePaths3(n, m);
}