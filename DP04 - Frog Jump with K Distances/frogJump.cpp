#include <bits/stdc++.h>
using namespace std;

/**
 * Recursive Solution
 * TC - exponential
*/

int jump(int ind, int k, vector<int> &heights){
    if(ind == 0) return 0;

    int bestPossible = INT_MAX;
    for(int j = 1;j<=k;j++){
        int currPossible = INT_MAX;
        if(ind - j >= 0) currPossible = jump(ind - j, k, heights) + abs(heights[ind] - heights[ind - j]);
        bestPossible = min(bestPossible, currPossible);
    }
    return bestPossible;
}

int frogJump1(int n, int k, vector<int> &heights){
    return jump(n-1, k, heights);
}

/**
 * Memoization - Top-down
 * TC - O(N*K)
 * SC - O(N) { recursive stack space } + O(N) { dp array }
*/
int jump(int ind, int k, vector<int> &heights, vector<int> &dp){
    if(ind == 0) return 0;
    if(dp[ind] != -1) return dp[ind]; // step 3 - overlapping subproblems

    int bestPossible = INT_MAX;
    for(int j = 1;j<=k;j++){
        int currPossible = INT_MAX;
        // * ind - j >= 0, otherwise you will be checking negative indices
        if(ind - j >= 0) currPossible = jump(ind - j, k, heights) + abs(heights[ind] - heights[ind - j]);
        bestPossible = min(bestPossible, currPossible);
    }
    return dp[ind] = bestPossible; // step 2
}


int frogJump2(int n, int k, vector<int> &heights){
    vector<int> dp(n+1, -1);
    return jump(n-1, k, heights, dp);
}

/**
 * Tabulation - Using Bottom-Up Approach
 * TC - O(N*K)
 * SC - O(N) { only dp array space }
*/

int frogJump3(int n, int k, vector<int> &heights){
    vector<int> dp(n + 1, -1);
    dp[0] = 0;
    for(int i = 1;i<n;i++){
        int currMinimum = INT_MAX;
        for(int j = 1;j<=k;j++){
            if(i - j >= 0){
                int jump = dp[i - j] + abs(heights[i] - heights[i - j]);
                currMinimum = min(currMinimum, jump);
            }
        }
        dp[i] = currMinimum;
    }
    return dp[n-1];
}

int main(){
    vector<int> heights = {40,10,20,70,80,10,20,70,80,60};
    int n = heights.size();
    int k = 4;
    cout << frogJump3(n, k, heights) << endl;
}