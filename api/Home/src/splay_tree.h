#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#include <string>

struct Node {
    std::string key;
    std::string value;
    Node* left;
    Node* right;

    Node(const std::string& key, const std::string& value) 
        : key(key), value(value), left(nullptr), right(nullptr) {}
};

class SplayTree {
public:
    SplayTree();
    void insert(const std::string& key, const std::string& value);
    std::string search(const std::string& key);

private:
    Node* root;
    Node* rotateRight(Node* x);  // Declaración añadida
    Node* rotateLeft(Node* x);   // Declaración añadida
    Node* splay(Node* root, const std::string& key);
};

#endif

