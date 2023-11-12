#include <bits/stdc++.h>
using namespace std;

/**
 * Bitonic means Increasing then decreasing
 * or strictly increasing or strictly decreasing
 * TC - O(N x N) x 2
 * SC - O(N) x 2
*/

int longestBitonicSubsequence(vector<int>& arr, int n)
{
	vector<int> dp1(n, 1);
	vector<int> dp2(n, 1);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < i; j++){
			if(arr[i] > arr[j] && dp1[i] < 1 + dp1[j]){
				dp1[i] = 1 + dp1[j];
			}
		}
	}
	for(int i = n-1; i >= 0; i--){
		for(int j = n-1; j > i; j--){
			if(arr[i] > arr[j] && dp2[i] < 1 + dp2[j]){
				dp2[i] = 1 + dp2[j];
			}
		}
	}
	int bitonic = 0;
	for(int i = 0; i < n; i++){
		bitonic = max(bitonic, dp1[i] + dp2[i] - 1);
	}
	return bitonic;
}


int main(){
    vector<int> arr = {1, 11, 2, 10, 4, 5, 2, 1};
    // * longest bitonic is {1, 11, 10, 4, 2, 1}
    cout << "length of lbs is " << longestBitonicSubsequence(arr, arr.size());
}