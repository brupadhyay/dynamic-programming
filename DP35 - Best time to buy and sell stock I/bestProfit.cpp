#include <bits/stdc++.h> 
using namespace std;

/**
 * Optimal Approach
 * selling on ith day means 
 * we need to buy on a day previously with 
 * lower cost than current day
 * TC - O(N)
 * SC - O(1)
*/

int maximumProfit(vector<int> &prices){
    int profit = 0, mini = prices[0];
    for(int i = 1; i < prices.size(); i++){
        profit = max(profit, prices[i] - mini);
        mini = min(mini, prices[i]);
    }
    return profit;
}

int main(){
    vector<int> prices = {7,1,5,3,6,4};
    cout << "maximum profit is "<< maximumProfit(prices);
}