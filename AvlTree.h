#ifndef _AVL_TREE
#define _AVL_TREE

#include "VipCostumer.h"
#include "Costumer.h"

inline int max(int a,int b)
{
    return a > b ? a : b;
}
template<class T>
class TreeNode
{
public:
    int key;
    T* data;
    TreeNode* left;
    TreeNode* right;
    int height;
    TreeNode(int key,T* data):key(key),data(data),left(nullptr),right(nullptr),height(1){}
    ~TreeNode(){delete left;delete right;delete data;}
    int getHeight(TreeNode* a)
    {
        if(a == nullptr)
        {
            return 0;
        }
        return a->height;
    }
    TreeNode* insert(TreeNode* head,TreeNode* to_add)
    {
        if(head == nullptr)
        {
            return to_add;
        }
        else if(head->key > to_add->key)
        {
            head->left = insert(head->left,to_add);

        }
        else if(head->key < to_add->key)
        {  
            head->right = insert(head->right,to_add);
        }
        else
        {
            return head;
        }
        head->height = max(getHeight(head->left),getHeight(head->right)) + 1;
        return fixNode(head);
    }
    int calcBF(TreeNode* head)
    {
        if(head == nullptr)
        {
            return 0;
        }
        return getHeight(head->left) - getHeight(head->right);
    }
    TreeNode* fixNode(TreeNode* head)
    {
        int bf_head = calcBF(head);
        int bf_left = calcBF(head->left);
        int bf_right = calcBF(head->right);
        if(bf_head == 2 && bf_left >= 0)
        {
            return rotateLL(head);
        }
        else if(bf_head == -2 && bf_right <= 0)
        {
            return rotateRR(head);
        }
        else if(bf_head == 2 && bf_left < 0)
        {
            return rotateLR(head);
        }
        else if(bf_head == -2 && bf_right >= 0)
        {
            return rotateRL(head);
        }
        return head;
    }
    TreeNode* rotateRR(TreeNode* head)
    {
        TreeNode* A = head;
        TreeNode* B = head->right;
        A->right = B->left;
        B->left = A;
        A->height = max(getHeight(A->left),getHeight(A->right))+1;
        B->height = max(getHeight(B->left),getHeight(B->right))+1;
        return B;
    }
    TreeNode* rotateLL(TreeNode* head)
    {
        TreeNode* A = head;
        TreeNode* B = head->left;
        A->left = B->right;
        B->right = A;
        A->height = max(getHeight(A->left),getHeight(A->right))+1;
        B->height = max(getHeight(B->left),getHeight(B->right))+1;
        return B;
    }
    TreeNode* rotateRL(TreeNode* head)
    {
        TreeNode* temp = rotateLL(head->right);
        head->right = temp;
        head = rotateRR(head);
        return head;
    }
    TreeNode* rotateLR(TreeNode* head)
    {
        TreeNode* temp = rotateRR(head->left);
        head->left = temp;
        head = rotateLL(head);
        return head;
    }
    TreeNode* find(int key)
    {
        TreeNode* temp = this;
        while(temp!= nullptr)
        {
            if(temp->key == key)
            {
                return temp;
            }
            else if(temp->key > key)
            {
                return temp->left->find(key);
            }
            else 
            {
                return temp->right->find(key);
            }
        }
        return nullptr;
    }
};

template<class T>
class AVLTree
{
public:
    TreeNode<T>* head;
    AVLTree():head(nullptr){}
    ~AVLTree(){delete head;}
    void treeInsert(int key,T* data)
    {
        head = head->insert(head,new TreeNode<T>(key,data));
    }
    TreeNode<T>* Find(int id)
    {
        return head->find(id);
    }
};

#endif