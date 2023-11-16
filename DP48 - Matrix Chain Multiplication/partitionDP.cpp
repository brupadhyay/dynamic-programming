#include <bits/stdc++.h>
using namespace std;

/**
 * Matrix Chain Multiplication (MCM)
 * Memoization
 * TC - O(N x N) x N ~ O(N^3)
 * SC - O(N x N) + O(N) - dp array and stack space
*/

int f(int i, int j, int *arr, int n, vector<vector<int>> &dp){
    if(i == j) return 0;

    if(dp[i][j] != -1) return dp[i][j];

    int mini = 1e9;
    for(int k = i; k < j; k++){
        mini = min(mini, arr[i-1]*arr[k]*arr[j] + f(i,k,arr,n, dp) + f(k+1,j,arr,n,dp));
    }
    return dp[i][j] = mini;
}

int matrixChainMultiplication(int* arr, int n) {
    vector<vector<int>> dp(n+1, vector<int> (n+1, -1));
    return f(1, n, arr, n, dp);
}

// DP 49
/**
 * Tabulation - Bottom-Up
 * TC - O(N^3)
 * SC - O(N^2)
*/

int matrixChainMultiplication(int* arr, int n) {
    vector<vector<int>> dp(n+1, vector<int> (n+1, -1));
    for(int i = 0; i < n+1; i++){
        // i == j
        dp[i][i] = 0; // all diagonal elements equal to 0
    }
    for(int i = n; i > 0; i--){
        // * i...j so ideally j > i hence j = i+1 ... n
        for(int j = i+1; j <= n; j++){
            int mini = 1e9;
            for(int k = i; k < j; k++){
                mini = min(mini, arr[i-1]*arr[k]*arr[j] + dp[i][k] + dp[k+1][j]);
            }
            dp[i][j] = mini;
        }
    }
    return dp[1][n];
}