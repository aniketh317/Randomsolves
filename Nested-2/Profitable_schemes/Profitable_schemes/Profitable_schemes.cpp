// Profitable_schemes.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
#define M 1000000007
class Solution {
public:
    int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit) {
        int siz = group.size();
        vector<vector<vector<ll>>>dp(siz, vector<vector<ll>>(n + 1, vector<ll>(minProfit + 1, 0)));//dp[i][m][mp] -- number of subsets upto index i
        //that consume exactly m persons and generate an mp amount of profit, dp[i][m][minProfit] -- number of subsets with profit >=minProfit, m fellows consumed
        dp[0][0][0] = 1;
        if (group[0] <= n)
        {
            if (profit[0] < minProfit)
                dp[0][group[0]][profit[0]] += 1;
            else
                dp[0][group[0]][minProfit] += 1;
        }
        for (int i = 1; i < siz; i++)
        {
            for (int m = 0; m <= n; m++)
            {
                for (int mp = 0; mp < minProfit; mp++)
                {
                    dp[i][m][mp] = dp[i - 1][m][mp];//Upto previous are there. Further
                    if (m >= group[i] && mp >= profit[i])
                        dp[i][m][mp] = (dp[i][m][mp] + dp[i - 1][m - group[i]][mp - profit[i]]) % M;
                }
                /*To handle case for minProfit*/
                dp[i][m][minProfit] = dp[i - 1][m][minProfit];//Upto previous are there. Further 
                if (m >= group[i])
                {
                    int sp = (minProfit - profit[i]) >= 0 ? minProfit - profit[i] : 0;
                    for (int p = sp; p <= minProfit; p++)
                        dp[i][m][minProfit] = (dp[i][m][minProfit] + dp[i - 1][m - group[i]][p]) % M;
                }
            }

        }
        ll sub = 0;
        for (int m = 0; m <= n; m++)
            sub = (sub + dp[siz - 1][m][minProfit]) % M;
        return sub;
    }
};

int main()
{
    Solution sol;
    int n = 10;
    int minProfit = 5;
    vector<int>group{ 2,3,5 };
    vector<int>profit{ 6,7,8 };
    int ret = sol.profitableSchemes(n, minProfit, group, profit);
    std::cout << "Number of profitable schemes : " << ret << endl;
    return 0;
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
