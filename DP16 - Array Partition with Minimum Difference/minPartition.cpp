#include <bits/stdc++.h>
using namespace std;

int minDiff(int i, int sum, int totalSum, int n, vector<int> arr, vector<vector<int>> &dp){
	if(i >= n){
		return abs(totalSum - 2*sum);
	}

	if(dp[i][sum] != -1) return dp[i][sum];

	int pick = minDiff(i+1, sum + arr[i], totalSum, n, arr, dp);
	int nonpick = minDiff(i+1, sum, totalSum, n, arr, dp);
	return dp[i][sum] = min(pick, nonpick);
}

int minSubsetSumDifference1(vector<int>& arr, int n)
{
	int totalSum = 0;
	for(int x: arr) totalSum += x;

	vector<vector<int>> dp(n, vector<int> (totalSum + 1, -1));

	return minDiff(0, 0, totalSum, n, arr, dp);
}

void minDiff(int i, int totalSum, int n, vector<int> arr, vector<vector<bool>> &dp){
	for(int i = 0;i<n;i++){
		dp[i][0] = true;
	}
	dp[n-1][arr[n-1]] = true;
	for(int i = n-2;i>=0;i--){
		for(int t = 1;t<=totalSum;t++){
			bool take = false;
			if(arr[i] <= t) take = dp[i+1][t-arr[i]];
			bool notTake = dp[i+1][t];
			dp[i][t] = take || notTake;
		}
	}
}

int minSubsetSumDifference2(vector<int>& arr, int n)
{
	int totalSum = 0;
	for(int x: arr) totalSum += x;

	vector<vector<bool>> dp(n, vector<bool> (totalSum + 1, false));

	minDiff(0, totalSum, n, arr, dp);
	int mini = 1e9;
	for(int j = 0;j<=totalSum/2;j++){
		if(dp[0][j] == true){
			mini = min(mini, abs(totalSum - 2*j));
		}
	}
	return mini;
}


void minDiff(int i, int totalSum, int n, vector<int> arr, vector<bool> &front, vector<bool> &cur){
	
	front[0] = cur[0] = true;
	front[arr[n-1]] = true;

	for(int i = n-2;i>=0;i--){
		for(int t = 1;t<=totalSum;t++){
			bool take = false;
			if(arr[i] <= t) take = front[t-arr[i]];
			bool notTake = front[t];
			cur[t] = take || notTake;
		}
		front = cur;
	}
}

int minSubsetSumDifference3(vector<int>& arr, int n)
{
	int totalSum = 0;
	for(int x: arr) totalSum += x;

	vector<bool> front(totalSum + 1, false);
	vector<bool> cur(totalSum + 1, false);

	minDiff(0, totalSum, n, arr, front, cur);
	int mini = 1e9;
	for(int j = 0;j<=totalSum/2;j++){
		if(front[j] == true){
			mini = min(mini, abs(totalSum - 2*j));
		}
	}
	return mini;
}



int main(){
    vector<int> arr = {3,2,7};
    int n = 3;
    cout << "the minimum absolute difference in partition sum is "<< minSubsetSumDifference2(arr,n);
}