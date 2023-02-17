// Min_cost_2_reach_destn.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;
#define M 1000000007
#define VP vector<int>
class Solution {
public:
    int minCost(int maxTime, vector<vector<int>>& edges, vector<int>& passingFees) {
        int n = passingFees.size();
        vector<vector<pair<int, int>>>G(n);//Adjacency graph
        for (int i = 0; i < edges.size(); i++)
        {
            int u = edges[i][0];
            int v = edges[i][1];
            int t = edges[i][2];
            G[u].push_back(make_pair(v, t));
            G[v].push_back(make_pair(u, t));
        }
        vector<vector<int>>dp(n, vector<int>(maxTime + 1, M));
        for (int t = 0; t <= maxTime; t++)
            dp[0][t] = passingFees[0];

        for (int t = 1; t <= maxTime; t++)
        {
            for (int u = 1; u < n; u++)
            {
                for (pair<int, int>v : G[u])
                {
                    int m = t - v.second;
                    if (m >= 0)
                        dp[u][t] = (dp[u][t] < dp[v.first][m] + passingFees[u]) ? dp[u][t] : dp[v.first][m] + passingFees[u];
                }
            }
        }
        return (dp[n - 1][maxTime] != M) ? dp[n - 1][maxTime] : -1;
    }
};

int main()
{
    Solution sol;
    int maxTime = 30;
    vector<int>passingFees{ 5,1,2,20,20,3 };
    vector<vector<int>>edges{ VP{0,1,10} ,VP{1,2,10},VP{2,5,10},VP{0,3,1},VP{3,4,10},VP{4,5,15} };
    int ret = sol.minCost(maxTime, edges, passingFees);
    std::cout << "Min passing cost : " << ret << endl;
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
