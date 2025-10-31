#include <iostream>
#include <vector>
#include <queue>
#include <string>

class BinTree
{
private:
    int data;
    BinTree *left;
    BinTree *right;

public:
    // default constructor
    BinTree() : data(0), left(nullptr), right(nullptr) {};

    BinTree(const BinTree &bt) : data(bt.data), left(nullptr), right(nullptr) {
        if (bt.left) left = new BinTree(*bt.left);
        if (bt.right) right = new BinTree(*bt.right);
    };

    BinTree(int data, BinTree *left, BinTree *right) : data(data), left(left), right(right) {};

    // getter and setter
    int getData() const { return this->data; };
    BinTree *getLeft() const { return this->left; };
    BinTree *getRight() const { return this->right; };
    void setData(int data) { this->data = data; };
    void setLeft(BinTree *subTree) { this->left = subTree; };
    void setRight(BinTree *subTree) { this->right = subTree; };

    std::vector<int> toStringByInOrder()
    {
        std::vector<int> result;
        if (left != nullptr)
        {
            auto temp = left->toStringByInOrder();
            result.insert(result.end(), temp.begin(), temp.end());
        }
        result.push_back(data);
        if (right != nullptr)
        {
            auto temp = right->toStringByInOrder();
            result.insert(result.end(), temp.begin(), temp.end());
        }
        
        return result;
    }
};

BinTree *parseFromTwoTraverseSequence(std::vector<int> mid, std::vector<int> frt)
{
    if (mid.empty() || frt.empty() || mid.size() != frt.size())
    {
        return nullptr;
    }

    int rootValue = frt.front();
    frt.erase(frt.begin());

    int idx_mid = 0;
    for (size_t i = 0; i < mid.size(); i++)
    {
        if (mid[i] == rootValue)
        {
            idx_mid = i;
            break;
        }
    }

    std::vector<int> front_part_mid(mid.begin(), mid.begin() + idx_mid);
    std::vector<int> behind_part_mid(mid.begin() + idx_mid + 1, mid.end());

    std::vector<int> front_part_frt(frt.begin(), frt.begin() + idx_mid);
    std::vector<int> behind_part_frt(frt.begin() + idx_mid, frt.end());

    BinTree *bt = new BinTree();
    bt->setData(rootValue);
    bt->setLeft(parseFromTwoTraverseSequence(front_part_mid, front_part_frt));
    bt->setRight(parseFromTwoTraverseSequence(behind_part_mid, behind_part_frt));

    return bt;
}

// 辅助函数：计算以bt为根的子树所有节点的和
int calcSubtreeSum(BinTree *bt)
{
    if (bt == nullptr) return 0;
    return bt->getData() + calcSubtreeSum(bt->getLeft()) + calcSubtreeSum(bt->getRight());
}

BinTree *transformToSumTree(BinTree *bt)
{
    if (bt == nullptr) return nullptr;

    BinTree *leftSum = transformToSumTree(bt->getLeft());
    BinTree *rightSum = transformToSumTree(bt->getRight());

    int leftOriginalSum = calcSubtreeSum(bt->getLeft());
    int rightOriginalSum = calcSubtreeSum(bt->getRight());
    
    int total = leftOriginalSum + rightOriginalSum;

    BinTree *node = new BinTree(total, leftSum, rightSum);
    return node;
}

int main()
{
    int count;

    std::cin >> count;

    std::vector<int> front;
    std::vector<int> middle;

    for (size_t i = 0; i < count; i++)
    {
        int temp;
        std::cin >> temp;
        front.push_back(temp);
    }
    for (size_t i = 0; i < count; i++)
    {
        int temp;
        std::cin >> temp;
        middle.push_back(temp);
    }

    BinTree *bt = parseFromTwoTraverseSequence(middle, front);
    BinTree *sum = transformToSumTree(bt);

    auto inorder = sum->toStringByInOrder();
    for (size_t i = 0; i < inorder.size(); ++i)
    {
        if (i) std::cout << " ";
        std::cout << inorder[i];
    }
    std::cout << std::endl;

    return 0;
}
