//  BSTHeader.h
//  CS300_Homework3
//
//  Created by Yusuf Erkam Köksal on 28.04.2023.

#ifndef BSTHeader_h
#define BSTHeader_h
#include <string>
#include <iostream>
using namespace std;


template <class T>
struct BSTNode
{
    T contact;
    BSTNode *left;
    BSTNode *right;

    BSTNode(const T& theContact, BSTNode* lt, BSTNode* rt)
      : contact(theContact), left(lt), right(rt) {}
};

template <class T>
class BinarySearchTree
{
private:

    void insertContact(T iContact, BSTNode<T>* &iNode);
    void removeContact( const T& dContact, BSTNode<T>* &iNode) const;
    T& contactAt(BSTNode<T>* ptr);
    void printTreeInOrder( BSTNode<T> *t) const;
    void makeEmpty (BSTNode<T>* &t) const;
    BSTNode<T>* findMin( BSTNode<T> *t) const;
    void printTreePreOrder(BSTNode<T> *t) const;
    bool isBalanced(BSTNode<T>* node) const;
    void printTreeInOrderToFile(BSTNode<T>* t, ofstream& outFile) const;
    void printTreePreOrderToFile(BSTNode<T>* t, ofstream& outFile) const;

public:
    BinarySearchTree();
    ~BinarySearchTree();
    BSTNode<T>* root;
    int getHeight(BSTNode<T>* node) const;
    void insertContact(const T& iContact);
    const T& findMin() const;
    bool searchContact(string fullName, T& x);
    void printTreeInOrder() const;
    bool isEmpty() const;
    void removeContact(const T& dContact);
    void makeEmpty();
    void printTreePreOrder() const;
    void drawTreeHelper(BSTNode<T>* node, string indent, bool last) const;
    void drawTree() const;
    BSTNode<T>* getRoot();
    bool isBalanced() const;
    void printTreeInOrderToFile(ofstream& outFile) const;
    void printTreePreOrderToFile(ofstream& outFile) const;
    void drawTreeToFileHelper(ofstream& file, BSTNode<T>* node, string indent, bool last);

};

template<class T>
void BinarySearchTree<T>::printTreePreOrder() const {
    if(!isEmpty()){
        printTreePreOrder(root);
    }
}

template<class T>
void BinarySearchTree<T>::printTreePreOrder(BSTNode<T> *t) const {
    if(t != NULL) {
        cout << t->contact.fullname <<" "<<t->contact.phone <<" "<<t->contact.city << endl;
        printTreePreOrder(t->left);
        printTreePreOrder(t->right);
    }
}

template<class T>
BSTNode<T>* BinarySearchTree<T>::getRoot(){
    if (root == NULL){
        return nullptr;
    }
    return root;
}

template <class T>
BinarySearchTree<T>::BinarySearchTree()
{
    root = NULL;
}

template <class T>
BinarySearchTree<T>::~BinarySearchTree()
{
    makeEmpty();
}

template <class T>
void BinarySearchTree<T>::printTreeInOrder() const
{
    if(!isEmpty()){
        printTreeInOrder(root);
    }
}

template <class T>
void BinarySearchTree<T>::printTreeInOrder(BSTNode<T> *t) const
{
    if(t != NULL) {
        printTreeInOrder(t->left);
        cout << t->contact.fullname <<" "<<t->contact.phone <<" "<<t->contact.city << endl;
        printTreeInOrder(t->right);
    }
}

template <class T>
bool BinarySearchTree<T>::isEmpty() const
        {
            return root == NULL;
        }

template <class T>
void BinarySearchTree<T>::insertContact(const T& iContact)
{
    insertContact(iContact, root);
}

template <class T>
void BinarySearchTree<T>::insertContact(T iContact,  BSTNode<T>* &iNode)
{
    if (iNode == NULL) {
        iNode = new BSTNode<T>(iContact, NULL, NULL);
    }
    else if (iContact.fullname < iNode->contact.fullname) {
        insertContact(iContact, iNode->left);
    }
    else if (iNode->contact.fullname < iContact.fullname) {
        insertContact(iContact, iNode->right);
    }
    else { 
    }
}


template <class T>
T& BinarySearchTree<T>::contactAt(BSTNode<T>* ptr)
{
            if( ptr == NULL )
                return NULL;
            else
                return ptr->contact;
}

template <class T>
bool BinarySearchTree<T>::searchContact(string cFullName, T& x){
    bool found = false;
    if(isEmpty())
    {
        cout<<"";
    }
    BSTNode<T>* curr;
    BSTNode<T>* parent;
    curr = root;
    parent = (BSTNode<T>*)NULL;
    while(curr != NULL)
    {
        if((curr->contact.fullname).find(cFullName) == 0)
        {
            if(curr->contact.fullname == cFullName){
                cout<<"The name you entered is found in database"<<endl;
                cout<<curr->contact.fullname<<" "<<curr->contact.phone<<" "<<curr->contact.city<<endl;
                found = true;
                break;
            }
            else{
                cout<<curr->contact.fullname<<" "<<curr->contact.phone<<" "<<curr->contact.city<<endl;
                parent = curr;
                if(cFullName > curr->contact.fullname && curr ->right != nullptr) {curr = curr->right;}
                else if (cFullName < curr->contact.fullname && curr ->left != nullptr) {curr = curr->left;}
                found = true;
            }
        }
        else
        {
            parent = curr;
            if(cFullName > curr->contact.fullname && curr ->right != nullptr) {curr = curr->right;}
            else if (cFullName < curr->contact.fullname && curr ->left != nullptr) {curr = curr->left;}
        }
    }
    if(!found)
    {
        cout<<"Contact cannot found."<<endl;
        return false;
    }
    else{
        x = curr->contact;
        return true;
    }
}

