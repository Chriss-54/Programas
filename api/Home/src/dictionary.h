#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>

class SplayTree;

class Dictionary {
public:
    Dictionary();
    void addWord(const std::string& word, const std::string& translation);
    std::string translate(const std::string& word);
private:
    SplayTree* tree;
};

#endif // DICTIONARY_H
