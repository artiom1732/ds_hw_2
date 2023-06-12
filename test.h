#ifndef _TEST_H
#define _TEST_H

class Node;
class Group;

class Disk_Node
{
public:
    int id; 
    int cd_amount;  //the number of cds of that type
    Disk_Node* up;   //the node above in the tree
    Group* group;
    int r;
    Disk_Node(int id,int amount):id(id),cd_amount(amount),up(nullptr),group(nullptr),r(0){}
    void AddGroup(Group* to_add){group = to_add;}
};

class Group
{
public:
    int group_id;
    int size;
    int column;
    int height;
    Disk_Node* head;
    Group(Disk_Node* head,int id):group_id(id),size(1),column(id),height(head->cd_amount),head(head){}
};

class UnionFind
{
public:
    int group_counter;
    Disk_Node** elements;
    Group** groups;
    int number_of_records;
    UnionFind(int* input,int input_size):group_counter(0),elements(new Disk_Node*[input_size]),groups(new Group*[input_size]),number_of_records(input_size)
    {
        for(int i=0;i<input_size;i++)
        {
            elements[i] = new Disk_Node(i,input[i]);
            groups[i] = new Group(elements[i],i);
            elements[i]->AddGroup(groups[i]);
            group_counter++;
        }
    }
    ~UnionFind(){delete[] elements;delete[] groups;}
    Group* Find(int a)
    {
        int sumR = 0;
        Disk_Node* root = elements[a];
        while(root->up!=nullptr)
        {
            sumR += root->r;
            root = root->up;
        }
        //path compression
        Disk_Node* temp = elements[a];
        int to_subtract = 0;
        while(temp!=root)
        {
            temp->r = sumR;
            to_subtract = to_subtract + temp->r;
            sumR = sumR - temp->r;
            Disk_Node* next = temp->up;
            temp->up = root;
            temp = next;
        }
        return root->group;
    }
    Group* Union(int b,int a)   // putting b on a
    {
        Group* A = Find(a);   //g_1 = A
        Group* B = Find(b);   //g_2 = B
        if(A->size < B->size)
        {
            A->head->up = B->head;
            B->size += A->size;
            B->group_id = ++group_counter;
            B->height += A->height;
            B->head->r += A->height;
            A->head->r = A->head->r - B->head->r;
            A->head->group = nullptr;
            return B;
        }
        B->head->up = A->head;
        A->size += B->size;
        A->group_id = ++group_counter;
        B->head->r = B->head->r + A->height - A->head->r;
        B->head->group = nullptr;
        return A;
    }
    bool Connected(int a,int b)
    {
        return Find(a) == Find(b);
    }
    void getPlace(int r_id,int* column,int* height)
    {
        Group* temp = Find(r_id);
        *column = temp->column;
        *height = 0;
        Disk_Node* root = elements[r_id];
        while(root!=nullptr)
        {
            *height += root->r;
            root = root->up;
        }
    }
};





class Costumer
{
public:
    int id;
    int phone_number;
    Costumer* next;
    bool vip;
    Costumer(int id,int number):id(id),phone_number(number),next(nullptr),vip(false){}
};

class VipCostumer
{
public:
    int id;
    int expenses;
    int prize;
    VipCostumer(int id):id(id),expenses(0),prize(0){}
};


//class HashTableException : public std::exception{};



static int HashFunc(int n,int m)
{
    return n%m;
}


class HashTable
{
public:
    int size;
    int max_size;
    Costumer** costumers;
    HashTable(int sz=10):size(0),max_size(sz),costumers(new Costumer*[sz])
    {
        for(int i=0;i<sz;i++)
        {
            costumers[i] = nullptr;
        }
    }
    ~HashTable(){delete[] costumers;}
    void largerTable(Costumer** to_resize)  
    {
        max_size = max_size * 2;
        Costumer** temp = costumers;
        costumers = new Costumer*[max_size];
        for(int i=0;i<size;i++)
        {
            costumers[i] = temp[i];
            temp[i] = nullptr;
        }
        delete[] temp;
    }
    void smallerTable(Costumer** to_resize) //not needed, we never reduce the number of costumers
    {
        max_size = max_size / 2;
        Costumer** temp = costumers;
        costumers = new Costumer*[max_size];
        for(int i=0;i<size;i++)
        {
            costumers[i] = temp[i];
            temp[i] = nullptr;
        }
        delete[] temp;
    }
    void addCostumer(int id,int number)
    {
        int index = HashFunc(id,max_size);
        if(costumers[index] == nullptr)
        {
            costumers[index] = new Costumer(id,number);
            size++;
            return;
        }
        Costumer* temp = costumers[index];
        while(temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = new Costumer(id,number);
        size++;
        if(size > max_size/2)
        {
            largerTable(costumers);
        }
        else if(size < max_size/4)
        {
            smallerTable(costumers);
        }
    }
    int getPhone(int id)
    {
        int index = HashFunc(id,max_size);
        if(costumers[index] != nullptr)
        {
            return costumers[index]->phone_number;
        }
        Costumer* temp = costumers[index];
        while(temp->next != nullptr)
        {
            temp = temp->next;
        }
        return temp->phone_number;
    }
};


static int max(int a,int b)
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