//
//  AVLHeader.h
//  CS300_Homework3
//
//  Created by Yusuf Erkam Köksal on 28.04.2023.
//

#ifndef AVLHeader_h
#define AVLHeader_h
#include <string>
#include <iostream>
using namespace std;

template <class T>
struct AVLNode
{
    T contact; // Current contact
    AVLNode* left; // Left node of contact
    AVLNode* right; // Right node of contact
    int height; // height of the currentNode respect to its location in the AVL tree

    AVLNode(T theContact, AVLNode* left, AVLNode* right, int height = 0)
        : contact(theContact), left(left), right(right), height(height) {}
};

template <class T>
class AVLTree {
private:
    int findMax(int lhs, int rhs);
    void insertContact(T x, AVLNode<T>* &ptr);
    T& contactAt(AVLNode<T>* ptr);
    void printTreeInOrder( AVLNode<T> *t) const;
    void removeContact(const T& x, AVLNode<T>* &t);
    AVLNode<T>* findMin(AVLNode<T> *t) const;
    void makeEmpty (AVLNode<T>* &ptr);
    void printTreePreOrder(AVLNode<T>* t) const;
    bool isBalanced(AVLNode<T>* node);
    void printTreeInOrderToFile(AVLNode<T>* t, ofstream& outFile) const;
    void printTreePreOrderToFile(AVLNode<T>* t, ofstream& outFile) const;
    
public:
    AVLNode<T>* root;
    AVLTree();
    ~AVLTree();
    void insertContact(T x);
    int getHeight(AVLNode<T>* ptr);
    void rotateWithRightChild( AVLNode<T>* &k1);
    void rotateWithLeftChild( AVLNode<T>* &k2);
    void doubleWithLeftChild( AVLNode<T>* &k3);
    void doubleWithRightChild( AVLNode<T>* &k1);
    void printTreeInOrder() const;
    bool isEmpty() const;
    void removeContact( const T& x);
    void getBalanced(AVLNode<T>* &t);
    const T& findMin() const;
    bool searchContact(string fullname, T& x);
    void makeEmpty();
    void printTreePreOrder() const;
    void drawTree() const;
    void drawTreeHelper(AVLNode<T>* node,string indent, bool last) const;
    AVLNode<T>* getRoot() const;
    bool isBalanced();
    void printTreeInOrderToFile(ofstream& outFile) const;
    void printTreePreOrderToFile(ofstream& outFile) const;
    void drawTreeToFileHelper(ofstream& file, AVLNode<T>* node, std::string indent, bool last);
    


};


template <class T>
AVLTree<T>::AVLTree()
{
    root = NULL;
}

template <class T>
AVLTree<T>::~AVLTree()
{
    makeEmpty();
}

template<class T>
AVLNode<T>* AVLTree<T>::getRoot() const{
    if (root == NULL){
        return nullptr;
    }
    return root;
}

template <class T>
int AVLTree<T>::getHeight(AVLNode<T>* ptr)
{
    if (ptr == NULL){
        return -1;
    }
    return ptr->height;
}

template <class Temp>
void AVLTree<Temp>::printTreeInOrder() const
{
    if(!isEmpty()){
        printTreeInOrder(root);
    }
}

template <class T>
void AVLTree<T>::printTreeInOrder(AVLNode<T> *t) const //Inorder traversal !!!!!!!
{
    if( t != NULL )
    {
        printTreeInOrder(t->left);
        cout << t->contact.fullname <<" "<<t->contact.phone <<" "<<t->contact.city << endl;
        printTreeInOrder(t->right);
    }
}

template <class T>
void AVLTree<T>::printTreePreOrder() const{
    if(!isEmpty()){
        printTreePreOrder(root);
    }
}

template <class T>
void AVLTree<T>::printTreePreOrder(AVLNode<T> *t) const{
    if( t != NULL )
    {
        cout << t->contact.fullname <<" "<<t->contact.phone <<" "<<t->contact.city << endl;
        printTreePreOrder(t->left);
        printTreePreOrder(t->right);
    }
}

template <class T>
int AVLTree<T>::findMax(int lhs, int rhs)
{
    if (lhs > rhs){
        return lhs;
    }
    return rhs;
}

