#include <bits/stdc++.h>
using namespace std;

// * TC - O(2^n) SC - O(n)
int fib(int n){
    if(n <= 1) return n;

    return fib(n-1) + fib(n-2);
}

/**
 * Memoization Code - using dp array of size (n + 1)
 * TC - O(N) { linearity in recursive tree }
 * SC - O(N) + O(N) { rec. stack space and dp array }
*/

int memoizedFib(int n, vector<int> &dp){
    if(n <= 1) return n;

    if(dp[n] != -1) return dp[n];

    return dp[n] = memoizedFib(n-1, dp) + memoizedFib(n-2, dp);
}

/**
 * Tabulation - Using Base Cases
 * TC - O(N)
 * SC - O(N) { eliminated recursive stack space }
*/

void tabulation(int n, vector<int> dp){
    dp[0] = 0;
    dp[1] = 1;

    for(int i = 2;i<=n;i++){
        dp[i] = dp[i-1] + dp[i-2];
    }
    cout << dp[n] << endl;
}


int main(){
    int n = 8;
    vector<int> dp(n + 1, -1);
    // cout << memoizedFib(n, dp);

    // tabulation(n, dp);  

    int prev1 = 0;
    int prev2 = 1;
    for(int i = 2;i<=n;i++){
        int next = prev1 + prev2;
        prev1 = prev2;
        prev2 = next;
    }  
    cout << prev2 << endl;

    return 0;
}