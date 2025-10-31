#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 辅助函数：根据层次遍历和中序遍历构建二叉树
TreeNode* buildTreeHelper(vector<int>& levelOrder, int levelStart, int levelEnd,
                          vector<int>& inOrder, int inStart, int inEnd,
                          unordered_map<int, int>& inMap) {
    if (levelStart > levelEnd || inStart > inEnd) {
        return nullptr;
    }
    
    // 找到当前子树的根节点（在层次遍历中最早出现的节点）
    int rootVal = -1;
    int rootLevelIdx = levelEnd + 1;
    
    for (int i = levelStart; i <= levelEnd; i++) {
        int val = levelOrder[i];
        int inIdx = inMap[val];
        if (inIdx >= inStart && inIdx <= inEnd) {
            if (rootLevelIdx > i) {
                rootLevelIdx = i;
                rootVal = val;
            }
        }
    }
    
    if (rootVal == -1) return nullptr;
    
    TreeNode* root = new TreeNode(rootVal);
    int rootInIdx = inMap[rootVal];
    
    // 递归构建左右子树
    root->left = buildTreeHelper(levelOrder, levelStart, levelEnd, 
                                  inOrder, inStart, rootInIdx - 1, inMap);
    root->right = buildTreeHelper(levelOrder, levelStart, levelEnd,
                                   inOrder, rootInIdx + 1, inEnd, inMap);
    
    return root;
}

// 根据层次遍历和中序遍历构建二叉树
TreeNode* buildTree(vector<int>& levelOrder, vector<int>& inOrder) {
    if (levelOrder.empty()) return nullptr;
    
    // 建立中序遍历中值到索引的映射
    unordered_map<int, int> inMap;
    for (int i = 0; i < inOrder.size(); i++) {
        inMap[inOrder[i]] = i;
    }
    
    return buildTreeHelper(levelOrder, 0, levelOrder.size() - 1,
                          inOrder, 0, inOrder.size() - 1, inMap);
}

// 收集叶子节点（从左到右）
void collectLeaves(TreeNode* root, vector<int>& leaves) {
    if (!root) return;
    if (!root->left && !root->right) {
        leaves.push_back(root->val);
        return;
    }
    collectLeaves(root->left, leaves);
    collectLeaves(root->right, leaves);
}

// 先序遍历
void preOrder(TreeNode* root, vector<int>& result) {
    if (!root) return;
    result.push_back(root->val);
    preOrder(root->left, result);
    preOrder(root->right, result);
}

// 后序遍历
void postOrder(TreeNode* root, vector<int>& result) {
    if (!root) return;
    postOrder(root->left, result);
    postOrder(root->right, result);
    result.push_back(root->val);
}

int main() {
    int n;
    cin >> n;
    
    vector<int> levelOrder(n), inOrder(n);
    for (int i = 0; i < n; i++) {
        cin >> levelOrder[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> inOrder[i];
    }
    
    // 构建二叉树
    TreeNode* root = buildTree(levelOrder, inOrder);
    
    // 收集叶子节点
    vector<int> leaves;
    collectLeaves(root, leaves);
    
    // 先序遍历
    vector<int> preOrderResult;
    preOrder(root, preOrderResult);
    
    // 后序遍历
    vector<int> postOrderResult;
    postOrder(root, postOrderResult);
    
    // 输出结果
    for (int i = 0; i < leaves.size(); i++) {
        if (i > 0) cout << " ";
        cout << leaves[i];
    }
    cout << endl;
    
    for (int i = 0; i < preOrderResult.size(); i++) {
        if (i > 0) cout << " ";
        cout << preOrderResult[i];
    }
    cout << endl;
    
    for (int i = 0; i < postOrderResult.size(); i++) {
        if (i > 0) cout << " ";
        cout << postOrderResult[i];
    }
    cout << endl;
    
    return 0;
}
