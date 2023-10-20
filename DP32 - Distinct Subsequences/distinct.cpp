#include <bits/stdc++.h>
using namespace std;

/**
 * Memoization - Top-Down
 * Time Complexity: O(N*M)
 * Reason: There are two nested loops for memoization 
 * Space Complexity: O(N*M) + O(N + M)
 * Reason: We are using an external array of size (N*M) and recursive stack space.
*/

int mod = (int)1e9+7;

int count(int i, int j, int n, int m, string &str, string &sub, vector<vector<int>> &dp)
{
	if(j >= m) return 1;
	if(i >= n) return 0;
	
	if(dp[i][j] != -1) return dp[i][j];

	if(str[i] == sub[j]){
		return dp[i][j] = (count(i+1,j+1,n,m,str,sub,dp) + count(i+1,j,n,m,str,sub,dp))%mod;
	}
	return dp[i][j] = count(i+1, j, n, m, str, sub, dp)%mod;
}

int distinctSubsequences1(string &str, string &sub)
{
	int n = str.length();
	int m = sub.length();
	vector<vector<int>> dp(n, vector<int> (m, -1));
	return count(0, 0, n, m, str, sub, dp)%mod;
}
/**
 * Tabulation - Bottom-Up
 * Time Complexity: O(N*M) + O(N) { for pre-filling }
 * Reason: There are two nested loops for tabulation 
 * Space Complexity: O(N*M)
 * Reason: We are using an external array of size (N*M).
*/

int distinctSubsequences2(string &str, string &sub)
{
	int n = str.length();
	int m = sub.length();
	vector<vector<int>> dp(n + 1, vector<int> (m + 1, 0));

	// i can be anything from 0...n
	for(int i = 0;i<=n;i++){
		dp[i][m] = 1;
	}

	for(int i = n-1; i >= 0; i--){
		for(int j = m-1; j >= 0; j--){
			if(str[i] == sub[j]){
				dp[i][j] = dp[i+1][j+1] + dp[i+1][j];
			} else dp[i][j] = dp[i+1][j];
		}
	}
	return dp[0][0];
}

/**
 * Space Optimisation - 2 x 1D Array
 * TC - O(N x M)
 * SC - O(M) + O(M)
*/

int distinctSubsequences3(string &str, string &sub)
{
	int n = str.length();
	int m = sub.length();
	vector<int> front(m + 1, 0);
	vector<int> curr(m + 1, 0);
	
	front[m] = curr[m] = 1;
	
	for(int i = n-1; i >= 0; i--){
		for(int j = m-1; j >= 0; j--){
			if(str[i] == sub[j]){
				curr[j] = (front[j+1] + front[j])%mod;
			} else curr[j] = front[j];
		}
		front = curr;
	}
	return front[0];
}
/**
 * Single Array Space Optimisation - 1D Array
 * TC - O(N x M)
 * SC - O(M)
*/

int distinctSubsequences4(string &str, string &sub)
{
	int n = str.length();
	int m = sub.length();
	vector<int> front(m + 1, 0);
	
	front[m] = 1;
	
	for(int i = n-1; i >= 0; i--){
		// why j from 0 to m-1 because
		// j + 1 means curr[j] depends on front's (j + 1 and j)
		// so if we update j + 1 value then it would lead
		// to uncertainty in summation
		for(int j = 0; j < m; j++){
			if(str[i] == sub[j]){
				front[j] = (front[j+1] + front[j])%mod;
			}
		}
	}
	return front[0];
}