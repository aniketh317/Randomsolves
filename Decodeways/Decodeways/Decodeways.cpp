// Decodeways.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
constexpr auto M = 1000000007;
using namespace std;

class Solution {
public:
    int numDecodings(string &s) {
        int l = s.length();
        if (l == 0 || s[0] == '0')
            return 0;
        long int e1 = 0;//Number of strings with 1 left out at end
        long int e2 = 0;//Number of strings with 2 left out at end
        long int e = 0;//Number of strings with unleft letters
        if (s[0] == '1' || s[0] == '*')
            e1 = 1;
        if (s[0] == '2' || s[0] == '*')
            e2 = 1;
        if (s[0] == '*')
            e = 9;
        else
            e = 1;
        for (int i = 1; i < l; i++)
        {
            long int te1, te2, te;
            /*Update e1*/
            if (s[i] == '1' || s[i] == '*')
                te1 = e;
            else
                te1 = 0;
            if (s[i] == '2' || s[i] == '*')
                te2 = e;
            else
                te2 = 0;
            if (s[i] == '0')
                te = (e1 + e2) % M;
            else if (s[i] == '*')
                te = ((3 * ((3 * e1) % M)) % M + (2 * ((3 * e2) % M)) % M + (3 * ((3 * e) % M)) % M)%M;
            else if (int(s[i] - '0') <= 6)
                te = (e1 + e2 + e) % M;
            else
                te = (e1 + e) % M;
            e = te;
            e1 = te1;
            e2 = te2;
        }
        return (int)e;
    }
};

int main()
{
    string s = "2*3*";
    Solution sol;
    int ret = sol.numDecodings(s);
    std::cout << ret;
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
