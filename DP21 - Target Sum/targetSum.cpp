#include <bits/stdc++.h> 
using namespace std;

/*
    You are given an array 'ARR' of 'N' integers and a target
    number, 'TARGET'. Your task is to build an expression out of an
    array by adding one of the symbols '+' and '-' before each
    integer in an array, and then by concatenating all the integers,
    you want to achieve a target. You have to return the number of
    ways the target can be achieved.
*/

/**
 * Space Optimised
 * TC - O(N x target)
 * SC - O(target)
*/

int solve(vector<int> arr, int n, int d){
    vector<int> front(d + 1, 0);
    vector<int> curr(d + 1, 0);

    front[0] = curr[0] = 1;

    for(int i = n-1;i>=0;i--){
        for(int t = 1;t<=d;t++){
            int take = 0;
            if(arr[i] <= t){
                take = front[t - arr[i]];
            }
            int notTake = front[t];
            curr[t] = take + notTake;
        }
        front = curr;
    }
    return front[d];
}

int targetSum(int n, int target, vector<int>& arr) {
    int totSum = 0;
    for(int i = 0;i<n;i++){
        totSum += arr[i];
    }
    if(totSum - target < 0 || (totSum - target)%2) return 0;
    return solve(arr, n, (totSum - target)/2);
}
