// Max_Palin_4rm_subseq.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    int longestPalindrome(string &word1, string &word2) {
        reverse(word2.begin(), word2.end());//Reverse the word2
        
        int siz1 = word1.size();
        int siz2 = word2.size();

        vector<vector<int>>lcs(siz1, vector<int>(siz2, 0));
        lcs[0][0] = (word1[0] == word2[0]) ? 1 : 0;
        for (int j = 1; j < siz2; j++)
            lcs[0][j] = (word1[0] == word2[j]) ? 1 : lcs[0][j - 1];
        for (int i = 1; i < siz1; i++)
            lcs[i][0] = (word1[i] == word2[0]) ? 1 : lcs[i - 1][0];

        for (int i = 1; i < siz1; i++)
        {
            for (int j = 1; j < siz2; j++)
            {
                if (word1[i] == word2[j])
                    lcs[i][j] = 1 + lcs[i - 1][j - 1];
                else
                    lcs[i][j] = (lcs[i - 1][j] > lcs[i][j - 1]) ? lcs[i - 1][j] : lcs[i][j - 1];
            }
        }

        /*Get longest palindromic subsequence for every word1[i:j]*/
        vector<vector<int>>dp1(siz1, vector<int>(siz1, 0));
        for (int i = 0; i < siz1; i++)
            dp1[i][i] = 1;
        for (int l = 2; l <= siz1; l++)
        {
            for (int i = 0; i <= siz1 - l; i++)
            {
                dp1[i][i + l - 1] = 1;
                if (word1[i] == word1[i + l - 1])
                    dp1[i][i + l - 1] = 2 + dp1[i + 1][i + l - 2];
                else
                {
                    int val = (dp1[i + 1][i + l - 1] > dp1[i][i + l - 2]) ? dp1[i + 1][i + l - 1] : dp1[i][i + l - 2];
                    dp1[i][i + l - 1] = (dp1[i][i + l - 1] < val) ? val : dp1[i][i + l - 1];
                }
            }
        }

        /*Get longest palindromic subsequence for every word2[i:j]*/
        vector<vector<int>>dp2(siz2, vector<int>(siz2, 0));
        for (int i = 0; i < siz2; i++)
            dp2[i][i] = 1;
        for (int l = 2; l <= siz2; l++)
        {
            for (int i = 0; i <= siz2 - l; i++)
            {
                dp2[i][i + l - 1] = 1;
                if (word2[i] == word2[i + l - 1])
                    dp2[i][i + l - 1] = 2 + dp2[i + 1][i + l - 2];
                else
                {
                    int val = (dp2[i + 1][i + l - 1] > dp2[i][i + l - 2]) ? dp2[i + 1][i + l - 1] : dp2[i][i + l - 2];
                    dp2[i][i + l - 1] = (dp2[i][i + l - 1] < val) ? val : dp2[i][i + l - 1];
                }
            }
        }

        int maxlen = 0;
        for (int i = 0; i < siz1; i++)
        {
            for (int j = 0; j < siz2; j++)
            {
                if (lcs[i][j] > 0)
                {
                    maxlen = ((lcs[i][j] << 1) > maxlen) ? (lcs[i][j] << 1) : maxlen;
                    if (i + 1 < siz1)
                        maxlen = (((lcs[i][j] << 1) + dp1[i + 1][siz1 - 1]) > maxlen) ? ((lcs[i][j] << 1) + dp1[i + 1][siz1 - 1]) : maxlen;
                    if (j + 1 < siz2)
                        maxlen = (((lcs[i][j] << 1) + dp2[j + 1][siz2 - 1]) > maxlen) ? ((lcs[i][j] << 1) + dp2[j + 1][siz2 - 1]) : maxlen;
                }
            }
        }
        return maxlen;
    }
};
int main()
{
    Solution sol;
    string word1 = "ccabbcebfc";
    string word2 = "ffcdfcddaa";
    int ret = sol.longestPalindrome(word1, word2);
    cout << "Max length of subsequences palindrome: " << ret << endl;
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
