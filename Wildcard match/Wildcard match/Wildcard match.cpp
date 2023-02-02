// Wildcard match.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    bool isMatch(string &s, string &p) {
        vector<char>S;
        vector<char>P;
        for (char c : s)
            S.push_back(c);
        int i = 0;
        for (i = 0; i < p.size(); i++)
        {
            P.push_back(p[i]);
            if (p[i] == '*')
            {
                while (i + 1 < p.size() && p[i + 1] == '*')
                    i++;
            }
        }
        if (S.size() == 0)
        {
            if (P.size() == 0 || (P.size() == 1 && P[0] == '*'))
                return true;
            return false;
        }
        else if (P.size() == 0)
            return false;

        vector<vector<bool>>dp(S.size(), vector<bool>(P.size(), false));//dp[m][n] indicates if S[0:m], P[0:n] can be matched
        vector<vector<bool>>tp(S.size(), vector<bool>(P.size(), false));//tp[m][n] indicates if S[0:k], P[0:n] can be matched for some k<=m

        if (P[0] == '*')
        {
            for (int m = 0; m < S.size(); m++)
            {
                dp[m][0] = true;
                tp[m][0] = true;
            }
            if (P.size() > 1 && ((S[0] == P[1])||(P[1] == '?')))
                dp[0][1] = true;
        }
        if (P[0] == '?' || P[0] == S[0])
        {
            dp[0][0] = true;
            for (int m = 0; m < S.size(); m++)
                tp[m][0] = true;
        }

        for (int n = 1; n < P.size(); n++)
        {
            if (P[n] == '*')
            {
                for (int m = 0; m < S.size(); m++)
                    dp[m][n] = tp[m][n - 1];
            }
            else
            {
                for (int m = 1; m < S.size(); m++)
                    dp[m][n] = (P[n] == '?' || P[n] == S[m]) && (dp[m - 1][n - 1]);
            }
            tp[0][n] = dp[0][n];
            for (int m = 1; m < S.size(); m++)
                tp[m][n] = tp[m - 1][n] || dp[m][n];
        }
        return dp[S.size() - 1][P.size() - 1];
    }
};

int main()
{
    Solution sol;
    string s = "a";
    string p = "a*";
    bool ret = sol.isMatch(s, p);
    cout << "Match is possible? : " << ret << endl;
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
