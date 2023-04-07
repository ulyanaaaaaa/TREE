
#include <iostream>

using namespace std;

struct Tree {
    int info;
    string fio;
    Tree* left, * right;
};

void inOrder(Tree* node) {
    if (node != NULL) {
        inOrder(node->left);
        cout << node->info << ": " << node->fio << endl;
        inOrder(node->right);
    }
}

void preOrder(Tree* node) {
    if (node != NULL) {
        cout << node->info << ": " << node->fio << endl;
        preOrder(node->left);
        preOrder(node->right);
    }
}

void postOrder(Tree* node) {
    if (node != NULL) {
        postOrder(node->left);
        postOrder(node->right);
        cout << node->info << ": " << node->fio << endl;
    }
}

Tree* createNode(int info, string fio) {
    Tree* newNode = new Tree;
    newNode->info = info;
    newNode->fio = fio;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

Tree* insertNode(Tree* node, int info, string fio) {
    if (node == nullptr) {
        node = createNode(info, fio);
        return node;
    }
    if (info < node->info) {
        node->left = insertNode(node->left, info, fio);
    }
    else if (info > node->info) {
        node->right = insertNode(node->right, info, fio);
    }
    return node;
}

Tree* Del_Info(Tree* root, int info) {
    Tree * Prev_Del, * R, * Prev_R, *Del;
    Del = root;
    Prev_Del = NULL;
    
    while (Del != NULL && Del->info != info) {
        Prev_Del = Del;
        if (Del->info > info) Del = Del->left;
        else Del = Del->right;
    }
    if (Del == NULL) { 
        cout << "NOT Key!" << endl;
        return root;
    }
    
    if (Del->right == NULL) R = Del->left;
    else
        if (Del->left == NULL) R = Del->right;
        else {
            
            Prev_R = Del;
            R = Del->left;
            while (R->right != NULL) {
                Prev_R = R;
                R = R->right;
            }
            
            if (Prev_R == Del) R->right = Del->right;
            else {
                R->right = Del->right;
                Prev_R->right = R->left;
                R->left = Prev_R;
            }
        }
    if (Del == root) root = R; 
    else
        if (root->info < Prev_Del->info)
            Prev_Del->left = R; 
        else Prev_Del->right = R; 
    delete Del;
    return root;
}


void delTree(Tree* t) {
    if (t != NULL) {
        delTree(t->left);
        delTree(t->right);
        delete t;
    }
}

int listCount(Tree* root)
{
    int result;
    if (root == NULL) result = 0;
    else if ((root->left == NULL) && (root->right == NULL)) result = 1;
    else result = listCount(root->left) + listCount(root->right);
    return result;
}

int searchByKey(Tree* root, int key)
{
    if (root == NULL) return 1;
    if (root->info == key) return root->info;
    if (key < root->info) return searchByKey(root->left, key);
    else return searchByKey(root->right, key);
}

int main()
{
    int menu;
    int aInfo;
    string fio;
    cout << "Enter number and fio" << endl;
    cin >> aInfo;
    cin >> fio;
    Tree* root = createNode(aInfo, fio);
    Tree* aTree = NULL;
    while (true) {
        cout << "Menu:" << endl;
        cout << "9. Create tree" << endl;
        cout << "1. Add element" << endl;
        cout << "2. Delete element" << endl;
        cout << "3. Balance tree" << endl;
        cout << "4. Search" << endl;
        cout << "5. View forward" << endl;
        cout << "6. View backward" << endl;
        cout << "7. View in ascending order" << endl;
        cout << "8. Fint the number of leaves" << endl;
        cout << "0. Exit" << endl;
        cin >> menu;
        switch (menu) {

        case 1:
            cout << "Enter number and fio" << endl;
            cin >> aInfo;
            cin >> fio;
            insertNode(root, aInfo, fio);
            system("pause");
            break;
        case 2:
            cout << "Enter info for delete" << endl;
            cin >> aInfo;
            Del_Info(root, aInfo);
            system("pause");
            break;
        case 3:
            system("pause");
            break;
        case 4:
            int key;
            cout << "Enter number for search" << endl;
            cin >> key;
            cout << searchByKey(root, key) + 1 << endl;
            system("pause");
            break;
        case 5:
            inOrder(root);
            system("pause");
            break;
        case 6:
            postOrder(root);
            system("pause");
            break;
        case 7:
            preOrder(root);
            system("pause");
            break;
        case 8:
            cout << listCount(root) << endl;
            system("pause");
            break;
        case 0:
            delTree(root);
            return 0;
        }
    }
}

