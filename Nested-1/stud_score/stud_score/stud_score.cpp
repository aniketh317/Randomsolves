// stud_score.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;
class Solution {
private:
    vector<vector<pair<int,int>>>facs;//Factors for numbers
    struct cust {
        char c = '*';
        int val = -1;
        cust(char ch):c(ch){}
        cust(int v):val(v){}
    };
public:
    int scoreOfStudents(string s, vector<int>& answers) {
        facs.resize(1001);
        for (int i = 1; i <= 1000; i++)
        {
            for (int j = 1; j * j <= i; j++)
            {
                int q = i / j;
                if (j * q == i)
                {
                    facs[i].push_back(make_pair(j, q));
                    facs[i].push_back(make_pair(q, j));
                }
            }
        }
        for (int j = 0; j <= 1000; j++)
        {
            facs[0].push_back(make_pair(0, j));
            facs[0].push_back(make_pair(j, 0));
        }
        int siz = s.size();
        int dsz = (siz + 1) >> 1;
        vector<vector<set<int>>>dp(dsz);//dp[i][l] indicates all values that are possible from s[i:i+l-1] range
        for (int i=0;i<dsz;i++)
            dp[i].resize(1 + dsz - i);

        for (int i = 0; i < dsz; i++)
            dp[i][1].insert(int(s[(i << 1)] - '0'));
        for (int l = 2; l <= dsz; l++)
        {
            for (int i = 0; i <= dsz - l; i++)
            {
                for (int z = 1; z < l ; z++)
                {
                    char sym = s[((i + z - 1) << 1) + 1];
                    if (sym == '+')
                    {
                        for (int d1 : dp[i][z])
                        {
                            for (int d2 : dp[i + z][l - z])
                            {
                                int val = d1 + d2;
                                if (val <= 1000)
                                    dp[i][l].insert(val);
                            }
                        }
                    }
                    else
                    {
                        for (int d1 : dp[i][z])
                        {
                            for (int d2 : dp[i + z][l - z])
                            {
                                int val = d1 * d2;
                                if (val <= 1000)
                                    dp[i][l].insert(val);
                            }
                        }
                    }
                }
            }
        }
        /*To compute result*/
        vector<cust>stack;
        for (int i = 0; i < siz; i++)
        {
            if (i % 2 == 1)
            {
                if (s[i] == '+')
                {     
                    while (stack.size() > 2 && stack[stack.size() - 2].c == '*')
                    {
                        int ssiz = stack.size();
                        int val = stack[ssiz - 1].val * stack[ssiz - 3].val;
                        stack.pop_back();
                        stack.pop_back();
                        stack.pop_back();
                        stack.push_back(cust(val));
                    }
                }
                stack.push_back(cust(s[i]));
            }
            else
                stack.push_back(cust(int(s[i] - '0')));
        }
        while (stack.size() != 1)
        {
            int ssiz = stack.size();
            int val = -1;
            if(stack[ssiz-2].c=='*')
                val = stack[ssiz - 1].val * stack[ssiz - 3].val;
            else
                val = stack[ssiz - 1].val + stack[ssiz - 3].val;
            stack.pop_back();
            stack.pop_back();
            stack.pop_back();
            stack.push_back(cust(val));
        }
        int ans = stack[0].val;
        int score = 0;
        for (int i = 0; i < answers.size(); i++)
        {
            if (ans == answers[i])
                score += 5;
            else 
            {
                set<int>::iterator itr;
                itr = dp[0][dsz].find(answers[i]);
                if(itr!=dp[0][dsz].end())
                    score += 2;
            }
        }
        return score;
    }
};

int main()
{
    Solution sol;
    string s = "4+2*6+4*4+6";
    vector<int>answers{ 664,200,38,166,244,76,86,38,719,138,297,38,166,204,438,38,276,38,164,38,909,382,155,38,38,56,58,38,38,102,278,204,38,38,600,385,102,38,38,164,166,166,86,96,906,90,60,38,166,204,138,38,171,204,268,204,56,60,56,54,38,573,299,138,38,38,647,898 };
    int ret = sol.scoreOfStudents(s, answers);
    cout << "Total score : " << ret << endl;
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
