// Tile_cover.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    int minimumWhiteTiles(string floor, int numCarpets, int carpetLen) {
        int siz = floor.size();
        vector<vector<int>>dp(siz, vector<int>(numCarpets + 1, 0));
        /*//dp[i][nc] maximum number of whites, in floor[0:i] that can be covered with nc carpets*/
        vector<int>psum(siz, 0);//prefix sum for whites
        psum[0] = (floor[0] == '1') ? 1 : 0;
        for (int i = 1; i < siz; i++)
            psum[i] = psum[i - 1] + ((floor[i] == '1') ? 1 : 0);
        for (int i = 0; i < carpetLen; i++)
        {
            for (int j = 1; j <= numCarpets; j++)
                dp[i][j] = psum[i];
        }
        for (int i = carpetLen; i < siz; i++)
        {
            for (int j = 1; j <= numCarpets; j++)
            {
                int val = dp[i - carpetLen][j - 1] + psum[i] - psum[i - carpetLen];
                dp[i][j] = (val > dp[i - 1][j]) ? val : dp[i - 1][j];
            }
        }
        return psum[siz - 1] - dp[siz - 1][numCarpets];
    }
};
int main()
{
    Solution sol;
    string floor = "11111";
    int numCarpets = 2;
    int carpetLen = 3;
    int ret = sol.minimumWhiteTiles(floor, numCarpets, carpetLen);
    cout << "min number of white tiles left: " << ret << endl;
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
