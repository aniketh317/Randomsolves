// max_deletions_str.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Solution {
public:
    void KMP(string &s, vector<int> &v)
    {
        /* v[i] will have length of longest proper suffix that is also prefix of s[0:i] */
        int siz = s.size();
        v.resize(siz, 0);
        for (int i = 1; i < siz; i++)
        {
            int l = v[i - 1];
            while (l != 0 && s[l] != s[i])
                l = v[l - 1];

            if (l != 0 || s[0] == s[i])
                v[i] = l + 1;
        }
    }
    int deleteString(string &s) {
        int siz = s.size();
        vector<vector<int>>pos(siz);//pos[i] contains positions for s.substr(i) at which the post-break can start, as per the que. condition
        for (int i = 0; i < siz; i++)
        {
            vector<int>v;
            string sub = s.substr(i);
            KMP(sub, v);
            int vsiz = v.size();
            for (int j = 1; j < vsiz; j += 2)
            {
                if (v[j] == ((j + 1) >> 1))
                    pos[i].push_back(i + ((j + 1) >> 1));
            }
        }
        vector<int>dp(siz, 1);//dp[i] has max no. times s.substr(i) can be broken. Any s.substr(i) can be broken atleast once
        for (int i = siz - 2; i >= 0; i--)
        {
            for (int p : pos[i])
                dp[i] = (dp[i] < dp[p] + 1) ? dp[p] + 1 : dp[i];
        }
        return dp[0];
    }
};

int main()
{
    Solution sol;
    string s = "aaabaab";
    int ret = sol.deleteString(s);
    cout << "Max number of deletions: " << ret << endl;
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
