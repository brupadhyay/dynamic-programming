#include <bits/stdc++.h> 
using namespace std;

/**
 * Memoization - Top Down
 * TC - O(N x target)
 * SC - O(N) + O(N x target)
*/

bool checkSum(int ind, int n, int k, vector<int> arr, vector<vector<int>> &dp){
    if(k == 0) return true;
    if(ind >= n) return k == 0;
    if(dp[ind][k] != -1) return dp[ind][k];

    bool pick = false;
    if(k >= arr[ind]) pick = checkSum(ind + 1, n, k - arr[ind], arr, dp);
    bool nonpick = checkSum(ind + 1, n, k, arr, dp);
    return dp[ind][k] = pick || nonpick;
}

bool subsetSumToK1(int n, int k, vector<int> &arr) {
    vector<vector<int>> dp(n, vector<int> (k+1, -1));
    return checkSum(0, n, k, arr, dp);
}


/**
 * Tabulation - Bottom - Up
 * TC - O(N x target)
 * SC - O(N x target)
*/


bool subsetSumToK2(int n, int k, vector<int> &arr) {
    vector<vector<bool>> dp(n, vector<bool> (k+1, 0));

    for(int i = 0;i<n;i++){
        dp[i][0] = true; 
    }
    dp[n-1][arr[n-1]] = true;

    for(int i = n-2;i>=0;i--){
        for(int target = 1;target<=k;target++){
            bool pick = false;
            if(target >= arr[i]) pick = dp[i+1][target-arr[i]];
            bool nonpick = dp[i+1][target];
            dp[i][target] = pick || nonpick;
        }
    }
    return dp[0][k];
}


/**
 * Space Optimisation -
 * TC - O(N x target)
 * SC - O(target)
*/

bool subsetSumToK3(int n, int k, vector<int> &arr) {
    vector<bool> front(k+1,0);
    vector<bool> cur(k+1,0);

    front[arr[n-1]] = true; // if arr[n-1] == k, then it's true
    front[0] = cur[0] = true; // for anyone target = 0 is true

    for(int i = n-2;i>=0;i--){
        for(int target = 1;target<=k;target++){
            bool pick = false;
            if(target >= arr[i]) pick = front[target - arr[i]];
            bool nonpick = front[target];
            cur[target] = pick || nonpick;
        }
        front = cur;
    }
    return front[k];
}


int main(){
    vector<int> arr = {4,3,2,1};
    int k = 5;
    int n = 4;
    cout << "is subset present with sum equals k: " << subsetSumToK2(n, k, arr);
}