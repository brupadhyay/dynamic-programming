#include <bits/stdc++.h> 
using namespace std;

/**
 * Memoization - Top-down
 * TC - O(N x M)
 * SC - O(N + M - 2) { recursive path space to reach end } + O(N x M) { dp matrix }
*/

int minSum(int i, int j, int n, int m, vector<vector<int>> grid,vector<vector<int>> &dp){
    
    if(i == n-1 && j == m-1) return grid[i][j];
    if(i >= n || j >= m) return 1e9;
    if(dp[i][j] != 1e9) return dp[i][j];

    int down = grid[i][j] + minSum(i + 1, j, n, m, grid, dp);
    int right = grid[i][j] + minSum(i, j + 1, n, m, grid, dp);
    return dp[i][j] = min(down, right);
}

int minSumPath1(vector<vector<int>> &grid) {
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<int>> dp(n, vector<int> (m, 1e9));
    return minSum(0, 0, n, m, grid, dp);
}

/**
 * Tabulation - Bottom-Up
 * TC - O(N x M)
 * SC - O(N x M)
*/

int minSumPath2(vector<vector<int>> &grid) {
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<int>> dp(n, vector<int> (m, 1e9));
    for(int i = n-1;i>=0;i--){
        for(int j = m-1;j>=0;j--){
            if(i == n-1 && j == m-1){
                dp[n-1][m-1] = grid[n-1][m-1];
            } else {
                int down = INT_MAX;
                int right = INT_MAX;
                if(i + 1 < n){
                    down = dp[i+1][j];
                }
                if(j + 1 < m){
                    right = dp[i][j+1];
                }
                dp[i][j] = grid[i][j] + min(down, right);
            }
        }
    }
    return dp[0][0];
}

/**
 * Space Optimisation - Bottom-Up 
 * TC - O(N x M)
 * SC - O(M) where M - no.of cols
*/

int minSumPath3(vector<vector<int>> &grid) {
    int n = grid.size();
    int m = grid[0].size();
    vector<int> next(m, 1e9);
    for(int i = n-1;i>=0;i--){
        vector<int> curr(m, 1e9);
        for(int j = m-1;j>=0;j--){
            if(i == n-1 && j == m-1){
                curr[m-1] = grid[n-1][m-1];
            } else {
                int down = INT_MAX;
                int right = INT_MAX;
                if(i + 1 < n){
                    down = next[j];
                }
                if(j + 1 < m){
                    right = curr[j+1];
                }
                curr[j] = grid[i][j] + min(down, right);
            }
        }
        next = curr;
    }
    return next[0];
}

int main(){
    vector<vector<int>> grid = {{5,9,6},
    {11,5,2}};
    cout << "minimum path sum is "<< minSumPath3(grid);
    return 0;
}