#include <bits/stdc++.h>
using namespace std; 

/**
 * Memoization - Top-down
 * TC - O(N x M) 
 * SC - O(N) + O(N X M) 
 * Reason - O(N) for recursive stack space and N x M for external dp array
*/


int getMaxPathSum(int i, int j, int n, int m, vector<vector<int>> matrix, vector<vector<int>> &dp){
    if(i >= n || j < 0 || j >= m) return -1e9;
    if(i == n-1) return matrix[i][j];    
    if(dp[i][j] != -1) return dp[i][j];

    int dcol[] = {-1,0,1};
    int ans = INT_MIN;
    for(int k = 0;k<3;k++){
        int currSum = matrix[i][j] + getMaxPathSum(i+1, j+dcol[k], n, m, matrix, dp);
        ans = max(ans, currSum);
    }
    return dp[i][j] = ans;
}

int getMaxPathSum1(vector<vector<int>> &matrix)
{
    int ans = INT_MIN;
    int n = matrix.size();
    int m = matrix[0].size();
    vector<vector<int>> dp(n, vector<int> (m, -1));
    for(int i = 0;i<m;i++){
        ans = max(ans, getMaxPathSum(0, i, n, m, matrix, dp));
    }
    return ans;
}

/**
 * Tabulation - Bottom_Up Approach
 * TC - O(N x M) + O(M){ to find maximum from first row }
 * SC - O(N x M)
*/

int getMaxPathSum2(vector<vector<int>> &matrix)
{
    int n = matrix.size();
    int m = matrix[0].size();
    vector<vector<int>> dp(n, vector<int> (m, -1));

    dp[n-1] = matrix[n-1];

    int dcol[] = {-1,0,1};

    for(int i = n-2;i>=0;i--){
        for(int j = m-1;j>=0;j--){
            int ans = INT_MIN;
            for(int dir = 0;dir<3;dir++){
                int ncol = j + dcol[dir];
                if(ncol >= 0 && ncol < m){
                    ans = max(ans, dp[i+1][ncol]);
                }
            }
            dp[i][j] = matrix[i][j] + ans;
        }
    }

    int maxSum = INT_MIN;
    for(int i = 0;i<m;i++){
        maxSum = max(maxSum, dp[0][i]);
    }
    return maxSum;
}

/**
 * Space Optimisation 
 * TC - O(N x M) Reason: There are two nested loops
 * SC - O(M) { Reason: We are using an external array of size ‘M’ to store only one row.}
*/

int getMaxPathSum3(vector<vector<int>> &matrix)
{
    int n = matrix.size();
    int m = matrix[0].size();
    vector<int> next(m, -1);

    next = matrix[n-1];

    int dcol[] = {-1,0,1};

    for(int i = n-2;i>=0;i--){
        vector<int> curr(m, -1);
        for(int j = m-1;j>=0;j--){
            int ans = INT_MIN;
            for(int dir = 0;dir<3;dir++){
                int ncol = j + dcol[dir];
                if(ncol >= 0 && ncol < m){
                    ans = max(ans, next[ncol]);
                }
            }
            curr[j] = matrix[i][j] + ans;
        }
        next = curr;
    }
    return *max_element(begin(next), end(next));
}

int main(){
    vector<vector<int>> matrix = {{1,2,10,4},
    {100,3,2,1},
    {1,1,20,2},
    {1,2,2,1}};

    cout << "maximum path sum is "<< getMaxPathSum2(matrix);
}