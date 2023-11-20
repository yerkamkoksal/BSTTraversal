#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <chrono>
#include "AVLHeader.h"
#include "BSTHeader.h"
using namespace std;

struct Contact {
    string fullname;
    string phone;
    string city;

    
    Contact(string fname, string phoneNum, string cityName)
        :  fullname(fname), phone(phoneNum), city(cityName) {}
    Contact()
    : fullname(""), phone(""), city(""){}
};

string ToUpper(const string& str) {
    string result;
    for (auto c : str) {
        if (c >= 'a' && c <= 'z') {
            c = c - 'a' + 'A';
        }
        result += c;
    }
    return result;
}


void createContactsFromFile(BinarySearchTree<Contact>& bst, AVLTree<Contact>& avl) { // clock problem!!!
    string filename;
    cout<<"Please enter the contact filename: ";
    cin>>filename;
    ifstream inputFile(filename);
    
    // BST LOADING PART
    
    inputFile.open(filename);
    string line;
    
    auto startBST = std::chrono::high_resolution_clock::now();
    while (getline(inputFile, line)) {
        istringstream iss(line);
        string firstName, lastName, phone, city;
        iss >> firstName >> lastName >> phone >> city;
        string fullNameTemp = firstName + " " + lastName;
        
        Contact newContact(ToUpper(fullNameTemp), phone, city);
        bst.insertContact(newContact);
    }
    
    auto endBST = chrono::high_resolution_clock::now();
    auto durationBST = chrono::duration_cast<chrono::milliseconds>(endBST - startBST);
    inputFile.close();
    
    
    // AVL LOADING PART
    inputFile.open(filename);
    
    auto startAVL = std::chrono::high_resolution_clock::now();
    while (getline(inputFile, line)) {

        istringstream iss(line);
        string firstName, lastName, phone, city;
        iss >> firstName >> lastName >> phone >> city;
        string fullNameTemp = firstName + " " + lastName;
        
        Contact newContact(ToUpper(fullNameTemp), phone, city);
        avl.insertContact(newContact);
    }
    auto endAVL = std::chrono::high_resolution_clock::now();
    auto durationAVL = chrono::duration_cast<chrono::milliseconds>(endAVL - startAVL);

    inputFile.close();
    
    cout << "Loading the phonebook into a BST." << endl;
        cout << "Phonebook creation in BST took " << durationBST.count() << " milliseconds. . ." << endl;
        if (bst.isBalanced()) {
            cout << "The tree is balanced" << endl;
            cout << "The heights of BST are for left: " << bst.getHeight(bst.getRoot()) << " and right: " << bst.getHeight(bst.getRoot()) << endl;

        }
        else {
            cout << "The tree is not balanced" << endl;
            cout << "The heights of BST are for left: " << bst.getHeight(bst.getRoot()->left) << " and right: " << bst.getHeight(bst.getRoot()->right) << endl;
        }

        cout << "Loading the phonebook into an AVL." << endl;
        cout << "Phonebook creation in AVL took " << durationAVL.count() << " milliseconds. . ." << endl;
        if (avl.isBalanced()) {
            cout << "The tree is balanced" << endl;
            //cout << "The heights of BST are for left: " << bst.getHeight(bst.getRoot()->left) << " and right: " << bst.getHeight(bst.getRoot()->right) << endl;

        }
        else {
            cout << "The tree is not balanced" << endl;
            //cout << "The heights of BST are for left: " << avl.getHeight(avl.getRoot()) << " and right: " << avl.getHeight(avl.getRoot()) << endl;
        }
}


void selectList(){
    cout<<"Choose which action to perform from 1 to 6:"<<endl;
    cout<<"1 - Search a phonebook contact"<<endl;
    cout<<"2 - Adding a phonebook contact"<<endl;
    cout<<"3 - Deleting a phonebook contact"<<endl;
    cout<<"3 - Deleting a phonebook contact"<<endl;
    cout<<"4 - Print the phonebook to a file(inorder)"<<endl;
    cout<<"    Print the phonebook to a file(preorder)"<<endl;
    cout<<"5 - Draw the phonebook as a Tree to a file"<<endl;
    cout<<"6 - Press 6 to exit"<<endl;
}

