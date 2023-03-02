// min_refuel_stops.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
typedef long long ll;
using namespace std;
#define VI vector<int>
class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        if (target <= startFuel)
            return 0;
        if (target > startFuel && stations.size() == 0)
            return -1;
        int siz = stations.size();
        vector<vector<ll>>dp(siz, vector<ll>(siz + 1, -1));//dp[i][f] 
        //-- max fuel with which position i can be arrived with f stops(incl. of i)
        if (startFuel - stations[0][0] >= 0)
        {
            dp[0][0] = startFuel - stations[0][0];
            dp[0][1] = dp[0][0] + stations[0][1];
        }
        
        for (int i = 1; i < siz; i++)
        {
            if (dp[i - 1][0] - (stations[i][0] - stations[i - 1][0]) >= 0)
                dp[i][0] = dp[i - 1][0] - (stations[i][0] - stations[i - 1][0]);
            for (int f = 1; f <= i + 1; f++)
            {
                /*f stops made upto posn i*/
                
                ll m = -1;
                /*Case-1: fth stop made within i-1*/
                if (dp[i - 1][f] - (stations[i][0] - stations[i - 1][0]) >= 0)
                    m = dp[i - 1][f] - (stations[i][0] - stations[i - 1][0]);
                /*Case-2: fth statop made at i*/
                if (dp[i - 1][f - 1] - (stations[i][0] - stations[i - 1][0]) >= 0)
                {
                    ll fl = dp[i - 1][f - 1] - (stations[i][0] - stations[i - 1][0]);
                    m = (m > fl + stations[i][1]) ? m : fl + stations[i][1];
                }
                dp[i][f] = m;
            }
        }
        int ret = -1;
        bool flag = false;
        int f;
        for (f = 0; !flag && f <= siz; f++)
            flag = (dp[siz - 1][f] - (target - stations[siz - 1][0]) >= 0);
        f--;
        if (flag)
            ret = f;
        return ret;
    }
};


int main()
{
    Solution sol;
    int target = 100;
    int startFuel = 10;

    vector<vector<int>>stations{ VI{10,60} ,VI{20,30}, VI{30,30}, VI{60,40} };
    int ret = sol.minRefuelStops(target, startFuel, stations);
    std::cout << "Min Number of Refuelling stops : " << ret << endl;
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
