// valid_paranthesis_string.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#define VPC vector<char>
using namespace std;

class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        if (grid[0][0] == ')')
            return false;
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<vector<bool>>>dp(m, vector<vector<bool>>(n, vector<bool>(m + n + 1, false)));//dp[i][j][k] whether k open brackets are possible
        dp[0][0][1] = true;
        for (int j = 1; j < n; j++)
        {
            if (grid[0][j] == '(')
            {
                for (int k = 0; k < m + n; k++)
                    dp[0][j][k + 1] = dp[0][j - 1][k];
            }
            else
            {
                for (int k = 1; k <= m + n; k++)
                    dp[0][j][k - 1] = dp[0][j - 1][k];
            }
        }
        for (int i = 1; i < m; i++)
        {
            if (grid[i][0] == '(')
            {
                for (int k = 0; k < m + n; k++)
                    dp[i][0][k + 1] = dp[i - 1][0][k];
            }
            else
            {
                for (int k = 1; k <= m + n; k++)
                    dp[i][0][k - 1] = dp[i - 1][0][k];
            }
        }

        for (int i = 1; i < m; i++)
        {
            for (int j = 1; j < n; j++)
            {
                if (grid[i][j] == '(')
                {
                    for (int k = 0; k < m + n; k++)
                        dp[i][j][k + 1] = dp[i - 1][j][k] || dp[i][j - 1][k];
                }
                else
                {
                    for (int k = 1; k <= m + n; k++)
                        dp[i][j][k - 1] = dp[i - 1][j][k] || dp[i][j - 1][k];
                }
            }
        }
        return dp[m - 1][n - 1][0];
    }
};

int main()
{
    Solution sol;
    vector<vector<char>>grid{ VPC{'(','(','('},VPC{')','(',')'},VPC{'(','(',')'},VPC{'(','(',')'} };
    bool ret = sol.hasValidPath(grid);
    cout << "Is there a valid path : " << ret << endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
