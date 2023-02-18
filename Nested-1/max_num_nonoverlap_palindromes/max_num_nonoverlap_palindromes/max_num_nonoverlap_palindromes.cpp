// max_num_nonoverlap_palindromes.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#define M 10000000
using namespace std;

class Solution {
private:
    void manacher(string& s, vector<int>& v)
    {
        /*s-- Input String
        v -- vector to be populated with max radius palindrome around it entries
        */
        string mod = "*";
        for (char c : s)
        {
            mod.push_back(c);
            mod.push_back('*');
        }
        v.resize(mod.size(), 0);
        int siz = mod.size();
        int c = 0;//center of palindrome with right-most endpoint
        int r = 0;//radius of the above palindrome
        for (int i = 1; i < mod.size(); i++)
        {
            if (i - c < r)
            {
                int j = c - (i - c);//left image 
                v[i] = (v[j] < c + r - i) ? v[j] : c + r - i;
            }
            if (i + v[i] >= r + c)
            {
                c = i;
                r = v[i];
                while (c + r + 1 < siz && c - r - 1 >= 0 && mod[c + r + 1] == mod[c - r - 1])
                    r++;
                v[i] = r;
            }
        }
        return;
    }
public:
    int maxPalindromes(string s, int k) {
        int ret = 0;
        vector<int>prad;//longest palindrome radii around each point
        int siz = s.size();
        manacher(s, prad);
        
        int k1 = (k % 2 == 0) ? k + 1 : k;
        int k2 = (k % 2 == 0) ? k : k + 1;

        vector<int>mink(siz + 1, M);//minimum radius >= k bordering at *(initial vals are dummy)
        for (int i = 0; i < prad.size(); i++)
        {
            int k = (i % 2 == 0) ? k2 : k1;
            for (int j = i + k; j <= i + prad[i]; j += 2)
                mink[j >> 1] = (mink[j >> 1] > j - i) ? (j - i) : mink[j >> 1];
        }
        bool flag = false;
        int msiz = mink.size();
        for (int j = 0; j < msiz && !flag; j++)
            flag = mink[j] != M;
        if (flag)
        {
            vector<int>dp(msiz, 0);
            for (int j = 1; j < msiz; j++)
            {
                dp[j] = dp[j - 1];
                if (mink[j] != M)
                    dp[j] = (1 + dp[j - mink[j]] > dp[j]) ? 1 + dp[j - mink[j]] : dp[j];
            }
            ret = dp[msiz - 1];
        }
        return ret;
    }
};

int main()
{
    Solution sol;
    string s = "abaccdbbd";
    int k = 3;
    int ret = sol.maxPalindromes(s, k);
    cout << "Maximum number of non-overlapping palindrome strings : " << ret << endl;
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
