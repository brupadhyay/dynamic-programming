#include <bits/stdc++.h> 
using namespace std;

/**
 * Memoization -
 * Time Complexity: O(N*N)
 * Space Complexity: O(N) + O(N*N)
 * Reason: We are using a recursion stack space: O((N), 
 * where N is the path length and an external DP Array of size ‘N*N’.
*/

int minSum(int i, int j, vector<vector<int>> triangle, int n, vector<vector<int>> &dp){
	if(i == n-1) return triangle[i][j];
	if(i >= n || j >= triangle[i].size()) return 1e9;
	if(dp[i][j] != 1e9) return dp[i][j];

	int down = triangle[i][j] + minSum(i+1,j,triangle,n, dp);
	int right = triangle[i][j] + minSum(i+1,j+1, triangle,n, dp);
	return dp[i][j] = min(down,right);
}

int minimumPathSum1(vector<vector<int>>& triangle, int n){
	vector<vector<int>> dp(n, vector<int> (n, 1e9));
	return minSum(0, 0, triangle, n, dp);
}

/**
 * Tabulation -
 * Time Complexity: O(N*N)
 * Space Complexity: O(N*N)
 * Reason: external DP Array of size ‘N*N’.
*/

int minimumPathSum2(vector<vector<int>>& triangle, int n){
	vector<vector<int>> dp(n, vector<int> (n, 1e9));
	for(int i = n-1;i>=0;i--){
		int colsize = triangle[i].size();
		for(int j = colsize-1;j>=0;j--){
			if(i == n-1){
				dp[i][j] = triangle[i][j];
			} else {
				int down = 1e9;
				int diagonal = 1e9;
                // check if just below element is good to take
				if(i + 1 < n){
					down = dp[i+1][j];
				}
                // check if diagonal element is safe
				if(i + 1 < n && j + 1 < triangle[i+1].size()){
					diagonal = dp[i+1][j+1];
				}
                // add current cell value and minimal of bottom and diagonal
				dp[i][j] = triangle[i][j] + min(down, diagonal);
			}
		}
	}
	return dp[0][0];
}

/**
 * Space Optimisation -
 * TC - O(NxN)
 * SC - O(N) { space required for next and curr array }
*/

int minimumPathSum3(vector<vector<int>>& triangle, int n){
	vector<int> next(n, 1e9);
	for(int i = n-1;i>=0;i--){
		int colsize = triangle[i].size();
		vector<int> curr(colsize, 1e9);
		for(int j = colsize-1;j>=0;j--){
			if(i == n-1){
				curr[j] = triangle[i][j];
			} else {
				int bottom = 1e9;
				int diagonal = 1e9;
				if(i + 1 < n){
					bottom = next[j];
				}
				if(i + 1 < n && j + 1 < triangle[i+1].size()){
					diagonal = next[j+1];
				}
				curr[j] = triangle[i][j] + min(bottom, diagonal);
			}
		}
		next = curr;
	}
	return next[0];
}

int main(){
    vector<vector<int>> triangle = {{1},
    {2,3},
    {3,6,7},
    {8,9,6,10}};
    cout << "minimum path sum is "<< minimumPathSum2(triangle, 4);
}