template <class T>
bool AVLTree<T>::isEmpty() const
{
    return root == NULL;
}

template <class T>
void AVLTree<T>::rotateWithLeftChild(AVLNode<T>* &k2)
{
    AVLNode<T>* k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = findMax(getHeight(k2->left), getHeight(k2->right)) + 1;
    k1->height = findMax(getHeight(k1->left), k2->height) + 1;
    k2 = k1;
}

template <class T>
void AVLTree<T>::rotateWithRightChild(AVLNode<T>* & k1)
{
    AVLNode<T>* k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = findMax(getHeight(k1->left), getHeight(k1->right)) + 1;
    k2->height = findMax(getHeight(k2->right), k1->height) + 1;
    k1 = k2;
}
template <class T>
void AVLTree<T>::doubleWithLeftChild(AVLNode<T>* &k3)
{
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}
template <class T>
void AVLTree<T>::doubleWithRightChild(AVLNode<T> * & k1)
{
    rotateWithLeftChild(k1->right);
    rotateWithRightChild(k1);
}
template <class T>
void AVLTree<T>::insertContact(T iContact, AVLNode<T>*& ptr)
{
    if (ptr == NULL) {
        ptr = new AVLNode<T>(iContact, NULL, NULL);
    } else if (iContact.fullname < ptr->contact.fullname) {
        insertContact(iContact, ptr->left);
        if (getHeight(ptr->left) - getHeight(ptr->right) == 2) {
            if (iContact.fullname < ptr->left->contact.fullname) {
                rotateWithLeftChild(ptr);
            } else {
                doubleWithLeftChild(ptr);
            }
        }
    } else if (ptr->contact.fullname < iContact.fullname) {
        insertContact(iContact, ptr->right);
        if (getHeight(ptr->right) - getHeight(ptr->left) == 2) {
            if (ptr->right->contact.fullname < iContact.fullname) {
                rotateWithRightChild(ptr);
            } else {
                doubleWithRightChild(ptr);
            }
        }
    }

    ptr->height = findMax(getHeight(ptr->left), getHeight(ptr->right)) + 1;
}

template <class T>
void AVLTree<T>::insertContact(T iContact)
{
    insertContact(iContact, root);
}

template <class T>
T & AVLTree<T>::contactAt( AVLNode<T>* ptr )
{
    return ptr -> contact;
}
    
