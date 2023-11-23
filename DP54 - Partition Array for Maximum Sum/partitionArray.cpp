#include <bits/stdc++.h>
using namespace std;

int f(int i, int n, vector<int> &arr, int k, vector<int> &dp){
    // Base case: If the current index is equal to the size of the array, return 0.
    if(i == n) return 0;
    if(dp[i] != -1) return dp[i];
    int maxCost = -1e9;
    int maxi = -1e9;
    int len = 0;
    // Loop through the array starting from the current index.
    for(int j = i; j < min(i + k, n); j++){
        len++;
        maxi = max(maxi, arr[j]);
        int cost = maxi*len + f(j+1, n, arr, k, dp);
        maxCost = max(maxCost, cost);
    }
    // Store the computed result in the dp array and return it.
    return dp[i] = maxCost;
}

int maxSumAfterPartitioning1(vector<int>& arr, int k) {
    int n = arr.size();
    vector<int> dp(n, -1);
    return f(0, n, arr, k, dp);
}

int maxSumAfterPartitioning2(vector<int>& arr, int k) {
    int n = arr.size();
    vector<int> dp(n+1, 0);
    for(int i = n-1; i >= 0; i--){
        int maxCost = -1e9;
        int maxi = -1e9;
        int len = 0;
        for(int j = i; j < min(i + k, n); j++){
            len++;
            maxi = max(maxi, arr[j]);
            int cost = maxi*len + dp[j+1];
            maxCost = max(maxCost, cost);
        }
        dp[i] = maxCost;
    }
    return dp[0];
}


int main() {
    vector<int> num = {1, 15, 7, 9, 2, 5, 10};
    int k = 3;
    int maxSum = maxSumAfterPartitioning2(num, k);
    cout << "The maximum sum is: " << maxSum << "\n";
    return 0;
}
