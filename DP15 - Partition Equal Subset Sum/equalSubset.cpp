#include <bits/stdc++.h> 
using namespace std;

/**
 * Memoization - Top-Down
 * TC - O(N) + O(N x target)
 * SC - O(N) + O(N x target)
 * where target is total sum/2
*/

bool checkSum(int ind, int target, vector<int> &arr, int n, vector<vector<int>> &dp){
	if(target == 0) return true;
	if(ind >= n) return target == 0;
	if(dp[ind][target] != -1) return dp[ind][target];

	bool pick = false;
	if(target >= arr[ind]) pick = checkSum(ind+1, target-arr[ind], arr, n, dp);
	bool nonpick = checkSum(ind+1, target, arr, n, dp);
	return dp[ind][target] = pick || nonpick;
}

bool canPartition1(vector<int> &arr, int n)
{
	int sum = 0;
	for(int &x: arr) 
		sum += x;

	
	vector<vector<int>> dp(n, vector<int> (sum/2 + 1, -1));

    // if total sum is odd, then we can't partition into two subsets
	if(sum % 2 == 1) return false;
	return checkSum(0, sum/2, arr, n, dp);
}

/**
 * Space Optimisation
 * TC - O(N) + O(N x target)
 * SC - O(target)
*/

bool checkSum(int n, int k, vector<int> &arr) {
    vector<bool> front(k+1,0);
    vector<bool> cur(k+1,0);

    front[arr[n-1]] = true; // if arr[n-1] == k, then it's true
    front[0] = cur[0] = true; // for anyone target = 0 is true

    for(int i = n-2;i>=0;i--){
        for(int target = 1;target<=k;target++){
            bool pick = false;
            if(target >= arr[i]) pick = front[target - arr[i]];
            bool nonpick = front[target];
            cur[target] = pick || nonpick;
        }
        front = cur;
    }
    return front[k];
}


bool canPartition2(vector<int> &arr, int n)
{
	int sum = 0;
	for(int &x: arr) 
		sum += x;

    // if total sum is odd, then we can't partition into two subsets
	if(sum % 2 == 1) return false;
	return checkSum(n, sum/2, arr);
}
