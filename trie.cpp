#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class Node {
public:
    char character;
    std::unordered_map<char, Node> children;
    bool isTerminal;

    Node(char character = 0, bool isTerminal = false) : character(character), isTerminal(isTerminal) {}
};

class Trie {
public:
    Node root;

    Trie() : root(0, false) {}

    void insert(const std::string& word) {
        Node* curr = &root;
        for (char c : word) {
            if (curr->children.find(c) == curr->children.end()) {
                curr->children[c] = Node(c);
            }
            curr = &curr->children[c];
        }
        curr->isTerminal = true;
    }

    bool contains(const std::string& word) {
        const Node* curr = &root;
        for (char c : word) {
            if (curr->children.find(c) == curr->children.end()) {
                return false;
            }
            curr = &curr->children[c];
        }
        return curr->isTerminal;
    }

    std::vector<std::string> getPrefixes(const std::string& word) {
        std::string prefix = "";
        std::vector<std::string> prefixes;
        const Node* curr = &root;

        for (char c : word) {
            if (curr->children.find(c) == curr->children.end()) {
                return prefixes;
            }
            curr = &curr->children[c];
            prefix += c;
            if (curr->isTerminal) {
                prefixes.push_back(prefix);
            }
        }

        return prefixes;
    }
};

int main() {
    Trie trie;
    trie.insert("apple");
    trie.insert("app");
    trie.insert("banana");
    
    std::cout << "Contains 'apple': " << (trie.contains("apple") ? "true" : "false") << std::endl;
    std::cout << "Contains 'app': " << (trie.contains("app") ? "true" : "false") << std::endl;
    std::cout << "Contains 'apples': " << (trie.contains("apples") ? "true" : "false") << std::endl;

    std::cout << "Prefixes of 'appetite':" << std::endl;
    std::vector<std::string> prefixes = trie.getPrefixes("appetite");
    for (const std::string& prefix : prefixes) {
        std::cout << prefix << std::endl;
    }

    return 0;
}
