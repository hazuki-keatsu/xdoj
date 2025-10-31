#include <iostream>
#include <vector>
#include <queue>
#include <string>

class BinTree
{
private:
    char data;
    BinTree *left;
    BinTree *right;

public:
    // default constructor
    BinTree() : data(0), left(nullptr), right(nullptr) {};

    BinTree(char data, BinTree *left, BinTree *right) : data(data), left(left), right(right) {};

    // getter and setter
    // int getData() const { return this->data; };
    // BinTree *getLeft() const { return this->left; };
    // BinTree *getRight() const { return this->right; };
    void setData(char data) { this->data = data; };
    void setLeft(BinTree *subTree) { this->left = subTree; };
    void setRight(BinTree *subTree) { this->right = subTree; };

    std::string toStringByBehind() {
        if (this == nullptr) {
            return "";
        }
        std::string result = "";
        if (left != nullptr) {
            result += left->toStringByBehind();
        }
        if (right != nullptr) {
            result += right->toStringByBehind();
        }
        result += data;
        return result;
    }
};

BinTree* parseFromTwoTraverseSequence(std::vector<char> mid, std::vector<char> frt) {
    if (mid.empty() || frt.empty() || mid.size() != frt.size()) {
        return nullptr;
    }

    char rootValue = frt.front();
    frt.erase(frt.begin());
    
    int idx_mid = 0;
    for (size_t i = 0; i < mid.size(); i++)
    {
        if (mid[i] == rootValue) {
            idx_mid = i;
            break;
        }
    }
    
    std::vector<char> front_part_mid(mid.begin(), mid.begin() + idx_mid);
    std::vector<char> behind_part_mid(mid.begin() + idx_mid + 1, mid.end());

    std::vector<char> front_part_frt(frt.begin(), frt.begin() + idx_mid);
    std::vector<char> behind_part_frt(frt.begin() + idx_mid, frt.end());

    BinTree* bt = new BinTree();
    bt->setData(rootValue);
    bt->setLeft(parseFromTwoTraverseSequence(front_part_mid, front_part_frt));
    bt->setRight(parseFromTwoTraverseSequence(behind_part_mid, behind_part_frt));

    return bt;
}

int main()
{
    std::vector<char> front;
    std::vector<char> middle;

    std::string line;

    if (!std::getline(std::cin, line)) return 1;
    for (char ch : line) {
        if (ch != ' ' && ch != '\r' && ch != '\n') front.push_back(ch);
    }

    if (!std::getline(std::cin, line)) return 1;
    for (char ch : line) {
        if (ch != ' ' && ch != '\r' && ch != '\n') middle.push_back(ch);
    }

    BinTree* bt = parseFromTwoTraverseSequence(middle, front);

    std::string str = bt->toStringByBehind();

    std::cout << str << std::endl;

    return 0;
}
