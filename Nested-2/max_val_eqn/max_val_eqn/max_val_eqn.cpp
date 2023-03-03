// max_val_eqn.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <deque>
#define VI vector<int>
#define M 1000000007
using namespace std;
class Solution {
public:
    int findMaxValueOfEquation(vector<vector<int>>& points, int k) {
        int siz = points.size();
        deque<pair<int,int>>dq;//first -> x, second -> y-x
        int ret = -M;
        for (int i = 0; i < siz; i++)
        {
            int x = points[i][0];
            int y = points[i][1];
            while (!dq.empty() && (x - dq.front().first) > k)
                dq.pop_front();
            if (!dq.empty())
                ret = ret > x + y + dq.front().second ? ret : x + y + dq.front().second;
            while (!dq.empty() && dq.back().second <= y - x)
                dq.pop_back();
            dq.push_back(make_pair(x, y - x));
        }
        return ret;
    }
};

int main()
{
    Solution sol;
    vector<vector<int>>points{ VI{1,3} ,VI{2,0},VI{5,10},VI{6,-10} };
    int k = 1;
    int ret = sol.findMaxValueOfEquation(points, k);
    std::cout << "Max value of equation : " << ret << endl;
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
