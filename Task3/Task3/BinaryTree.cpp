#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include "BinaryTree.h"
using namespace std;
void BinaryTree::Insert(int value)
{
    if (firstNode)
    {
        auto node = firstNode;
        while (true)
        {
            if (node->getValue() > value)
            {
                auto left = node->getLeft();
                if (left)
                {
                    node = left;
                    continue;
                }
                else
                {
                    Insert(node, value);
                    break;
                }
            }
            auto right = node->getRight();
            if (right)
                node = right;
            else
            {
                Insert(node, value);
                break;
            }
        }
    }
    else firstNode = new TreeNode(value);
}
BinaryTree::TreeNode* BinaryTree::Search(int value) const
{
    if (firstNode)
    {
        auto node = firstNode;
        while (!Search(node, value))
        {
            auto nodeValue = node->getValue();
            if (nodeValue > value)
            {
                auto left = node->getLeft();
                if (left)
                    node = left;
                else
                    return nullptr;
            }
            else
            {
                auto right = node->getRight();
                if (right)
                    node = right;
                else
                    return nullptr;
            }
        }
        return node;
    }
    return nullptr;
}
void BinaryTree::Print() const
{
    if (firstNode)
    {
        TreeNode** nodes = new TreeNode*[1]{ firstNode };
        int nodesCurrentCount = 1;
        for(int level = 1; nodesCurrentCount; level++)
        {
            TreeNode** newNodes = new TreeNode * [nodesCurrentCount * 2];
            int index = 0;
            cout << "Вершины на уровне " << level << ":" << endl;
            for(int i = 0; i < nodesCurrentCount; i++)
            {
                auto node = nodes[i];
                cout << node->getValue() << ' ';
                if (node->getLeft())
                    newNodes[index++] = node->getLeft();
                if (node->getRight())
                    newNodes[index++] = node->getRight();
            }
            nodesCurrentCount = index;
            delete[] nodes;
            nodes = newNodes;
            cout << endl;
            if (index == 0)
                cout << "Высота дерева = " << level << endl;
        }
        delete[] nodes;
    }
    else cout << "Дерево пустое";
}
void BinaryTree::Insert(TreeNode* node, int value)
{
    assert(node);
    if (node->getValue() > value)
    {
        assert(node->getLeft() == nullptr);
        node->setLeft(new TreeNode(value));
    }
    else
    {
        assert(node->getRight() == nullptr);
        node->setRight(new TreeNode(value));
    }
}
bool BinaryTree::Search(TreeNode* node, int value) const
{
    assert(node);
    return node->getValue() == value;
}
