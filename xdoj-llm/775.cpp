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

    BinTree(int data, BinTree *left, BinTree *right) : data(data), left(left), right(right) {};

    // getter and setter
    // int getData() const { return this->data; };
    // BinTree *getLeft() const { return this->left; };
    // BinTree *getRight() const { return this->right; };
    void setData(int data) { this->data = data; };
    void setLeft(BinTree *subTree) { this->left = subTree; };
    void setRight(BinTree *subTree) { this->right = subTree; };

    std::string toStringByLayer() {
        if (this == nullptr) {
            return "";
        }
        
        std::string result = "";
        std::queue<BinTree*> queue;
        queue.push(this);
        bool first = true;
        
        while (!queue.empty()) {
            BinTree* node = queue.front();
            queue.pop();
            
            if (!first) {
                result += " ";
            }
            result += std::to_string(node->data);
            first = false;
            
            if (node->left != nullptr) {
                queue.push(node->left);
            }
            
            if (node->right != nullptr) {
                queue.push(node->right);
            }
        }
        
        return result;
    }
};

BinTree* parseFromTwoTraverseSequence(std::vector<int> mid, std::vector<int> bhd) {
    if (mid.empty() || bhd.empty() || mid.size() != bhd.size()) {
        return nullptr;
    }

    int rootValue = bhd.back();
    bhd.pop_back();
    
    int idx_mid = 0;
    for (size_t i = 0; i < mid.size(); i++)
    {
        if (mid[i] == rootValue) {
            idx_mid = i;
            break;
        }
    }
    
    std::vector<int> front_part_mid(mid.begin(), mid.begin() + idx_mid);
    std::vector<int> behind_part_mid(mid.begin() + idx_mid + 1, mid.end());

    std::vector<int> front_part_bhd(bhd.begin(), bhd.begin() + idx_mid);
    std::vector<int> behind_part_bhd(bhd.begin() + idx_mid, bhd.end());

    BinTree* bt = new BinTree();
    bt->setData(rootValue);
    bt->setLeft(parseFromTwoTraverseSequence(front_part_mid, front_part_bhd));
    bt->setRight(parseFromTwoTraverseSequence(behind_part_mid, behind_part_bhd));

    return bt;
}

int main()
{
    int n;
    std::cin >> n;

    if (n < 1) {
        return 1;
    }

    std::vector<int> behind;
    behind.reserve(n);
    std::vector<int> middle;
    middle.reserve(n);

    for (size_t i = 0; i < n; i++) {
        int temp;
        std::cin >> temp;
        behind.push_back(temp);
    }

    for (size_t i = 0; i < n; i++) {
        int temp;
        std::cin >> temp;
        middle.push_back(temp);
    }

    BinTree* bt = parseFromTwoTraverseSequence(middle, behind);

    std::string str = bt->toStringByLayer();

    std::cout << str << std::endl;

    return 0;
}