void SearchContact(string searchStr, BinarySearchTree<Contact>& bst, AVLTree<Contact>& avl){
    Contact foundContact;
    searchStr = ToUpper(searchStr);
    cout<<"Searching an item in the phonebook (BST) . . ."<<endl;
    cout<<endl;
    cout<<"Phonebook: Searching for: ("<<searchStr<<")"<<endl;
    cout<<"===================================="<<endl;
    auto startSearchBST = std::chrono::high_resolution_clock::now();
    bst.searchContact(searchStr,foundContact);
    auto endSearchBST = std::chrono::high_resolution_clock::now();
    auto durationSearchBST = chrono::duration_cast<chrono::nanoseconds>(endSearchBST - startSearchBST);
    
    cout<<"Searching an item in the phonebook (AVL) . . ."<<endl;
    cout<<endl;
    cout<<"Phonebook: Searching for: ("<<searchStr<<")"<<endl;
    cout<<"===================================="<<endl;
    auto startSearchAVL = std::chrono::high_resolution_clock::now();
    avl.searchContact(searchStr,foundContact);
    auto endSearchAVL = std::chrono::high_resolution_clock::now();
    auto durationSearchAVL = chrono::duration_cast<chrono::nanoseconds>(endSearchAVL - startSearchAVL);
    
    cout<<endl;
    cout<<"The search in BST took " << durationSearchBST.count() <<" nanoseconds. . ."<<endl;
    cout<<"The search in AVL took " << durationSearchAVL.count() <<" nanoseconds. . ."<<endl;
    cout<<endl;
    return;
}

void AddContact(BinarySearchTree<Contact>& bst, AVLTree<Contact>& avl){
    string cName,cTel,cCity;
    cout<<"Enter the information of the contact to be added:"<<endl;
    cout<<"Name: ";
    cin>>cName;
    cout<<endl;
    cout<<"Tel: ";
    cin>>cTel;
    cout<<endl;
    cout<<"City: ";
    cin>>cCity;
    cout<<endl;
    
    cout<<"Adding an item to the phonebook BST . . ."<<endl;
    cout<<"===================================="<<endl;
    auto startAddBST = std::chrono::high_resolution_clock::now();
    Contact newContact(ToUpper(cName),cTel,cCity);
    bst.insertContact(newContact);
    auto endAddBST = std::chrono::high_resolution_clock::now();
    auto durationAddBST = chrono::duration_cast<chrono::nanoseconds>(endAddBST - startAddBST);
    cout<<"Contact has been added successfully to the BST"<<endl;
    cout<<endl;
    
    cout<<"Adding an item to the phonebook AVL . . ."<<endl;
    cout<<"===================================="<<endl;
    auto startAddAVL = std::chrono::high_resolution_clock::now();
    avl.insertContact(newContact);
    auto endAddAVL = std::chrono::high_resolution_clock::now();
    auto durationAddAVL = chrono::duration_cast<chrono::nanoseconds>(endAddAVL - startAddAVL);
    cout<<"Contact has been added successfully to the AVL Tree"<<endl;
    cout<<endl;
    
    cout<<"Adding a contact to the Binary Tree took " << durationAddBST.count() <<" nanoseconds. . ."<<endl;
    cout<<"Adding a contact to the AVL Tree took " << durationAddAVL.count() <<" nanoseconds. . ."<<endl;
    cout<<endl;
    return;
}

