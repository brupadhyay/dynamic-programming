#include <bits/stdc++.h>
using namespace std;

/**
 * Time Complexity: O(N * (M+M)), 
 * where N = total no. of rows and M = total no. of columns.
 * Reason: O(N) for running a loop to check all rows. Now, inside that loop, O(M)
 * is for visiting all the columns, and another O(M) is for the function we are using. 
 * the function takes linear time complexity. Here, the size of the height array is M, 
 * so it will take O(M).
 * Space Complexity: O(M), where M = total no. of columns.
 * Reason: We are using a height array and a stack of size M.
*/

class Solution {
    int largestRectangleArea(vector<int> heights) {
        int n = heights.size();
        int maxA = 0;
        stack<int> st;
        for(int i = 0; i <= n; i++){
            while(!st.empty() && (i == n || heights[st.top()] >= heights[i])){
                int width;
                int height = heights[st.top()];
                st.pop();
                if(st.empty()) width = i;
                else width = i - st.top() - 1;
                maxA = max(maxA, height * width);
            }
            st.push(i);
        }
        return maxA;
    }
public:
    int maximalRectangle(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        vector<int> histo(m, 0);
        int maxA = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(matrix[i][j] == 1){
                    histo[j] += 1;
                } else {
                    histo[j] = 0;
                }
            }
            maxA = max(maxA, largestRectangleArea(histo));
        }
        return maxA;
    }
};

int main() {

    vector<vector<int>> matrix = {
        {1, 0, 1, 0, 0}, {1, 0, 1, 1, 1},
        {1, 1, 1, 1, 1}, {1, 0, 0, 1, 0}
    };
    Solution obj;
    int maxArea = obj.maximalRectangle(matrix);
    cout << "The maximum are is: " << maxArea << "\n";
    return 0;
}