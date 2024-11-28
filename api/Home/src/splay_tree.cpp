#include "splay_tree.h"

SplayTree::SplayTree() {
    root = nullptr;
}

Node* SplayTree::rotateRight(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

Node* SplayTree::rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

Node* SplayTree::splay(Node* root, const std::string& key) {
    if (root == nullptr || root->key == key)
        return root;

    if (root->key > key) {
        if (root->left == nullptr) return root;

        if (root->left->key > key) {
            root->left->left = splay(root->left->left, key);
            root = rotateRight(root);
        }
        else if (root->left->key < key) {
            root->left->right = splay(root->left->right, key);
            if (root->left->right != nullptr)
                root->left = rotateLeft(root->left);
        }
        return (root->left == nullptr) ? root : rotateRight(root);
    }
    else {
        if (root->right == nullptr) return root;

        if (root->right->key > key) {
            root->right->left = splay(root->right->left, key);
            if (root->right->left != nullptr)
                root->right = rotateRight(root->right);
        }
        else if (root->right->key < key) {
            root->right->right = splay(root->right->right, key);
            root = rotateLeft(root);
        }
        return (root->right == nullptr) ? root : rotateLeft(root);
    }
}

void SplayTree::insert(const std::string& key, const std::string& value) {
    if (root == nullptr) {
        root = new Node(key, value);
        return;
    }

    root = splay(root, key);

    if (root->key == key) return;

    Node* newNode = new Node(key, value);

    if (root->key > key) {
        newNode->right = root;
        newNode->left = root->left;
        root->left = nullptr;
    }
    else {
        newNode->left = root;
        newNode->right = root->right;
        root->right = nullptr;
    }

    root = newNode;
}

std::string SplayTree::search(const std::string& key) {
    root = splay(root, key);
    if (root && root->key == key) {
        return root->value;
    }
    return "";
}
