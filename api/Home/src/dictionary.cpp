#include "dictionary.h"
#include "splay_tree.h"

Dictionary::Dictionary() {
    tree = new SplayTree();
}

void Dictionary::addWord(const std::string& word, const std::string& translation) {
    tree->insert(word, translation);
}

std::string Dictionary::translate(const std::string& word) {
    return tree->search(word);
}
