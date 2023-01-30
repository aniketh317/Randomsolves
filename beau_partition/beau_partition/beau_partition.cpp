// beau_partition.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#define M 1000000007
using namespace std;
class Solution {
public:
    int beautifulPartitions(string &s, int k, int minLength) {
        vector<int>ppos;//positions which are non-prime and immediately followed by prime
        char c = s[0];
        int siz = s.length();
        char cl = s[s.length() - 1];
        if (!(c == '2' || c == '3' || c == '5' || c == '7') || (cl == '2' || cl == '3' || cl == '5' || cl == '7'))
            return 0;

        ppos.push_back(0);//Dummy ppos posn befor the first prime
        for (int i = 0; i < s.length()-1; i++)
        {
            char c = s[i];
            char cn = s[i + 1];
            if (cn == '2' || cn == '3' || cn == '5' || cn == '7')
            {
                if (c != '2' && c != '3' && c != '5' && c != '7')
                    ppos.push_back(i + 1);
            }
        }
        ppos.push_back(siz);
        vector<vector<int>>dp(k + 1, vector<int>(ppos.size(), 0));//dp[z][j] is the number of z partitions ending at this non-prime posn
        vector<vector<int>>tot(k + 1, vector<int>(ppos.size(), 0));//tot[z][j] is the number of z partitions ending at non-prime posn upto this non-prime posn

        int ist = 0;//Will contain the index of 1st ppos that is minLength away from start
        while (ist < ppos.size() && ppos[ist] < minLength)
            ist++;
        int sum = 0;
        for (int i = ist; i < ppos.size(); i++)
        {
            dp[1][i] = 1;
            tot[1][i] = tot[1][i - 1] + 1;
        }
        for (int z = 2; z <= k; z++)
        {
            int t = 0;
            for (int i = ist; i < ppos.size(); i++)
            {
                while (t + 1 < ppos.size() && ppos[i] - ppos[t + 1] >= minLength)
                    t++;
                dp[z][i] = tot[z - 1][t];
                tot[z][i] = (tot[z][i - 1] + dp[z][i]) % M;
            }
        }
        return dp[k][ppos.size() - 1];
    }
};

int main()
{
    Solution sol;
    string s = "783938233588472343879134266968";
    int k = 4;
    int minLength = 6;
    int ret = sol.beautifulPartitions(s, k, minLength);
    std::cout << "Number of beautiful partitions: " << ret << endl;;
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
