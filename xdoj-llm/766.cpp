#include <iostream>

struct BiTreeNode {
    int data;
    BiTreeNode* left;
    BiTreeNode* right;
};

void insertBiTree(BiTreeNode*& head, int data) {
    if (!head) {
        BiTreeNode* node = new BiTreeNode;
        node->data = data;
        node->left = nullptr;
        node->right = nullptr;
        head = node;
    } else if (data < head->data) {
        insertBiTree(head->left, data);
    } else {
        insertBiTree(head->right, data);
    }
}

BiTreeNode* createBiTree(int count) {
    BiTreeNode* head = nullptr;
    for (size_t i = 0; i < count; i++) {
        int temp;
        std::cin >> temp;
        insertBiTree(head, temp);
    }
    return head;
}

void inOrderTraverse(BiTreeNode* head) {
    if (!head) {
        return;
    }
    inOrderTraverse(head->left);
    std::cout << head->data << " ";
    inOrderTraverse(head->right);
}

void destroyBiTree(BiTreeNode* head) {
    if (head == nullptr) {
        return;
    }
    destroyBiTree(head->left);
    destroyBiTree(head->right);
    delete head;
}

int main() {
    int count;
    std::cin >> count;
    BiTreeNode* root = createBiTree(count);
    inOrderTraverse(root);
    std::cout << std::endl;

    destroyBiTree(root);

    return 0;
} 