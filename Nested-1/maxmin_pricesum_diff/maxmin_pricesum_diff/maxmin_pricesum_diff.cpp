// maxmin_pricesum_diff.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <set>
using namespace std;

#define V(i,j) vector<int>{i,j}

class Solution {
private:
    vector<vector<int>>G;//Adjacency Graph
    vector<int>p;//prices of each vertex
    vector<bool>v;//visit vector
    vector<int>nver;//next vertex for the max path price
    vector<int>maxp;//maxp[i]max path sum for the sub tree rooted at i
    set<int>pver;
    void dfs1(int i)
    {
        /*Return the length of the longest path in the subtree rooted at i, updating nver*/
        v[i] = true;
        int max = 0;//maxlen excl. of i in the subtree from i
        for (int k = 0; k < G[i].size(); k++)
        {
            int j = G[i][k];
            if (!v[j])
            {
                v[j] = true;
                dfs1(j);
                if (maxp[j] > max)
                {
                    max = maxp[j];
                    nver[i] = j;
                }
            }
        }
        maxp[i] = max + p[i];
        return;
    }

    vector<int>stack;
    void dfs2(int i, set<int>& pver, int dis)
    {
        /*dis indicates sum of prices from the lowest ancestor in pver upto this, excluding the ancestor */
        bool flag = false;
        v[i] = true;
        set<int>::iterator itr = pver.find(i);
        if (itr != pver.end())
            flag = true;
        if (flag)
        {
            stack.push_back(i);
            dis = 0;
        }
        else
            dis += p[i];

        for (int k = 0; k < G[i].size(); k++)
        {
            int j = G[i][k];
            if (!v[j])
            {
                if (!flag)
                    maxp[j] = (maxp[j] < dis + p[j] + maxp[stack.back()]) ? dis + p[j] + maxp[stack.back()] : maxp[j];
                if (flag)
                    dfs2(j, pver, 0);
                else
                    dfs2(j, pver, dis);
            }
        }
        if (flag)
            stack.pop_back();
        return;
    }
public:
    long long maxOutput(int n, vector<vector<int>>& edges, vector<int>& price) {
        G.clear();
        v.clear();
        nver.clear();
        maxp.clear();

        G.resize(n);
        p = price;
        v.resize(n, false);
        nver.resize(n, -1);
        maxp.resize(n, 0);

        for (int i = 0; i < n - 1; i++)
        {
            G[edges[i][0]].push_back(edges[i][1]);
            G[edges[i][1]].push_back(edges[i][0]);
        }
        dfs1(0);
        int i = 0;
        int d = 0;//length of path starting from a vertex and going up along maxpath and dropping in non-max direction
        for (int i = 0; i < n; i++)
            v[i] = false;
        while (i!= -1)
        {
            pver.insert(i);
            v[i] = true;
            for (int k = 0; k < G[i].size(); k++)
            {
                int j = G[i][k];
                if (!v[j] && j != nver[i])
                    d = (d < maxp[j]) ? maxp[j] : d;
            }
            d += p[i];
            maxp[i] = (maxp[i] < d) ? d : maxp[i];//Updated to longest path from this vertex
            i = nver[i];
        }
        for (int i = 0; i < n; i++)
            v[i] = false;

        dfs2(0, pver, 0);
        int maxd = maxp[0] - p[0];
        for (int i = 1; i < n; i++)
            maxd = (maxp[i] - p[i] > maxd) ? maxp[i] - p[i] : maxd;
        return maxd;
    }
};
int main()
{
    Solution sol;
    int n = 6;
    vector<vector<int>>edges{ V(0,1), V(1,2), V(1,3), V(3,4), V(3,5) };
    vector<int>price{ 9,8,7,6,10,5 };
    int ret = sol.maxOutput(n, edges, price);
    cout << "Difference between Max and Min price Sum : " << ret << endl;
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
