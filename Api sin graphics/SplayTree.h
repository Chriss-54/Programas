// SplayTree.h
#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include <string>

class SplayNode {
public:
    std::string english;
    std::string spanish;
    SplayNode* left;
    SplayNode* right;
    
    SplayNode(const std::string& eng, const std::string& spa);
};

class SplayTree {
private:
    SplayNode* root;
    
    SplayNode* splay(SplayNode* root, const std::string& key);
    SplayNode* rightRotate(SplayNode* x);
    SplayNode* leftRotate(SplayNode* x);
    void inorderTraversal(SplayNode* node);

public:
    SplayTree();
    ~SplayTree();
    
    void insert(const std::string& english, const std::string& spanish);
    std::string search(const std::string& english);
    void remove(const std::string& english);
    void printDictionary();
};

#endif // SPLAYTREE_H