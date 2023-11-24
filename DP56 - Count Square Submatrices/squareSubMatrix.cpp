#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countSquares(int n, int m, vector<vector<int>> matrix) {
        int ans = 0;
        vector<vector<int>> dp(n, vector<int> (m , 0));
        for(int i = 0; i < n; i++) dp[i][0] = matrix[i][0];
        for(int j = 0; j < m; j++) dp[0][j] = matrix[0][j];

        for(int i = 1; i < n; i++){
            for(int j = 1; j < m; j++){
                if(matrix[i][j] == 0){
                    dp[i][j] = 0;
                } else {
                    dp[i][j] = min(dp[i-1][j-1], min(dp[i-1][j], dp[i][j-1])) + 1;
                }
            }
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                ans += dp[i][j];
            }
        }
        return ans;
    }
};

int main() {

    vector<vector<int>> arr = {
        {0, 1, 1, 1}, {1, 1, 1, 1},
        {0, 1, 1, 1}
    };
    int n = 3, m = 4;
    Solution obj;
    int squares = obj.countSquares(n, m, arr);
    cout << "The number of squares: " << squares << "\n";
    return 0;
}