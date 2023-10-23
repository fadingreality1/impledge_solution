#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>

class TrieNode {
public:
    char key;
    TrieNode* parent;
    std::unordered_map<char, TrieNode*> children;
    bool end;

    TrieNode(char key) : key(key), parent(nullptr), end(false) {}
};

class Trie {
public:
    Trie() {
        root = new TrieNode('\0');
    }

    void insert(const std::string& word) {
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

    std::vector<std::string> find(const std::string& prefix) {
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

std::string LongestString(const std::vector<std::string>& arr) {
    return *std::max_element(arr.begin(), arr.end(),
        [](const std::string& x, const std::string& y) {
            return x.length() < y.length();
        });
}

bool wordChecker(const std::string& word, Trie& trie) {
    for (size_t index = 1; index <= word.length(); ++index) {
        const std::string subWord = word.substr(0, index);
        const std::vector<std::string> foundWords = trie.find(subWord);
        const size_t length = foundWords.size();

        if (length <= 1 && index == 1) {
            return false;
        } else if (length <= 1) {
            return wordChecker(word.substr(index - 1), trie);
        }
    }

    return true;
}

std::vector<std::string> searchConcatWords(const std::string& file, int noOfResults) {
    Trie trie;
    std::vector<std::string> result;

    std::ifstream inputFile(file);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open file " << file << std::endl;
        return result;
    }

    std::vector<std::string> text;
    std::string line;
    while (std::getline(inputFile, line)) {
        text.push_back(line);
        trie.insert(line);
    }

    inputFile.close();

    while (noOfResults > 0) {
        const std::string longestString = LongestString(text);
        text.erase(std::remove(text.begin(), text.end(), longestString), text.end());

        if (wordChecker(longestString, trie)) {
            result.push_back(longestString);
            noOfResults--;
        }
    }

    return result;
}

int main() {
    std::vector<std::string> result1 = searchConcatWords("./Input_01.txt", 2);
    if (result1.size() >= 2) {
        std::cout << result1[0] << ' ' << result1[1] << ' ' << "ms" << std::endl;
    }

    std::vector<std::string> result2 = searchConcatWords("./Input_02.txt", 2);
    if (result2.size() >= 2) {
        std::cout << result2[0] << ' ' << result2[1] << ' ' << "ms" << std::endl;
    }

    return 0;
}
