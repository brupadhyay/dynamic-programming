#include <bits/stdc++.h>
using namespace std;

/**
 * Memoization 
 * TC - O(N)
 * SC - O(N) + O(N)
*/

int count(int nStairs, vector<int> &dp){
    if(nStairs == 1) return 1;
    if(nStairs == 0) return 1;

    if(dp[nStairs] != -1) return dp[nStairs];
    
    return dp[nStairs] = count(nStairs - 1, dp) + count(nStairs - 2, dp);
}

int climbStairs(int nStairs) {
    vector<int> dp(nStairs + 1, -1);
    return count(nStairs, dp);
}

int climbStairs(int n) {
    // * Tabulation - using base cases to solve
    // * TC - O(N) SC - O(N)
    vector<int> dp(n + 1, -1);
    dp[0] = 1;
    dp[1] = 1;

    for(int i = 2;i<=n;i++){
        dp[i] = dp[i-1] + dp[i-2];
    }
    return dp[n];
}

/**
 * Space Optimisation - Using two variables
 * TC - O(N)
 * SC - O(1)
*/

int climbStairs(int n) {
    int prev1 = 1;
    int prev2 = 1;
    for(int i = 2;i<=n;i++){
        int next = prev1 + prev2;
        prev1 = prev2;
        prev2 = next;
    }
    return prev2;
}


int main(){
    int n = 5;
    cout << climbStairs(n) << endl;
}