template <typename T>
void DeleteContact(BinarySearchTree<T>& bst, AVLTree<T>& avl){
    string dName;
    T foundContact;
    cout<<"Deleting an item from the phonebook . . ."<<endl;
    cout<<"Enter the fullname of the contact to be deleted: ";
    cin>>dName;
    cout<<endl;
    if(avl.searchContact(dName,foundContact) || bst.searchContact(dName,foundContact)){
        auto startDeleteBST = std::chrono::high_resolution_clock::now();
        bst.removeContact(foundContact);
        auto endDeleteBST = std::chrono::high_resolution_clock::now();
        auto durationDeleteBST = chrono::duration_cast<chrono::nanoseconds>(endDeleteBST - startDeleteBST);
        
        auto startDeleteAVL = std::chrono::high_resolution_clock::now();
        avl.removeContact(foundContact);
        auto endDeleteAVL = std::chrono::high_resolution_clock::now();
        auto durationDeleteAVL = chrono::duration_cast<chrono::nanoseconds>(endDeleteAVL - startDeleteAVL);
        
        cout<<"Deleted succcessfully. . ."<<endl;
        cout<<endl;
        
        cout<<"Deletion from the Binary Tree took " << durationDeleteBST.count() <<" nanoseconds. . ."<<endl;
        cout<<"Deletion from AVL Tree took " << durationDeleteAVL.count() <<" nanoseconds. . ."<<endl;
    }
    else{
        cout<<"Not found."<<endl;
    }
    return;
}

template <typename T>
void InOrderPrintToFile(BinarySearchTree<T>& bst, AVLTree<T>& avl) {
    ofstream bstFile("InOrderBST.txt");
    ofstream avlFile("InOrderAVL.txt");

    if (!bstFile.is_open() || !avlFile.is_open()) {
        cout << "Failed to open output files." << endl;
        return;
    }

    // Print BST in order to file
    bst.printTreeInOrderToFile(bstFile);

    // Print AVL in order to file
    avl.printTreeInOrderToFile(avlFile);

    bstFile.close();
    avlFile.close();
}

template <typename T>
void PreOrderPrintToFile(BinarySearchTree<T>& bst, AVLTree<T>& avl){
    ofstream bstFile("PreOrderBST.txt");
    ofstream avlFile("PreOrderAVL.txt");

    if (!bstFile.is_open() || !avlFile.is_open()) {
        cout << "Failed to open output files." << endl;
        return;
    }

    // Print BST in order to file
    bst.printTreePreOrderToFile(bstFile);

    // Print AVL in order to file
    avl.printTreePreOrderToFile(avlFile);

    bstFile.close();
    avlFile.close();
}

template <typename T>
void DrawTreeToFile(BinarySearchTree<T>& bst, AVLTree<T>& avl) {
    ofstream bstFile("phonebookTreeBST.txt");
    if (bstFile.is_open()) {
        bstFile << "Printing out the phonebook  (BST)" <<endl;
        bstFile << "====================================" <<endl;
        bst.printTreeInOrderToFile(bstFile);
        bstFile <<endl << "Tree Structure:" << endl;
        bst.drawTreeToFileHelper(bstFile, bst.getRoot(), "", true);
        bstFile.close();
    }

    ofstream avlFile("phonebookTreeAVL.txt");
    if (avlFile.is_open()) {
        avlFile << "Printing out the phonebook  (AVL)" <<endl;
        avlFile << "====================================" <<endl;
        avl.printTreeInOrderToFile(avlFile);
        avlFile << endl << "Tree Structure:" << endl;
        avl.drawTreeToFileHelper(avlFile, avl.getRoot(), "", true);
        avlFile.close();
    }
}


int main() {
    BinarySearchTree<Contact> bst;
    AVLTree<Contact> avl;
    createContactsFromFile(bst, avl);
    
    int choice;
    selectList();
    cin >> choice;
    cout<<endl;

    while (choice != 0) {

        if (choice == 1) {
            string searchString;
            cout << "Search for a contact: ";
            cin >> searchString;
            cout<<endl;
            SearchContact(searchString, bst, avl);
            continue;
        }
        else if (choice == 2) {
            AddContact(bst, avl);
        }
        else if (choice == 3) {
            DeleteContact(bst, avl);
        }
        else if (choice == 4) {
            InOrderPrintToFile(bst, avl);
            PreOrderPrintToFile(bst, avl);
        }
        else if (choice == 5) {
            DrawTreeToFile(bst, avl);
        }
        else if (choice == 6) {
            break;
        }
        selectList();
        cin.clear();
        cin >> choice;
        cout<<endl;
    }

    
    return 0;
}
