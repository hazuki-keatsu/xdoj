#include <stdio.h>
#include <stdlib.h>

typedef struct TNode {
    char Data;
    struct TNode *Left, *Right;
} TNode, *BinTree;

BinTree CreateBinTree();
int GetHeight(BinTree BT);

int main () {
    BinTree BT = CreateBinTree();
    printf("%d\n", GetHeight(BT));
    return 0;
}

BinTree CreateBinTree() {
    char ch;
    scanf("%c", &ch);
    if (ch == '#') {
        return NULL;
    } else {
        TNode *t = (TNode *)malloc(sizeof(TNode));
        if (!t) exit(0);
        t->Data = ch;
        t->Left = CreateBinTree();
        t->Right = CreateBinTree();
        return t;
    }
}

int GetHeight(BinTree BT) {
    if (BT == NULL) return 0;
    int lh = GetHeight(BT->Left);
    int rh = GetHeight(BT->Right);
    return (lh > rh ? lh : rh) + 1;
}