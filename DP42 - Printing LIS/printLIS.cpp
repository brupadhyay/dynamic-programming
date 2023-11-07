#include <bits/stdc++.h>
using namespace std;

vector<int> printingLongestIncreasingSubsequence(vector<int> arr, int n) {
	vector<int> dp(n, 1);
	int lastIndex = 0;
	int maxi = 0;
	vector<int> hash(n, 0);
	for(int i = 0; i < n; i++) hash[i] = i;
	for(int i = 0; i < n; i++){
		for(int prev = 0; prev < i; prev++){
			if(arr[i] > arr[prev]){
				if(1 + dp[prev] > dp[i]){
					dp[i] = 1 + dp[prev];
					hash[i] = prev;
				}
			}
		}
		if(dp[i] > maxi){
			maxi = dp[i];
			lastIndex = i;
		}
	}
	vector<int> lis;
	while(lastIndex != hash[lastIndex]){
		lis.push_back(arr[lastIndex]);
		lastIndex = hash[lastIndex];
	}
	lis.push_back(arr[lastIndex]);
	reverse(lis.begin(), lis.end());
	return lis;
}

int main(){
    vector<int> arr = {10, 9, 2, 5, 3, 7, 101, 18};
    int n = arr.size();
    vector<int> ans = printingLongestIncreasingSubsequence(arr, n);
    for(auto it: ans){
        cout << it << " ";
    }
}