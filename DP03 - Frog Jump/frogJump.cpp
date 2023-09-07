#include <bits/stdc++.h>
using namespace std;

/**
 * Memoization - Top_Down Approach
 * TC - O(N) { linearity in depth }
 * SC - O(N) { for recursive stack space } + O(N) { dp array }
*/

int jump(int ind, vector<int> &heights, vector<int> &dp){
    if(ind == 0) return 0;
    if(dp[ind] != -1) return dp[ind];
    
    int left = jump(ind - 1, heights, dp) + abs(heights[ind - 1] - heights[ind]);
    int right = INT_MAX;
    if(ind > 1){
        right = jump(ind - 2, heights, dp) + abs(heights[ind - 2] - heights[ind]);
    }    
    return dp[ind] = min(left, right);
}

int frogJump(int n, vector<int> &heights)
{
    vector<int> dp(n, -1);
    return jump(n-1, heights, dp);
}

/**
 * Tabulation - Bottom-Up Approach
 * TC - O(N) { for-loop }
 * SC - O(N) { using auxiliary space for dp array }
*/

int frogJump(int n, vector<int> &heights)
{
    vector<int> dp(n, INT_MAX);
    dp[0] = 0;
    for(int i = 1;i<n;i++){
        int step1 = abs(heights[i] - heights[i-1]);
        int step2 = INT_MAX;
        if(i > 1){
            step2 = abs(heights[i] - heights[i-2]);
            dp[i] = step2 + dp[i-2];
        }
        dp[i] = min(dp[i], step1 + dp[i-1]);
    }
    return dp[n-1];
}

/**
 * Space Optimisation - Using only variables
 * TC - O(N) { Reason: We are running a simple iterative loop }
 * SC - O(1)
*/

int frogJump(int n, vector<int> &heights)
{
    int twoBack = 0;
    int oneBack = abs(heights[1] - heights[0]);
    for(int i = 2;i<n;i++){
        int step1 = abs(heights[i] - heights[i-1]);
        int step2 = abs(heights[i] - heights[i-2]);
        int curr = min(oneBack + step1, twoBack + step2);
        twoBack = oneBack;
        oneBack = curr;
    }
    return oneBack;
}

int main(){
    vector<int> heights = {30,10,60,10,60,50};
    int n = heights.size();
    cout << frogJump(n, heights) << endl;
}