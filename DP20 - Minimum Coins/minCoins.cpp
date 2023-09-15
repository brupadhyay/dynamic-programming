#include <bits/stdc++.h> 
using namespace std;

/**
 * Memoization - 
 * TC - O(N x target)
 * SC - O(N x target) + O(target)
*/

int solve(int i, int x, vector<int> num, int n, vector<vector<int>> &dp){
    if(i == n-1){
        if(x % num[i] == 0) return x/num[i];
        return 1e8;
    }

    if(dp[i][x] != -1) return dp[i][x];

    int notTake = 0 + solve(i+1, x, num, n, dp);
    int take = INT_MAX;
    if(num[i] <= x){
        take = 1 + solve(i, x - num[i], num, n, dp);
    }
    return dp[i][x] = min(take, notTake);
}

int minimumElements(vector<int> &num, int x)
{
    int n = num.size();
    vector<vector<int>> dp(n, vector<int> (x+1, -1));
    int ans = solve(0, x, num, n, dp);
    return ans == 1e8 ? -1: ans;
}

/**
 * Tabulation - Bottom-Up
 * TC - O(N x target)
 * SC - O(N x target)
*/

int minimumElements(vector<int> &num, int x)
{
    int n = num.size();
    vector<vector<int>> dp(n, vector<int> (x+1, 1e8));

    for(int t = 0;t<=x;t++){
        if(t%num[n-1] == 0) dp[n-1][t] = t/num[n-1];
        else dp[n-1][t] = 1e8;
    }

    for(int i = n-2;i>=0;i--){
        for(int t = 0;t<=x;t++){
            int notTake = dp[i+1][t];
            int take = INT_MAX;
            if(num[i] <= t){
                take = 1 + dp[i][t-num[i]];
            }
            dp[i][t] = min(take, notTake);
        }
    }
    return dp[0][x] == 1e8 ? -1 : dp[0][x];
}


/**
 * Space Optimisation - Bottom-Up
 * TC - O(N x target)
 * SC - O(2 x target)
*/

int minimumElements(vector<int> &num, int x)
{
    int n = num.size();
    vector<int> front(x+1, 1e8);
    vector<int> curr(x+1, 1e8);

    for(int t = 0;t<=x;t++){
        if(t%num[n-1] == 0) front[t] = t/num[n-1];
        else front[t] = 1e8;
    }

    for(int i = n-2;i>=0;i--){
        for(int t = 0;t<=x;t++){
            int notTake = front[t];
            int take = INT_MAX;
            if(num[i] <= t){
                take = 1 + curr[t-num[i]];
            }
            curr[t] = min(take, notTake);
        }
        front = curr;
    }
    return front[x] == 1e8 ? -1 : front[x];
}

/**
 * Single Array Space Optimisation - Bottom-Up
 * TC - O(N x target)
 * SC - O(target)
*/

int minimumElements(vector<int> &num, int x)
{
    int n = num.size();
    vector<int> curr(x+1, 1e8);

    for(int t = 0;t<=x;t++){
        if(t%num[n-1] == 0) curr[t] = t/num[n-1];
        else curr[t] = 1e8;
    }

    for(int i = n-2;i>=0;i--){
        for(int t = 0;t<=x;t++){
            int notTake = curr[t];
            int take = INT_MAX;
            if(num[i] <= t){
                take = 1 + curr[t-num[i]];
            }
            curr[t] = min(take, notTake);
        }
    }
    return curr[x] == 1e8 ? -1 : curr[x];
}