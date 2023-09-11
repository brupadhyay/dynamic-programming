#include <bits/stdc++.h> 
using namespace std;


int mod = (int)1e9+7;

/**
 * Memoization
 * Time Complexity - O(N x totalSum)
 * Space Complexity - O(N) + O(N x totalSum)
*/

int checkSum(int i, int sum, int totalSum, int n, int d, vector<int> arr, vector<vector<int>> &dp){
    if(i >= n){
        int firstHalf = sum;
        int secondHalf = totalSum - firstHalf;
        if(firstHalf >= secondHalf){
            return (firstHalf - secondHalf) == d;
        }
        return 0;
    }

    if(dp[i][sum] != -1) return dp[i][sum];

    int take = checkSum(i+1,sum+arr[i],totalSum,n,d,arr,dp);
    int notTake = checkSum(i+1,sum,totalSum,n,d,arr,dp);
    return dp[i][sum] = (take + notTake)%mod;
}


int countPartitions1(int n, int d, vector<int> &arr) {
    int totalSum = 0;
    for(auto &x: arr) totalSum += x;
    
    vector<vector<int>> dp(n, vector<int> (totalSum + 1, -1));

    return checkSum(0, 0, totalSum, n, d, arr, dp);
}

/**
 * Tabulation
 * Time Complexity - O(N x target)
 * Space Complexity - O(N x target)
*/

int findWays0(vector<int>& arr, int k)
{
	int n = arr.size();
	vector<vector<int>> dp(n,vector<int> (k+1, 0));

	if(arr[n-1] == 0) dp[n-1][0] = 2;
	else dp[n-1][0] = 1;

	if(arr[n-1] != 0 && arr[n-1] <= k) dp[n-1][arr[n-1]] = 1;
	for(int i = n-2;i>=0;i--){
		for(int j = 0;j<=k;j++){
			int take = 0;
			if(j >= arr[i]) take = dp[i+1][j-arr[i]];
			int notTake = dp[i+1][j];
			dp[i][j] = (take + notTake)%mod;
		}
	}
	return dp[0][k];
}
int countPartitions2(int n, int d, vector<int> &arr) {
    int totalSum = 0;
    for(auto &x: arr) totalSum += x;
    if(totalSum - d < 0 || (totalSum - d)%2) return 0;

    return findWays0(arr, (totalSum - d)/2);
}

/**
 * Space Optimisation 
 * Time Complexity - O(N x target)
 * Space Complexity - O(target)
*/

int findWays1(vector<int>& arr, int k)
{
	int n = arr.size();
	vector<int> front(k+1,0);
	vector<int> cur(k+1,0);

	if(arr[n-1] == 0) front[0] = 2;
	else front[0] = 1;

	if(arr[n-1] != 0 && arr[n-1] <= k) front[arr[n-1]] = 1;
	for(int i = n-2;i>=0;i--){
		for(int j = 0;j<=k;j++){
			int take = 0;
			if(j >= arr[i]) take = front[j-arr[i]];
			int notTake = front[j];
			cur[j] = (take + notTake)%mod;
		}
		front = cur;
	}
	return front[k];
}
int countPartitions3(int n, int d, vector<int> &arr) {
    int totalSum = 0;
    for(auto &x: arr) totalSum += x;
    if(totalSum - d < 0 || (totalSum - d)%2) return 0;

    return findWays1(arr, (totalSum - d)/2);
}


int main(){
    vector<int> arr = {1,1,1,1};
    int d = 0;
    int n = 4;
    cout << countPartitions3(n, d, arr);
}