template <class T>
bool AVLTree<T>::searchContact(string cFullName,T& x){
    bool found = false;
    if(isEmpty())
    {
        cout<<"";
    }
    AVLNode<T>* curr;
    AVLNode<T>* parent;
    curr = root;
    parent = (AVLNode<T>*)NULL;
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
                // added this else condition to update the current node when a match is found with a partial string
                else {
                    found = true;
                    break;
                }
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
void AVLTree<T>::makeEmpty(AVLNode<T>* &ptr)
{
    if( ptr != NULL )
    {
        makeEmpty( ptr->left );
        makeEmpty( ptr->right );
        delete ptr;
    }
    ptr = NULL;
}

template <class T>
void AVLTree<T>::makeEmpty()
{
    makeEmpty(root);
}

static const int ALLOWED_IMBALANCE = 1;

template<class T>
void AVLTree<T>::getBalanced(AVLNode<T>* &t)
{
     if( t == nullptr ){
         return;
     }
     
     if( getHeight( t->left ) - getHeight( t->right ) > ALLOWED_IMBALANCE ) {
         if( getHeight( t->left->left ) >= getHeight( t->left->right ) ) {
             rotateWithLeftChild( t );
         }
         else {
             doubleWithLeftChild( t );
         }
     }
     else {
         if((getHeight(t->right) - getHeight(t->left))> ALLOWED_IMBALANCE) {
             if(getHeight(t->right->right) >= getHeight(t->right->left)){
                 rotateWithRightChild( t );
             }
             else{
                 doubleWithRightChild( t );
             }
             
             t->height = findMax( getHeight( t->left ), getHeight( t->right ) ) + 1;
         }
     }
 }

template <class T>
void AVLTree<T>::removeContact(const T& dContact)
{
    removeContact(dContact, root);
}

template <class T>
const T & AVLTree<T>::findMin() const
{
    return contactAt(findMin(root));
}

template <class T>
AVLNode<T>*
AVLTree<T>::findMin( AVLNode<T> *t) const
{
    if(t == NULL)
        return t;

    while( t->left != NULL )
        t = t->left;
    return t;
}

template<class T>
void AVLTree<T>::removeContact(const T& iContact, AVLNode<T>* &dNode)
{
    if( dNode == nullptr ) {
        return;   // Item not found; do nothing
    }
    
    if( iContact.fullname < dNode->contact.fullname ) {
        removeContact(iContact, dNode->left );
    }
    
    else if(dNode->contact.fullname < iContact.fullname ){
        removeContact(iContact, dNode->right );
    }
    
    else if(dNode->left != nullptr && dNode->right != nullptr) // Two children
    {
        dNode->contact = findMin( dNode->right )->contact;
        removeContact( dNode->contact, dNode->right );
    }
    else
    {
        AVLNode<T> *oldNode = dNode;
        dNode = ( dNode->left != nullptr ) ? dNode->left : dNode->right;
        delete oldNode;
    }
    
    getBalanced(dNode); // Balance the AVL tree after deletion
}

template<class T>
void AVLTree<T>::drawTreeHelper(AVLNode<T>* node,string indent, bool last) const {
    cout << indent;
    if (last) {
        cout << "|__ ";
        indent += "   ";
    }
    else {
        cout << "|__ ";
        indent += "|  ";
    }
    cout << node->contact.fullname << endl;

    if (node->left && node->left != nullptr) {
        drawTreeHelper(node->left, indent, node->right == NULL);
    }

    if (node->right && node->right != nullptr) {
        drawTreeHelper(node->right, indent, true);
    }
}

template<class T>
void AVLTree<T>::drawTree() const{
    drawTreeHelper(root, "", true);
}

template<class T>
bool AVLTree<T>::isBalanced() {
    return isBalanced(root);
}

template<class T>
bool AVLTree<T>::isBalanced(AVLNode<T>* node) {
    if (node == nullptr) {
        return true;
    }
    int balanceFactor = getHeight(node->left) - getHeight(node->right);
    if (abs(balanceFactor) > 1) {
        return false;
    }
    return isBalanced(node->left) && isBalanced(node->right);
}

template<class T>
void AVLTree<T>::printTreeInOrderToFile(ofstream& outFile) const {
    if (root != NULL) {
        printTreeInOrderToFile(root, outFile);
    }
}

template<class T>
void AVLTree<T>::printTreeInOrderToFile(AVLNode<T>* t, ofstream& outFile) const {
    if (t != NULL) {
        printTreeInOrderToFile(t->left, outFile);
        outFile << t->contact.fullname << " " << t->contact.phone << " " << t->contact.city << endl;
        printTreeInOrderToFile(t->right, outFile);
    }
}


template<class T>
void AVLTree<T>::printTreePreOrderToFile(AVLNode<T>* t, ofstream& outFile) const {
    if (t != NULL) {
        
        outFile << t->contact.fullname << " " << t->contact.phone << " " << t->contact.city << endl;
        printTreePreOrderToFile(t->left, outFile);
        printTreePreOrderToFile(t->right, outFile);
    }
}
    
template<class T>
void AVLTree<T>::printTreePreOrderToFile(ofstream& outFile) const {
    if (root != NULL) {
        printTreePreOrderToFile(root, outFile);
    }
}

template<class T>
void AVLTree<T>::drawTreeToFileHelper(ofstream& file, AVLNode<T>* node, string indent, bool last) {
    file << indent;
    if (last) {
        file << "|__ ";
        indent += "   ";
    }
    else {
        file << "|-- ";
        indent += "|  ";
    }
    file << node->contact.fullname << endl;

    if (node->left) {
        drawTreeToFileHelper(file, node->left, indent, node->right == NULL);
    }

    if (node->right) {
        drawTreeToFileHelper(file, node->right, indent, true);
    }
}




#endif /* AVLHeader_h */
