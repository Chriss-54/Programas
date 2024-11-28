// SplayTree.cpp
#include "SplayTree.h"
#include <iostream>

SplayNode::SplayNode(const std::string& eng, const std::string& spa)
    : english(eng), spanish(spa), left(nullptr), right(nullptr) {}

SplayTree::SplayTree() : root(nullptr) {}

SplayTree::~SplayTree() {
    // Implementar destructor para liberar memoria
}

SplayNode* SplayTree::rightRotate(SplayNode* x) {
    SplayNode* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

SplayNode* SplayTree::leftRotate(SplayNode* x) {
    SplayNode* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

SplayNode* SplayTree::splay(SplayNode* root, const std::string& key) {
    if (root == nullptr || root->english == key)
        return root;

    if (key < root->english) {
        if (root->left == nullptr) return root;
        
        if (key < root->left->english) {
            root->left->left = splay(root->left->left, key);
            root = rightRotate(root);
        } else if (key > root->left->english) {
            root->left->right = splay(root->left->right, key);
            if (root->left->right != nullptr)
                root->left = leftRotate(root->left);
        }
        
        return (root->left == nullptr) ? root : rightRotate(root);
    } else {
        if (root->right == nullptr) return root;
        
        if (key > root->right->english) {
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        } else if (key < root->right->english) {
            root->right->left = splay(root->right->left, key);
            if (root->right->left != nullptr)
                root->right = rightRotate(root->right);
        }
        
        return (root->right == nullptr) ? root : leftRotate(root);
    }
}

void SplayTree::insert(const std::string& english, const std::string& spanish) {
    if (root == nullptr) {
        root = new SplayNode(english, spanish);
        return;
    }
    
    root = splay(root, english);
    
    if (root->english == english) {
        root->spanish = spanish;  // Actualizar traducción si la palabra ya existe
        return;
    }
    
    SplayNode* newNode = new SplayNode(english, spanish);
    
    if (english < root->english) {
        newNode->right = root;
        newNode->left = root->left;
        root->left = nullptr;
    } else {
        newNode->left = root;
        newNode->right = root->right;
        root->right = nullptr;
    }
    
    root = newNode;
}

std::string SplayTree::search(const std::string& english) {
    root = splay(root, english);
    
    if (root != nullptr && root->english == english)
        return root->spanish;
    
    return "Not found";
}

void SplayTree::remove(const std::string& english) {
    if (root == nullptr) return;
    
    root = splay(root, english);
    
    if (root->english != english) return;
    
    SplayNode* temp;
    if (root->left == nullptr) {
        temp = root;
        root = root->right;
    } else {
        temp = root;
        root = splay(root->left, english);
        root->right = temp->right;
    }
    
    delete temp;
}

void SplayTree::inorderTraversal(SplayNode* node) {
    if (node != nullptr) {
        inorderTraversal(node->left);
        std::cout << node->english << " : " << node->spanish << std::endl;
        inorderTraversal(node->right);
    }
}

void SplayTree::printDictionary() {
    inorderTraversal(root);
}