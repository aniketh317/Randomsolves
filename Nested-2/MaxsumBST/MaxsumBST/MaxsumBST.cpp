// MaxsumBST.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#define M 1000000007
/*Definition for a binary tree node.*/
  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  };
 
class Solution {
    struct cust {
        /*Associate instance with the call*/
        bool isbst = true;
        int max = -M;//The maximum in the bst(if it is so)
        int min = M;
        int sum = 0;//Sum of all keys in bst(valid only if this one is bst)
        int maxsum = 0;//Maxsum bst in the respective subtree
        cust(){}
        cust(bool bst, int max, int min, int sum, int maxsum):isbst(bst), max(max), min(min), sum(sum), maxsum(maxsum){}
    };
    cust rec_call(TreeNode* node)
    {
        if (node == nullptr)
            return cust();
        cust ret;
        cust l = rec_call(node->left);
        cust r = rec_call(node->right);
        ret.maxsum = (l.maxsum > r.maxsum) ? l.maxsum : r.maxsum;
        ret.isbst = l.isbst && r.isbst && (l.max < node->val) && (node->val < r.min);
        if (ret.isbst)
        {
            ret.sum = l.sum + r.sum + node->val;
            if (ret.sum > ret.maxsum)
                ret.maxsum = ret.sum;
            ret.min = (l.min < node->val) ? l.min : node->val;
            ret.max = (r.max > node->val) ? r.max : node->val;
        }
        return ret;
    }
public:
    int maxSumBST(TreeNode* root) {
        cust ret = rec_call(root);
        return ret.maxsum;
    }
};

int main()
{
    Solution sol;
    TreeNode n4(4);
    TreeNode n3(3);
    TreeNode n1(1);
    TreeNode n2(2);
    n4.left = &n3;
    n3.left = &n1;
    n3.right = &n2;
    int ret = sol.maxSumBST(&n4);
    std::cout << "Max sum BST : " << ret << std::endl;
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
