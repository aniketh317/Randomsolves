// Parallel_course2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <assert.h>
#include <algorithm>
constexpr auto INF = 10000000;
using namespace std;

void calcdeg0(vector<int>&fil,vector<vector<int>>G, vector<int>deg, int sub)
{
    /*Calculates no dependency vertices for this subset covered so far,*/
    int n = (int)deg.size();//Number of vertices in all
    int ver = 0;
    int sub2 = sub;
    while (sub != 0)
    {
        if (sub % 2 == 1)
        {
            for (int z : G[ver])
                deg[z]--;
        }
        ver++;
        sub >>= 1;
    }
    for (int i = 0; i < n; i++)
    {
        if (deg[i] == 0 && (((1<<i)&sub2)==0))//Ensure vertex not in subset
            fil.push_back(i);
    }

}

void neighbor_compute_rec(int sub, vector<int>& deg0, int st, int kl,vector<int>&adj)
{
    /*
    * sub is the subset so far
    * deg0 is the vector of zero degree vertices for the initial subset
    * st is the next index to start from
    * kl is the number of slots left
    * adj is the adjacency list to which next subset to be appended
    */
    if (st == deg0.size() || kl == 0)
    {
        adj.push_back(sub);
        return;
    }
    for (int j = st; j < deg0.size(); j++)
    {
        int subset = sub | (1 << deg0[j]);
        neighbor_compute_rec(subset, deg0, j + 1, kl - 1, adj);//This traversal turns out to be DFS along a tree(|E|=|V|-1)
    }
}

void DFS_visit(vector<vector<int>>& G, int i, vector<bool>& v, vector<int>&top)
{
    /*top is for storing vertices in topological sort, graph G is DAG*/
    for (int z : G[i])
    {
        if (!v[z])
        {
            v[z] = true;
            DFS_visit(G, z, v, top);
        }
    }
    top.push_back(i);
}

class Solution {
public:
    int minNumberOfSemesters(int n, vector<vector<int>>& relations, int k) {
        vector<vector<int>>st0deg(1 << n);//st0deg[st] will have list of vertices of 0 degree for this subset of vertices covered
        assert(n <= 15);
        vector<vector<int>>G(n);//For each vertex, vertices dependent on it(list)
        vector<int>deg(n);//Number of vertices on which this vertex is dependent
        for (int i = 0; i < relations.size(); i++)
        {
            int u = relations[i][0]-1;
            int v = relations[i][1]-1;
            G[u].push_back(v);
            deg[v]++;
        }
        if (relations.size() == 0)
        {
            int v = n / k;
            if (n % k != 0)
                v++;
            return v;
        }
        for (int sub = 0; sub < st0deg.size(); sub++)
            calcdeg0(st0deg[sub], G, deg, sub);//Calculate no internal dependency vertices for each subset
        vector<vector<int>>Gcont(1<<n);//From a subset of vertices covered upto current step what subset can be covered within next step
        //A subset of vertices with cardinality < \sum_i=0^{k}(n-r)C_i <= 2^(n-r) will be cosidered as adjacent vertices  
        for (int i = 0; i < (1 << n) - 1; i++)
            neighbor_compute_rec(i, st0deg[i], 0, k, Gcont[i]);
        
        vector<bool>visit((1 << n), false);
        vector<int>topo;//Will store topological ordering of vertices in Gcont
        visit[0] = true;
        DFS_visit(Gcont, 0, visit, topo);
        reverse(topo.begin(), topo.end());

        vector<int>dist(1 << n, INF);
        dist[0] = 0;
        for (int i = 0; i < (1 << n); i++)
        {
            for (int z : Gcont[i])
                dist[z] = (dist[z] > dist[i] + 1) ? dist[i] + 1 : dist[z];
        }
        return dist[(1 << n) - 1];
    }
};
int main()
{
    int n = 15;
    vector<vector<int>>relations{ {6,15} };
    int k = 10;
    Solution sol;
    int ret = sol.minNumberOfSemesters(n, relations, k);
    cout << "Minimum number of semesters : " << ret << endl;
    return 0;
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
