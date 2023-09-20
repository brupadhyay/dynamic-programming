#include <bits/stdc++.h>
using namespace std;

/**
 * Memoization - Top-Down
 * TC - O(N x N)
 * SC - O(N x N) + O(N)
*/

int solve(int i, int size, int n, vector<int> price, vector<vector<int>> &dp){
	if(i == n-1){
		// size -> 0, required = n standing at lengthOfRod = n
		// we return price at last index
		if(size == 0) return price[n-1];
		return 0;
	}

	if(dp[i][size] != -1) return dp[i][size];

	int notTake = solve(i+1, size, n, price, dp);
	int take = 0;
	if(size + (i+1) <= n) 
		take = price[i] + solve(i, size + (i+1), n, price, dp);
	
	return dp[i][size] = max(notTake, take);
}

int cutRod1(vector<int> &price, int n)
{
	vector<vector<int>> dp(n, vector<int> (n+1, -1));
	return solve(0, 0, n, price, dp);
}

/**
 * Tabulation - Bottom-Up
 * TC - O(N x N)
 * SC - O(N x N)
*/

int cutRod2(vector<int> &price, int n)
{
	vector<vector<int>> dp(n+1, vector<int> (n+1, 0));
	for(int i = n-1;i>=0;i--){
		// ? why from n to 0 because for lower values
		// ? we need the previous computed values in the same row
		for(int s = n;s>=0;s--){
			int notTake = dp[i+1][s];
			int take = 0;
			if(s + i + 1 <= n){
				// * important
				take = price[i] + dp[i][s+i+1];
			}
			dp[i][s] = max(take, notTake);
		}
	}
	return dp[0][0];
}

/**
 * Space Optimisation - Bottom-Up
 * TC - O(N x N)
 * SC - O(2 x N)
*/

int cutRod3(vector<int> &price, int n)
{
	vector<int> curr(n+1,0);
	vector<int> front(n+1,0);
	for(int i = n-1;i>=0;i--){
		for(int s = n;s>=0;s--){
			int notTake = front[s];
			int take = 0;
			if(s + i + 1 <= n){
				take = price[i] + curr[s+i+1];
			}
			curr[s] = max(take, notTake);
		}
		front = curr;
	}
	return front[0];
}

/**
 * 1D Array Space Optimisation - Bottom-Up
 * TC - O(N x N)
 * SC - O(N)
*/


int cutRod4(vector<int> &price, int n)
{
	vector<int> curr(n+1,0);
	for(int i = n-1;i>=0;i--){
		for(int s = n;s>=0;s--){
			int notTake = curr[s];
			int take = 0;
			if(s + i + 1 <= n){
				take = price[i] + curr[s+i+1];
			}
			curr[s] = max(take, notTake);
		}
	}
	return curr[0];
}

int main(){
    vector<int> price = {2,5,7,8,10};
    cout << "maximum cost of cutting - " << cutRod4(price, price.size());
}