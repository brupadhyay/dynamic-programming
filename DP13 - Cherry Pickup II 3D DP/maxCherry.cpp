#include <bits/stdc++.h> 
using namespace std;

/**
 * Memoization - 
 * TC - O(N x M x M x 9)
 * SC - O(N) + O(N x M x M)
*/

int pickup(int i, int j1, int j2, int n, int m, vector<vector<int>> grid, vector<vector<vector<int>>> &dp){
    if(j1 < 0 || j1 >= m || j2 < 0 || j2 >= m) return -1e8;
    if(i == n-1){
        if(j1 == j2){
            return grid[i][j1];
        } else {
            return grid[i][j1] + grid[i][j2];
        }
    }
    if(dp[i][j1][j2] != -1){
        return dp[i][j1][j2];
    }

    int maxi = INT_MIN;
    for(int dj1 = -1;dj1<=1;dj1++){
        for(int dj2 = -1;dj2<=1;dj2++){
            int call = pickup(i + 1, j1 + dj1, j2 + dj2, n, m, grid, dp);
            if(j1 == j2){
                maxi = max(maxi, grid[i][j1] + call);
            } else {
                maxi = max(maxi, grid[i][j1] + grid[i][j2] + call);
            }
        }
    }
    return dp[i][j1][j2] = maxi;
}

int maximumChocolates1(int r, int c, vector<vector<int>> &grid) {

    vector<vector<vector<int>>> dp(r, vector<vector<int>> (c, vector<int> (c, -1)));
    
    return pickup(0, 0, c-1, r, c, grid, dp);
}

/**
 * Tabulation - 
 * TC - O(N x M x M x 9)
 * SC - O(N x M x M)
*/

int maximumChocolates2(int n, int m, vector<vector<int>> &grid) {
    vector<vector<vector<int>>> dp(n, vector<vector<int>> (m, vector<int> (m, -1)));
    for(int j1 = 0;j1<m;j1++){
        for(int j2 = 0;j2<m;j2++){
            if(j1 == j2){
                dp[n-1][j1][j2] = grid[n-1][j1];
            } 
            else dp[n-1][j1][j2] = grid[n-1][j1] + grid[n-1][j2];
        }
    }
    for(int i = n-2;i>=0;i--){
        for(int j1 = 0;j1<m;j1++){
            for(int j2 = 0;j2<m;j2++){
                
                int maxi = -1e8;

                for(int di = -1;di<=1;di++){
                    for(int dj = -1;dj<=1;dj++){
                        int value = 0;
                        if(j1 == j2){
                            value = grid[i][j1];
                        } else {
                            value = grid[i][j2] + grid[i][j1];
                        }
                        if(j1 + di < 0 || j1 + di >= m || j2 + dj < 0 || j2 + dj >= m){
                            value += -1e8;
                        } else {
                            value += dp[i+1][j1+di][j2+dj];
                        }
                        maxi = max(maxi, value);
                    }
                }
                dp[i][j1][j2] = maxi;
            }
        }
    }
    return dp[0][0][m-1];
}

/**
 * Space Optimisation - 
 * TC - O(N x M x M x 9)
 * SC - O(M x M)
*/

int maximumChocolates3(int n, int m, vector<vector<int>> &grid) {
    vector<vector<int>> front(m, vector<int> (m, -1));
    vector<vector<int>> cur(m, vector<int> (m, -1));
    
    for(int j1 = 0;j1<m;j1++){
        for(int j2 = 0;j2<m;j2++){
            if(j1 == j2){
                front[j1][j2] = grid[n-1][j1];
            } 
            else front[j1][j2] = grid[n-1][j1] + grid[n-1][j2];
        }
    }
    for(int i = n-2;i>=0;i--){
        for(int j1 = 0;j1<m;j1++){
            for(int j2 = 0;j2<m;j2++){
                
                int maxi = -1e8;

                for(int di = -1;di<=1;di++){
                    for(int dj = -1;dj<=1;dj++){
                        int value = 0;
                        if(j1 == j2){
                            value = grid[i][j1];
                        } else {
                            value = grid[i][j2] + grid[i][j1];
                        }
                        if(j1 + di < 0 || j1 + di >= m || j2 + dj < 0 || j2 + dj >= m){
                            value += -1e8;
                        } else {
                            value += front[j1+di][j2+dj];
                        }
                        maxi = max(maxi, value);
                    }
                }
                cur[j1][j2] = maxi;
            }
        }
        front = cur;
    }
    return front[0][m-1];
}

int main(){
    vector<vector<int>> grid = {{2,3,1,2},
    {3,4,2,2},
    {5,6,3,5}};

    cout << maximumChocolates1(3,4,grid);
}