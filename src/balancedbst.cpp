// {"category": "H-1B", "notes": "Binary Search Tree is balanced"}

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>


//------------------------------------------------------------------------------
//
//  Write a function to check if a Binary Search Tree is balanced.
//
//  Source: http://www.bbc.com/news/blogs-trending-39127617
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
struct node
{
    int data;
    struct node* left;
    struct node* right;

    node(int data);
};


int height(struct node* node)
{
    if (node == nullptr)
    {
        return 0;
    }

    return 1 + max(height(node->left), height(node->right));
}


bool isBalanced(struct node* root)
{
    if (root == nullptr)
    {
        return true;
    }

    int lh = height(root->left);
    int rh = height(root->right);

    if (abs(lh - rh) <= 1 &&
        isBalanced(root->left) &&
        isBalanced(root->right))
    {
        return true;
    }

    return false;
}


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    struct node *root = &node(1);
    root->left = &node(2);
    root->right = &node(3);
    root->left->left = &node(4);
    root->left->right = &node(5);
    root->left->left->left = &node(8);

    if (isBalanced(root))
    {
        printf("Tree is balanced\n");
    }
    else
    {
        printf("Tree is not balanced\n");
    }

    return 0;
}


node::node(int data)
{
    this->data = data;
    this->left = nullptr;
    this->right = nullptr;
}
