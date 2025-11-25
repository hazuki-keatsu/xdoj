#include <iostream>
#include <vector>
#include <climits>

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};


struct Tripair
{
    int val;
    int left;
    int right;
    Tripair(int val, int left, int right) : val(val), left(left), right(right) {}
};  

class Tree {
    TreeNode* _head;
    std::vector<Tripair> _rawNodes;
public:
    Tree(std::vector<Tripair> rawNodes, int root) {
        if (root < 1 || root > (int)rawNodes.size()) {
            _head = nullptr;
            return;
        }
        _rawNodes = rawNodes;
        _head = buildFromMapRecursion(_rawNodes[root - 1]);
    }

    TreeNode* getHead() const {
        return _head;
    }

    bool isBST() const {
        return isBSTHelper(_head, LLONG_MIN, LLONG_MAX);
    }

private:
    TreeNode* buildFromMapRecursion(const Tripair& tp) {
        TreeNode* curr = new TreeNode(tp.val);
        if (tp.left != 0) {
            curr->left = buildFromMapRecursion(_rawNodes[tp.left - 1]);
        }
        if (tp.right != 0) {
            curr->right = buildFromMapRecursion(_rawNodes[tp.right - 1]);
        }
        return curr;
    }

    bool isBSTHelper(TreeNode* node, long long minVal, long long maxVal) const {
        if (!node) return true;
        if (node->val <= minVal || node->val >= maxVal) return false;
        return isBSTHelper(node->left, minVal, node->val) && 
               isBSTHelper(node->right, node->val, maxVal);
    }
};

int main() {
    int count, root;
    std::cin >> count >> root;
    std::vector<Tripair> v;
    for (int i = 0; i < count; i++) {
        int val, left, right;
        std::cin >> val >> left >> right;
        v.push_back(Tripair(val, left, right));
    }

    Tree tree(v, root);
    std::cout << (tree.isBST() ? "true" : "false") << std::endl;
    return 0;
}