#include <bits/stdc++.h> 
using namespace std;

int solve(int i, int maxWeight, int n, vector<int> weight, vector<int> value, vector<vector<int>> &dp){
	if(maxWeight == 0) return 0;
	if(i >= n){
		return 0;
	}
	if(dp[i][maxWeight] != -1) return dp[i][maxWeight];
	
	int take = INT_MIN;
	if(weight[i] <= maxWeight){
		take = value[i] + solve(i+1, maxWeight - weight[i], n, weight, value, dp);
	}
	int notTake = 0 + solve(i+1, maxWeight, n, weight, value, dp);
	return dp[i][maxWeight] = max(take, notTake);
}

int knapsack1(vector<int> weight, vector<int> value, int n, int maxWeight) 
{
	vector<vector<int>> dp(n, vector<int> (maxWeight + 1, -1));
	return solve(0, maxWeight, n, weight, value, dp);	
}

int knapsack2(vector<int> weight, vector<int> value, int n, int maxWeight) 
{
	vector<vector<int>> dp(n+1, vector<int> (maxWeight + 1, 0));
	for(int i = n-1;i>=0;i--){
		for(int w = 0;w<=maxWeight;w++){
			int take = INT_MIN;
			if(weight[i] <= w){
				take = value[i] + dp[i+1][w - weight[i]];
			}
			int notTake = dp[i+1][w];
			dp[i][w] = max(take, notTake);
		}
	}
	return dp[0][maxWeight];
}

int knapsack3(vector<int> weight, vector<int> value, int n, int maxWeight) 
{
	vector<int> front(maxWeight+1, 0);
	vector<int> curr(maxWeight+1,0);
	
	for(int i = n-1;i>=0;i--){
		for(int w = 0;w<=maxWeight;w++){
			int take = INT_MIN;
			if(weight[i] <= w){
				take = value[i] + front[w - weight[i]];
			}
			int notTake = front[w];
			curr[w] = max(take, notTake);
		}
		front = curr;
	}
	return front[maxWeight];	
}

int knapsack4(vector<int> weight, vector<int> value, int n, int maxWeight) 
{
	vector<int> front(maxWeight+1, 0);
	
	for(int i = n-1;i>=0;i--){
		for(int w = maxWeight;w >= 0;w--){
			int take = INT_MIN;
			if(weight[i] <= w){
				take = value[i] + front[w - weight[i]];
			}
			int notTake = front[w];
			front[w] = max(take, notTake);
		}
	}
	return front[maxWeight];
}

int main(){
    vector<int> weight = {6, 5, 1, 5, 6, 5, 9};
    int n = 7;
    vector<int> value = {5,3,4,9,6,1,1};
    cout << "maximum steals value is "<< knapsack4(weight, value, n, 63);
}