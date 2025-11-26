#include <iostream>
#include <vector>

struct BTSeqNode
{
    int data;
    BTSeqNode *left;
    BTSeqNode *right;
};

enum Status
{
    NIL,
    GOT
};

struct ReturnType
{
    int data = 0;
    Status status = NIL;
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

    // Return parent of node with value 'target'. If found, ReturnType.status==GOT and data is parent's value.
    // If target is root or not found, return status==NIL.
    ReturnType getParent(int target) const
    {
        if (!head)
        {
            ReturnType t;
            t.data = 0;
            t.status = NIL;
            return t;
        }
        if (head->data == target)
        {
            ReturnType t;
            t.data = 0;
            t.status = NIL;
            return t;
        } // root has no parent
        BTSeqNode *curr = head;
        while (curr)
        {
            // check if one of curr's children is target
            if (curr->left && curr->left->data == target)
            {
                ReturnType t;
                t.data = curr->data;
                t.status = GOT;
                return t;
            }
            if (curr->right && curr->right->data == target)
            {
                ReturnType t;
                t.data = curr->data;
                t.status = GOT;
                return t;
            }
            // traverse using BST property
            if (target < curr->data)
                curr = curr->left;
            else
                curr = curr->right;
        }
        {
            ReturnType t;
            t.data = 0;
            t.status = NIL;
            return t;
        }
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
};

int main() {
    BTSeq tree;
    int count;
    std::cin >> count;
    std::vector<int> v;
    for (int i = 0; i < count; i++) {
        int temp;
        std::cin >> temp;
        tree.insert(temp);
        v.push_back(temp);
    }

    for (auto i : v) {
        ReturnType rt = tree.getParent(i);
        if (rt.status != NIL) {
            std::cout << rt.data << std::endl;
        } else {
            std::cout << -1 << std::endl;
        }
    }

    return 0;
}