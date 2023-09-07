#include <bits/stdc++.h> 
using namespace std;

/**
 * Recurrence Relation - 
 * TC - O(3^days)
 * SC - O(day)
*/

int merits(int day, int last, vector<vector<int>> &points){
    // base case
    if(day == 0){
        int maxi = 0;
        for(int i = 0; i < 3; i++){
            if(i != last){
                maxi = max(maxi, points[day][i]);
            }
        }
        return maxi;
    }

    int maxMerits = 0;
    for(int i = 0; i < 3; i++){
        if(i != last){
            int meritEarned = points[day][i] + merits(day - 1, i, points);
            maxMerits = max(maxMerits, meritEarned);
        }
    }
    return maxMerits;
}

int ninjaTraining1(int n, vector<vector<int>> &points)
{
    return merits(n-1, 3, points);
}

/**
 * Memoization - Top-down approach
 * Changing parameters day and last so create a 2D DP Array of size [n][4]
 * since - 0,1,2,3 are possible activities
 * TC - O(N x 4 x 3) { since N x 4 states, and for each state we keep on iterating a for loop of 3 }
 * SC - O(N x 4) { dp array } + O(N) { stack space }
*/

int merits(int day, int last, vector<vector<int>> &points, vector<vector<int>> &dp){
    // base case
    if(day == 0){
        int maxi = 0;
        for(int i = 0; i < 3; i++){
            if(i != last){
                maxi = max(maxi, points[day][i]);
            }
        }
        return maxi;
    }
    if(dp[day][last] != -1) return dp[day][last];
    int maxMerits = 0;
    for(int i = 0; i < 3; i++){
        if(i != last){
            int meritEarned = points[day][i] + merits(day - 1, i, points, dp);
            maxMerits = max(maxMerits, meritEarned);
        }
    }
    return dp[day][last] = maxMerits;
}

int ninjaTraining2(int n, vector<vector<int>> &points)
{
    vector<vector<int>> dp(n, vector<int> (4, -1));
    return merits(n-1, 3, points, dp);
}

/**
 * Tabulation - Bottom-Up
 * TC - O(N x 4 x 3)
 * SC - O(N x 4) we eliminated stack space
*/

int ninjaTraining3(int n, vector<vector<int>> &points)
{
    vector<vector<int>> dp(n, vector<int> (4, -1));
    dp[0][0] = max(points[0][1], points[0][2]);
    dp[0][1] = max(points[0][0], points[0][2]);
    dp[0][2] = max(points[0][0], points[0][1]);
    dp[0][3] = max(points[0][0], max(points[0][1],points[0][2]));

    for(int day = 1;day<n;day++){
        for(int last = 0;last<4;last++){
            dp[day][last] = 0;
            for(int task = 0;task<3;task++){
                if(task != last){
                    int merits = points[day][task] + dp[day - 1][task];
                    dp[day][last] = max(dp[day][last], merits);
                }
            }
        }
    }
    return dp[n-1][3];    
}

/**
 * SPACE Optimisation - 
 * TC - O(N x 4 x 3)
 * SC - O(4) ~ O(1)
*/

int ninjaTraining4(int n, vector<vector<int>> &points)
{
    vector<int> prev(4, 0);
    prev[0] = max(points[0][1], points[0][2]);
    prev[1] = max(points[0][0], points[0][2]);
    prev[2] = max(points[0][0], points[0][1]);
    prev[3] = max(points[0][0], max(points[0][1],points[0][2]));

    for(int day = 1;day<n;day++){
        vector<int> dummy(4, 0);
        for(int last = 0;last<4;last++){            
            for(int task = 0;task<3;task++){
                if(task != last){
                    dummy[last] = max(dummy[last], points[day][task] + prev[task]);
                }
            }
        }
        prev = dummy;
    }
    return prev[3];    
}

int main(){
    int n = 3;
    vector<vector<int>> points = {
    {10, 40 , 70}, 
    {20, 50, 80}, 
    {30, 60, 90}};
    cout << "maximum merit points earned is " << ninjaTraining3(n, points);
}