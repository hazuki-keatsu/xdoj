#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <climits>

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

    void fromString(std::string input)
    {
        int pos = 0;
        head = buildFromStringRecursion(input, pos);
    }

private:
    BTSeqNode *buildFromStringRecursion(const std::string &input, int &pos)
    {
        if (pos >= (int)input.length())
            return nullptr;
        char ch = input[pos++];
        if (ch == '#')
        {
            return nullptr;
        }
        BTSeqNode *node = new BTSeqNode;
        node->data = ch - '0';
        node->left = buildFromStringRecursion(input, pos);
        node->right = buildFromStringRecursion(input, pos);
        return node;
    }

public:
    bool isBST() const
    {
        const long long NEG = LLONG_MIN;
        const long long POS = LLONG_MAX;
        return isBSTRec(head, NEG, POS);
    }

private:
    bool isBSTRec(BTSeqNode *node, long long minv, long long maxv) const
    {
        if (!node)
            return true;
        if (node->data <= minv || node->data >= maxv)
            return false;
        return isBSTRec(node->left, minv, node->data) && isBSTRec(node->right, node->data, maxv);
    }
};

int main()
{
    std::string input;
    std::cin >> input;
    BTSeq tree;
    tree.fromString(input);
    bool ok = tree.isBST();
    std::cout << (ok ? "yes" : "no") << std::endl;
    return 0;
}