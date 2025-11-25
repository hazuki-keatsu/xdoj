#include <iostream>
#include <vector>

struct BTSeqNode
{
    int data;
    BTSeqNode *left;
    BTSeqNode *right;
};

class BTSeq
{
public:
    BTSeqNode *head;

    BTSeq()
    {
        head = nullptr;
    }

    // Insert value into BST (ignore duplicates)
    void insert(int data)
    {
        insertNode(head, data);
    }

    // Return in-order traversal as vector<int>
    std::vector<int> inorderVector() const
    {
        std::vector<int> v;
        inorderToVector(head, v);
        return v;
    }

    // Return pre-order traversal as vector<int>
    std::vector<int> preorderVector() const
    {
        std::vector<int> v;
        preorderToVector(head, v);
        return v;
    }

    // Return post-order traversal as vector<int>
    std::vector<int> postorderVector() const
    {
        std::vector<int> v;
        postorderToVector(head, v);
        return v;
    }

private:
    void insertNode(BTSeqNode *&node, int data)
    {
        if (node == nullptr)
        {
            node = new BTSeqNode{data, nullptr, nullptr};
            return;
        }
        if (data < node->data)
        {
            insertNode(node->left, data);
        }
        else if (data > node->data)
        {
            insertNode(node->right, data);
        }
    }

    void inorderToVector(BTSeqNode *node, std::vector<int> &v) const
    {
        if (!node)
            return;
        inorderToVector(node->left, v);
        v.push_back(node->data);
        inorderToVector(node->right, v);
    }

    void preorderToVector(BTSeqNode *node, std::vector<int> &v) const
    {
        if (!node)
            return;
        v.push_back(node->data);
        preorderToVector(node->left, v);
        preorderToVector(node->right, v);
    }

    void postorderToVector(BTSeqNode *node, std::vector<int> &v) const
    {
        if (!node)
            return;
        postorderToVector(node->left, v);
        postorderToVector(node->right, v);
        v.push_back(node->data);
    }
};

int main()
{
    int count;
    std::cin >> count;
    BTSeq tree;
    for(size_t i = 0; i < count; i++) {
        int temp;
        std::cin >> temp;
        tree.insert(temp);
    }

    std::vector<int> pre = tree.preorderVector();
    std::vector<int> in = tree.inorderVector();
    std::vector<int> post = tree.postorderVector();

    for(auto i : pre) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    for(auto i : in) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    for(auto i : post) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}