template <class T>
void BinarySearchTree<T>::makeEmpty( BSTNode<T>* &t) const
        {
            if(t != NULL)
            {
                makeEmpty(t->left);
                makeEmpty(t->right);
                delete t;
            }
            t = NULL;
        }

template <class T>
void BinarySearchTree<T>::makeEmpty()
{
    makeEmpty(root);
}

template <class T>
void BinarySearchTree<T>::removeContact(const T& dContact )
{
    removeContact(dContact, root);
}

template <class T>
void BinarySearchTree<T>::removeContact(const T& dContact, BSTNode<T>* &dNode) const
        {
            if( dNode == NULL )
                return;   // Item not found; do nothing
            if( dContact.fullname < dNode->contact.fullname)
                removeContact(dContact, dNode->left);
            else if(dNode->contact.fullname < dContact.fullname )
                removeContact( dContact, dNode->right );
            else if( dNode->left != NULL && dNode->right != NULL ) // Two children
            {
                dNode->contact = findMin(dNode->right)->contact;
                removeContact(dNode->contact, dNode->right);
            }
            else
            {
                BSTNode<T>* oldNode = dNode;
                dNode = (dNode->left != NULL) ? dNode->left : dNode->right;
                delete oldNode;
            }
        }

template <class T>
const T& BinarySearchTree<T>::findMin() const
{
    return contactAt(findMin(root));
}

template <class T>
BSTNode<T>* BinarySearchTree<T>::findMin(BSTNode<T> *t) const
{
    if(t == NULL){
        return NULL;
    }
    if(t->left == NULL){
        return t;
    }
    return findMin(t->left);
}

template<class T>
void BinarySearchTree<T>::drawTreeHelper(BSTNode<T>* node, string indent, bool last) const {
    cout << indent;
    if (last) {
        cout << "|-- ";
        indent += "   ";
    }
    else {
        cout << "|-- ";
        indent += "|  ";
    }
    cout << node->contact.fullname << endl;

    if (node->left) {
        drawTreeHelper(node->left, indent, node->right == NULL);
    }

    if (node->right) {
        drawTreeHelper(node->right, indent, true);
    }
}

template<class T>
void BinarySearchTree<T>::drawTree() const{
    drawTreeHelper(root, "", true);
}

template <class T>
int BinarySearchTree<T>::getHeight(BSTNode<T>* node) const
{
    if (node == nullptr) {
        return -1;
    }

    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);

    return 1 + max(leftHeight, rightHeight);
}

template <class T>
bool BinarySearchTree<T>::isBalanced(BSTNode<T>* node) const
{
    if (node == nullptr) {
        return true;
    }

    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);

    if (abs(leftHeight - rightHeight) <= 1 && isBalanced(node->left) && isBalanced(node->right)) {
        return true;
    }

    return false;
}

template <class T>
bool BinarySearchTree<T>::isBalanced() const
{
    return isBalanced(root);
}

template<class T>
void BinarySearchTree<T>::printTreeInOrderToFile(ofstream& outFile) const {
    if (root != NULL) {
        printTreeInOrderToFile(root, outFile);
    }
}

template<class T>
void BinarySearchTree<T>::printTreeInOrderToFile(BSTNode<T>* t, ofstream& outFile) const {
    if (t != NULL) {
        printTreeInOrderToFile(t->left, outFile);
        outFile << t->contact.fullname << " " << t->contact.phone << " " << t->contact.city << endl;
        printTreeInOrderToFile(t->right, outFile);
    }
}

template<class T>
void BinarySearchTree<T>::printTreePreOrderToFile(ofstream& outFile) const {
    if (root != NULL) {
        printTreePreOrderToFile(root, outFile);
    }
}

template<class T>
void BinarySearchTree<T>::printTreePreOrderToFile(BSTNode<T>* t, ofstream& outFile) const {
    if (t != NULL) {
        
        outFile << t->contact.fullname << " " << t->contact.phone << " " << t->contact.city << endl;
        printTreePreOrderToFile(t->left, outFile);
        printTreePreOrderToFile(t->right, outFile);
    }
}

template<class T>
void BinarySearchTree<T>::drawTreeToFileHelper(ofstream& file, BSTNode<T>* node, string indent, bool last) {
    file << indent;
    if (last) {
        file << "|__ ";
        indent += "   ";
    }
    else {
        file << "|-- ";
        indent += "|  ";
    }
    file << node->contact.fullname << std::endl;

    if (node->left) {
        drawTreeToFileHelper(file, node->left, indent, node->right == NULL);
    }

    if (node->right) {
        drawTreeToFileHelper(file, node->right, indent, true);
    }
}

#endif /* BSTHeader_h */
