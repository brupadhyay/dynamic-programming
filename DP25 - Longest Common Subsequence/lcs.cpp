#include <bits/stdc++.h>
using namespace std;

/**
 * Memoization - Top - Down
 * TC - O(N x M)
 * SC - O(N x M) + O(N + M)
*/

int solve(int i1, int i2, string s, string t, vector<vector<int>> &dp){
	if(i1 >= s.size() || i2 >= t.size()) return 0;
	if(dp[i1][i2] != -1e8) return dp[i1][i2];
	// match or not match
	int match = 0;
	if(s[i1] == t[i2]){
		match = 1 + solve(i1+1,i2+1, s, t, dp);
	}
	int notmatch = max(solve(i1,i2+1, s, t, dp) , solve(i1+1,i2,s,t, dp));
	return dp[i1][i2] = max(match, notmatch);
}
int lcs1(string s, string t)
{
	int n = s.size(), m = t.size();
	vector<vector<int>> dp(n, vector<int> (m, -1e8));
	return solve(0, 0, s, t, dp);
}


/**
 * Tabulation - Bottom - Up
 * TC - O(N x M)
 * SC - O(N + M) { dp matrix }
*/

int lcs2(string s, string t)
{
	int n = s.size(), m = t.size();
	vector<vector<int>> dp(n+1, vector<int> (m+1, 0));
	for(int i = n-1; i >= 0; i--){
		for(int j = m-1; j >= 0; j--){
			if(s[i] == t[j]){
				dp[i][j] = 1 + dp[i+1][j+1];
			} else {
                dp[i][j] = max(dp[i+1][j], dp[i][j+1]);
            }
		}
	}
	return dp[0][0];
}

/**
 * Space Optimisation - Top-Down
 * TC - O(N x M)
 * SC - O(2 x M) { 1D Optimisation }
*/

int lcs3(string s, string t)
{
	int n = s.size(), m = t.size();
	vector<int> front(m+1, 0);
	vector<int> curr(m+1, 0);
	for(int i = n-1; i >= 0; i--){
		for(int j = m-1; j >= 0; j--){
			if(s[i] == t[j]){
				curr[j] = 1 + front[j+1];
			} else curr[j] = max(curr[j+1], front[j]);;
		}
		front = curr;
	}
	return front[0];
}