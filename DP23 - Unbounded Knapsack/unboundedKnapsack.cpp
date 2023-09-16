
#include <bits/stdc++.h>
using namespace std;

/**
 * Memoization - Top_Down
 * TC - O(N x W)
 * SC - O(W) + O(N x W)
*/


int knapsack(int i, int w, int n, vector<int> &profit, vector<int> &weight, vector<vector<int>> &dp){
    // base cases
    if(i >= n){
        return 0;
    }
    if(dp[i][w] != -1) return dp[i][w];

    // recurrence
    int notTake = knapsack(i+1, w, n, profit, weight, dp);
    int take = 0;
    if(weight[i] <= w){
        take = profit[i] + knapsack(i, w-weight[i], n, profit, weight, dp);
    }

    // result
    return dp[i][w] = max(take, notTake);
}

int unboundedKnapsack1(int n, int w, vector<int> &profit, vector<int> &weight){
    vector<vector<int>> dp(n, vector<int> (w+1, -1));
    return knapsack(0, w, n, profit, weight, dp);
}

/**
 * Tabulation - Bottom_Up
 * TC - O(N x W)
 * SC - O(N x W)
*/


int unboundedKnapsack2(int n, int w, vector<int> &profit, vector<int> &weight){
    vector<vector<int>> dp(n+1, vector<int> (w+1, -1));

    for(int i = n-1;i>=0;i--){
        for(int wt = 0;wt<=w;wt++){
            int notTake = dp[i+1][wt];
            int take = 0;
            if(weight[i] <= wt){
                take = profit[i] + dp[i][wt-weight[i]];
            }
            dp[i][wt] = max(take, notTake);
        }
    }
    return dp[0][w];
}


/**
 * Space Optimisation - Bottom_Up
 * TC - O(N x W)
 * SC - O(2 x W)
*/

int unboundedKnapsack3(int n, int w, vector<int> &profit, vector<int> &weight){
    vector<int> front(w+1,0), curr(w+1,0);

    for(int i = n-1;i>=0;i--){
        for(int wt = 0;wt<=w;wt++){
            int notTake = front[wt];
            int take = 0;
            if(weight[i] <= wt){
                take = profit[i] + curr[wt-weight[i]];
            }
            curr[wt] = max(take, notTake);
        }
        front = curr;
    }
    return front[w];
}


/**
 * Single Array Space Optimisation - Bottom_Up
 * TC - O(N x W)
 * SC - O(W)
*/

int unboundedKnapsack4(int n, int w, vector<int> &profit, vector<int> &weight){
    vector<int> curr(w+1,0);

    for(int i = n-1;i>=0;i--){
        for(int wt = 0;wt<=w;wt++){
            int notTake = curr[wt];
            int take = 0;
            if(weight[i] <= wt){
                take = profit[i] + curr[wt-weight[i]];
            }
            curr[wt] = max(take, notTake);
        }
    }
    return curr[w];
}

int main(){
    int n = 3;
    int w = 10;
    vector<int> profit = {5,11,13};
    vector<int> weight = {2,4,6};

    cout << unboundedKnapsack4(n,w,profit,weight);
}
