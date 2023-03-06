// divide_corridor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#define M 1000000007
typedef long long ll;
using namespace std;
class Solution {
public:
    int numberOfWays(string corridor) {
        int siz = corridor.size();
        if (siz == 0 || siz == 1)
            return 0;
        vector<int>count(siz + 1, 0);
        count[0] = 0;
        for (int i = 1; i <= siz; i++)
            count[i] = count[i - 1] + ((corridor[i - 1] == 'S') ? 1 : 0);
        vector<int>dp(siz + 1, 0);//dp[i] total number of partitions possible with last rod at i, dp[siz] to contain the total no. of valid partitions 
        int k = 0;
        while (k<=siz && count[k] != 2)
            k++;
        if (k == siz + 1)
            return 0;
        dp[k] = 1;
        int sum = dp[k];
        for (int i = k + 1; i <= siz; i++)
        {
            if (corridor[i - 1] == 'P')
            {
                dp[i] = dp[i - 1];
                if (count[i] % 2 == 0)
                    sum = (sum + dp[i]) % M;
            }
            else
            {
                if (count[i] % 2 == 1)
                    dp[i] = 0;
                else
                    dp[i] = sum;
            }
        }
        return dp[siz];
    }
};

int main()
{
    Solution sol;
    string corridor = "SSPPSPS";
    int ret = sol.numberOfWays(corridor);
    std::cout << "Number of ways to divide corridor : " << ret << endl;
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
