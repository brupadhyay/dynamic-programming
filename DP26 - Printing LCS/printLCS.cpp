#include <bits/stdc++.h>
using namespace std;

/**
 * Memoization - Top-Down
 * TC - O(N x M)
 * SC - O(N x M) + O(N + M)
*/

string solve(int i1, int i2, string s1, string s2, vector<vector<string>> &dp){
	if(i1 >= s1.size() || i2 >= s2.size()) return "";
	if(dp[i1][i2] != "") return dp[i1][i2];

	if(s1[i1] == s2[i2]){
		return dp[i1][i2] = s1[i1] + solve(i1+1,i2+1,s1,s2,dp);
	}
	string notMatch1 = solve(i1, i2+1, s1, s2, dp);
	string notMatch2 = solve(i1+1, i2, s1, s2, dp);
	if(notMatch1.size() > notMatch2.size()) return dp[i1][i2] = notMatch1;
	return dp[i1][i2] = notMatch2;
}

string findLCS1(int n, int m,string &s1, string &s2){
	vector<vector<string>> dp(n, vector<string> (m, ""));
	return solve(0, 0, s1, s2, dp);
}

/**
 * Tabulation - Bottom-Up
 * TC - O(N x M)
 * SC - O(N x M) { dp array }
*/

string findLCS2(int n, int m,string &s1, string &s2){
	vector<vector<string>> dp(n+1, vector<string> (m+1, ""));
	for(int i1 = n-1; i1 >= 0; i1--){
		for(int i2 = m-1; i2 >= 0; i2--){
			if(s1[i1] == s2[i2]){
				dp[i1][i2] = s1[i1] + dp[i1+1][i2+1];
			} else {
				string notMatch1 = dp[i1][i2+1];
				string notMatch2 = dp[i1+1][i2];
				if(notMatch1.size() >= notMatch2.size()) dp[i1][i2] = notMatch1;
				else dp[i1][i2] = notMatch2;
			}
		}
	}
    // for(auto it: dp){
    //     for(auto x: it) cout << x << " ";
    //     cout << "\n";
    // }
	return dp[0][0];
}

/**
 * *Important
 * Tabulation + Backtracking - Bottom-Up then Top-Down
 * TC - O(N x M) + O(N + M)
 * SC - O(N x M)
*/

string findLCS3(int n, int m,string &s1, string &s2){
	vector<vector<int>> dp(n+1, vector<int> (m+1, 0));
	for(int i = n-1; i >= 0; i--){
		for(int j = m-1; j >= 0; j--){
			if(s1[i] == s2[j]){
				dp[i][j] = 1 + dp[i+1][j+1];
			} else {
                dp[i][j] = max(dp[i+1][j], dp[i][j+1]);
            }
		}
	}
	int len = dp[0][0];
	string ans;
	int i = 0, j = 0;
    // O(N + M)
	while(i < n && j < m){
		if(s1[i] == s2[j]){
			ans.push_back(s1[i]);
			i++;
			j++;
		} else if(dp[i+1][j] > dp[i][j+1]){
			i++;
		} else {
			j++;
		}
	}
	return ans;
}

int main(){
    string s1 = "abcab";
    string s2 = "cbab";
    cout << findLCS2(5,4,s1,s2);
}