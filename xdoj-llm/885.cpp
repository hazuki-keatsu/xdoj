#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode* insert(TreeNode* root, int val) {
    if (root == NULL) {
        return new TreeNode(val);
    }
    if (val < root->val) {
        root->left = insert(root->left, val);
    } else if (val > root->val) {
        root->right = insert(root->right, val);
    }
    return root;
}

TreeNode* buildTree(string seq) {
    TreeNode* root = NULL;
    for (int i = 0; i < seq.length(); i++) {
        int val = seq[i] - '0';
        root = insert(root, val);
    }
    return root;
}

bool isSameTree(TreeNode* t1, TreeNode* t2) {
    if (t1 == NULL && t2 == NULL) {
        return true;
    }
    if (t1 == NULL || t2 == NULL) {
        return false;
    }
    if (t1->val != t2->val) {
        return false;
    }
    return isSameTree(t1->left, t2->left) && isSameTree(t1->right, t2->right);
}

void freeTree(TreeNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

int main() {
    int n;
    std::vector<bool> v;
    while (cin >> n && n != 0) {
        string baseSeq;
        cin >> baseSeq;
        
        TreeNode* baseTree = buildTree(baseSeq);
        
        for (int i = 0; i < n; i++) {
            string seq;
            cin >> seq;
            
            TreeNode* tree = buildTree(seq);
            
            v.push_back(isSameTree(baseTree, tree));
            
            freeTree(tree);
        }
        
        // 释放基准树的内存
        freeTree(baseTree);
    }

    for(auto i : v) {
        cout << (i ? "YES" : "NO") << endl;
    }
    
    return 0;
}
