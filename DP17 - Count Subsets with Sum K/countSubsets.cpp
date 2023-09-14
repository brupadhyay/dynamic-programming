#include <bits/stdc++.h>
using namespace std;

int mod = (int)1e9+7;

/**
 * Memoization - Top-Down
 * TC - O(N x k)
 * SC - O(N x k) + O(N)
*/

int countUtil(int i, vector<int> arr, int k, int n, vector<vector<int>> &dp){
	if(dp[i][k] != -1) return dp[i][k];
	if(k == 0) return 1;
	if(i == n-1) return arr[n-1] == k ? 1 : 0;	

	int take = 0;
	if(k >= arr[i]) take = countUtil(i+1, arr, k-arr[i], n, dp);
	int notTake = countUtil(i+1, arr, k, n, dp);
	return dp[i][k] = (take + notTake)%mod;
}

int findWays1(vector<int>& arr, int k)
{
	int n = arr.size();
	vector<vector<int>> dp(n,vector<int> (k+1,-1));
	return countUtil(0, arr, k, n, dp);
}

/**
 * Tabulation - Bottom-Up
 * TC - O(N x k)
 * SC - O(N x k)
*/

int findWays2(vector<int>& arr, int k)
{
	int n = arr.size();
	vector<vector<int>> dp(n,vector<int> (k+1, 0));
	for(int i = 0;i<n;i++){
		dp[i][0] = 1;
	}
	if(arr[n-1] <= k) dp[n-1][arr[n-1]] = 1;
	for(int i = n-2;i>=0;i--){
		for(int target = 1;target<=k;target++){
			int take = 0;
			if(target >= arr[i]) take = dp[i+1][target-arr[i]];
			int notTake = dp[i+1][target];
			dp[i][target] = (take + notTake)%mod;
		}
	}
	return dp[0][k];
}

/**
 * Space Optimisation - 
 * TC - O(N x k)
 * SC - O(k)
*/

int findWays3(vector<int>& arr, int k)
{
	int n = arr.size();
	vector<int> front(k+1,0);
	vector<int> curr(k+1,0);
	front[0] = curr[0] = 1;
	if(arr[n-1] <= k) front[arr[n-1]] = 1;
    
	for(int i = n-2;i>=0;i--){
		for(int target = 1;target<=k;target++){
			int take = 0;
			if(target >= arr[i]) take = front[target-arr[i]];
			int notTake = front[target];
			curr[target] = (take + notTake)%mod;
		}
		front = curr;
	}
	return front[k];
}

int main(){
    vector<int> arr = {1,1,4,5};
    int k = 5;
    cout << "the number of ways which we can achieve sum = k are "<< findWays2(arr, k) << endl;
    return 0;
}
