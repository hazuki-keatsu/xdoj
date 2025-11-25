#include <iostream>
#include <vector>
#include <algorithm>

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

    // Return in-order traversal as vector<int>
    std::vector<int> inorderQueue() const
    {
        std::vector<int> v;
        inorderToQueue(head, v);
        return v;
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

    ReturnType getLeft(int target) const
    {
        if (!head)
        {
            ReturnType t;
            t.data = 0;
            t.status = NIL;
            return t;
        }
        BTSeqNode *curr = head;
        while (curr)
        {
            // compare curr->data (not assign), and use curr not head
            if (curr->data == target)
            {
                if (curr->left)
                {
                    ReturnType t;
                    t.data = curr->left->data;
                    t.status = GOT;
                    return t;
                }
                else
                {
                    ReturnType t;
                    t.data = 0;
                    t.status = NIL;
                    return t;
                }
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

    ReturnType getRight(int target) const
    {
        if (!head)
        {
            ReturnType t;
            t.data = 0;
            t.status = NIL;
            return t;
        }
        BTSeqNode *curr = head;
        while (curr)
        {
            if (curr->data == target)
            {
                if (curr->right)
                {
                    ReturnType t;
                    t.data = curr->right->data;
                    t.status = GOT;
                    return t;
                }
                else
                {
                    ReturnType t;
                    t.data = 0;
                    t.status = NIL;
                    return t;
                }
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

    void inorderToQueue(BTSeqNode *node, std::vector<int> &v) const
    {
        if (!node)
            return;
        inorderToQueue(node->left, v);
        v.push_back(node->data);
        inorderToQueue(node->right, v);
    }
};

int main()
{
    BTSeq tree;
    int count;
    std::cin >> count;
    for (size_t i = 0; i < count; i++)
    {
        int temp;
        std::cin >> temp;
        tree.insert(temp);
    }

    std::cin >> count;
    std::vector<int> buff;
    buff.reserve(count);
    for (size_t i = 0; i < count; i++)
    {
        int temp;
        std::cin >> temp;
        buff.push_back(temp);
    }

    for (auto i : buff)
    {
        ReturnType res = tree.getParent(i);
        if (res.status == GOT)
        {
            std::cout << res.data << " ";
        }
        else
        {
            std::cout << "NIL" << " ";
        }

        res = tree.getLeft(i);
        if (res.status == GOT)
        {
            std::cout << res.data << " ";
        }
        else
        {
            std::cout << "NIL" << " ";
        }

        res = tree.getRight(i);
        if (res.status == GOT)
        {
            std::cout << res.data << " ";
        }
        else
        {
            std::cout << "NIL" << " ";
        }

        std::vector<int> result = tree.inorderQueue();
        auto it = std::find(result.begin(), result.end(), i);
        // safety checks for predecessor and successor boundaries
        if (it == result.end())
        {
            // the queried value should exist in the tree per problem statement,
            // but print NIL for both if not found to avoid undefined behavior
            std::cout << "NIL NIL" << std::endl;
        }
        else
        {
            if (it == result.begin())
                std::cout << "NIL" << " ";
            else
                std::cout << *(it - 1) << " ";

            if ((it + 1) == result.end())
                std::cout << "NIL" << std::endl;
            else
                std::cout << *(it + 1) << std::endl;
        }
    }
    return 0;
}