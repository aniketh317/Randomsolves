// path_with_maxscore.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#define M 1000000007 
using namespace std;
class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        int m = board.size();
        int n = board[0].size();
        vector<vector<pair<int, int>>>dp(m, vector<pair<int, int>>(n, make_pair(0, 0)));//(maxsum, num paths)
        dp[m - 1][n - 1].first = 0;
        dp[m - 1][n - 1].second = 1;
        for (int i = m - 2; i >= 0; i--)
        {
            if (dp[i + 1][n - 1].second != 0 && board[i][n-1]!='X')
            {
                dp[i][n - 1].first = dp[i + 1][n - 1].first + int(board[i][n - 1] - '0');
                dp[i][n - 1].second = dp[i + 1][n - 1].second;
            }
        }
        for (int j = n - 2; j >= 0; j--)
        {
            if (dp[m - 1][j + 1].second != 0 && board[m - 1][j] != 'X')
            {
                dp[m - 1][j].first = dp[m - 1][j + 1].first + int(board[m - 1][j] - '0');
                dp[m - 1][j].second = dp[m - 1][j + 1].second;
            }
        }
        for (int i = m - 2; i >= 0; i--)
        {
            for (int j = n - 2; j >= 0; j--)
            {
                if (board[i][j] != 'X')
                {
                    int max = (dp[i][j + 1].first > dp[i + 1][j + 1].first) ? dp[i][j + 1].first : dp[i + 1][j + 1].first;
                    max = (max > dp[i + 1][j].first) ? max : dp[i + 1][j].first;
                    dp[i][j].first = max;
                    if (dp[i][j + 1].first == max)
                        dp[i][j].second = (dp[i][j].second + dp[i][j + 1].second) % M;
                    if (dp[i + 1][j + 1].first == max)
                        dp[i][j].second = (dp[i][j].second + dp[i + 1][j + 1].second) % M;
                    if (dp[i + 1][j].first == max)
                        dp[i][j].second = (dp[i][j].second + dp[i + 1][j].second) % M;
                    if (dp[i][j].second != 0 && board[i][j] != 'E')
                        dp[i][j].first += int(board[i][j] - '0');
                }
            }
        }
        vector<int>ret;
        ret.push_back(dp[0][0].first);
        ret.push_back(dp[0][0].second);
        return ret;
    }
};

int main()
{
    Solution sol;
    vector<string>board{"E23", "2X2", "12S"};
    vector<int>ret = sol.pathsWithMaxScore(board);
    cout << "[" << ret[0] << " , " << ret[1] << "]" << endl;
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
