#include <iostream>
#include <unordered_map>
#include <vector>

/**
 * Nodes of the Trie
 */
class TrieNode {
public:
    char key;
    TrieNode* parent;
    std::unordered_map<char, TrieNode*> children;
    bool end;

    TrieNode(char key) : key(key), parent(nullptr), end(false) {}
};

/**
 * Trie
 */
class Trie {
public:
    Trie() {
        root = new TrieNode('\0');
    }

    void insert(std::string word) {
        TrieNode* node = root;

        for (size_t index = 0; index < word.length(); ++index) {
            char c = word[index];
            if (node->children.find(c) == node->children.end()) {
                node->children[c] = new TrieNode(c);
                node->children[c]->parent = node;
            }
            node = node->children[c];

            if (index == word.length() - 1) {
                node->end = true;
            }
        }
    }

    std::vector<std::string> find(std::string prefix) {
        TrieNode* node = root;
        std::vector<std::string> output;

        for (size_t index = 0; index < prefix.length(); ++index) {
            char c = prefix[index];
            if (node->children.find(c) != node->children.end()) {
                node = node->children[c];
            } else {
                return output;
            }
        }
        findAllWords(node, output);

        return output;
    }

private:
    TrieNode* root;

    void findAllWords(TrieNode* node, std::vector<std::string>& arr) {
        if (node->end) {
            arr.insert(arr.begin(), node->getWord());
        }

        for (const auto& child : node->children) {
            findAllWords(child.second, arr);
        }
    }
};

int main() {
    Trie trie;
    trie.insert("apple");
    trie.insert("app");
    trie.insert("banana");
    trie.insert("bat");

    std::vector<std::string> result = trie.find("app");
    for (const std::string& word : result) {
        std::cout << word << std::endl;
    }

    return 0;
}
