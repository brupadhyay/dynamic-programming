#include <bits/stdc++.h>
using namespace std;

/**
 * Memoization - Top_Down
 * TC - O(N x target)
 * SC - O(target) + O(N x target)
*/

long solve(int i, int n, int value, int *denominations, vector<vector<long>> &dp){
    if(i >= n){
        if(value == 0) return 1;
        return 0;
    }

    if(dp[i][value] != 0) return dp[i][value];

    int notTake = solve(i+1,n,value,denominations, dp);
    int take = 0;
    if(denominations[i] <= value){
        take = solve(i, n, value-denominations[i], denominations, dp);
    }
    return dp[i][value] = notTake + take;
}

long countWaysToMakeChange1(int *denominations, int n, int value)
{
    vector<vector<long>> dp(n, vector<long> (value + 1, 0));
    return solve(0, n, value, denominations, dp);
}

/**
 * Tabulation - Bottom_Up
 * TC - O(N x target)
 * SC - O(N x target)
*/

long countWaysToMakeChange2(int *denominations, int n, int value)
{
    vector<vector<long>> dp(n+1, vector<long> (value + 1, 0));

    dp[n][0] = 1;

    for(int i = n-1;i>=0;i--){
        for(int v = 0;v<=value;v++){
            int notTake = dp[i+1][v];
            int take = 0;
            if(denominations[i] <= v){
                take = dp[i][v-denominations[i]];
            }
            dp[i][v] = take + notTake;
        }
    }
    return dp[0][value];
}

/**
 * Space Optimisation - Bottom_Up
 * TC - O(N x target)
 * SC - O(2 x target)
*/

long countWaysToMakeChange3(int *denominations, int n, int value)
{
    vector<long> front(value + 1, 0);
    vector<long> curr(value + 1, 0);

    front[0] = curr[0] = 1;


    for(int i = n-1;i>=0;i--){
        for(int v = 0;v<=value;v++){
            int notTake = front[v];
            int take = 0;
            if(denominations[i] <= v){
                take = curr[v-denominations[i]];
            }
            curr[v] = take + notTake;
        }
        front = curr;
    }
    return front[value];
}

/**
 * Space Optimisation - Bottom_Up
 * TC - O(N x target)
 * SC - O(target)
*/

long countWaysToMakeChange4(int *denominations, int n, int value)
{
    vector<long> curr(value + 1, 0);
    curr[0] = 1;

    for(int i = n-1;i>=0;i--){
        for(int v = 1;v<=value;v++){
            if(denominations[i] <= v){
                curr[v] += curr[v - denominations[i]];
            }
        }
    }
    return curr[value];
}


int main(){
    int denominations[] = {1,2,3};
    int n = 3;
    int value = 4;
    cout << "ways = "<< countWaysToMakeChange4(denominations,n,value);
}