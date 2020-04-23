#pragma once
#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <vector>
using namespace std;

struct BinaryTree
{
    struct TreeNode
    {
    private:
        int value;
        TreeNode * left, * right;
    public:
        TreeNode() : value(0), left(nullptr), right(nullptr) {}
        TreeNode(const int value) : value(value), left(nullptr), right(nullptr) {}
        ~TreeNode()
        {
            cout << '*';
            delete left;
            delete right;
        }
        int getValue() const { return value; }
        void setValue(const int value) { this->value = value; }
        TreeNode* getLeft() const { return left; }
        void setLeft(TreeNode* left) { this->left = left; }
        TreeNode* getRight() const { return right; }
        void setRight(TreeNode* right) { this->right = right; }
    };
    BinaryTree() : firstNode(nullptr) {}
    BinaryTree(int firstValue) : firstNode(new TreeNode(firstValue)) {}
    BinaryTree(TreeNode* node) : firstNode(node) {}
    ~BinaryTree() { delete firstNode; }
    void Insert(int value);
    TreeNode* Search(int value) const;
    void Print() const;
    TreeNode* getFirstNode() { return firstNode; }
private:
    TreeNode* firstNode;
    void Insert(TreeNode* node, int value);
    bool Search(TreeNode* node, int value) const;
};

#endif // !BINARYTREE_H

