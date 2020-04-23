#include <iostream>
#include <cassert>
#include <vector>
#include "BinaryTree.h"
using namespace std;

BinaryTree::TreeNode* CreateMinimalBST1(int* arr, int firstIndex, int lastIndex)
{
    int count = lastIndex - firstIndex + 1;
    int val = arr[firstIndex + count / 2];
    BinaryTree::TreeNode* res = new BinaryTree::TreeNode(val);
    if (count != 1)
        res->setLeft(CreateMinimalBST1(arr, firstIndex, firstIndex + count / 2 - 1));
    if (count > 2)
        res->setRight(CreateMinimalBST1(arr, firstIndex + count / 2 + 1, lastIndex));
    return res;
}

int main()
{
    setlocale(LC_ALL, "ru");
    
    auto arr = new int[10]{ 1, 2, 3, 5, 7, 9, 10, 20, 25, 30 };
    auto res = new BinaryTree(CreateMinimalBST1(arr, 0, 10 - 1));

    for (int i = 0; i < 10; i++)
        assert(res->Search(arr[i])->getValue() == arr[i]);

    res->Print();
    
    delete res;
}
