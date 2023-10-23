#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <unordered_map>
#include <vector>
#include <ctime>

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

class Solution {
public:
    Trie trie;
    std::deque<std::pair<std::string, std::string>> queue;

    void buildTrie(const std::string& filePath = "") {
        try {
            std::ifstream file(filePath);
            if (file.is_open()) {
                std::string line;
                while (std::getline(file, line)) {
                    std::string word = line;
                    std::vector<std::string> prefixes = trie.getPrefixes(word);
                    for (const std::string& prefix : prefixes) {
                        queue.push_back(std::make_pair(word, word.substr(prefix.length())));
                    }
                    trie.insert(word);
                }
                file.close();
            } else {
                std::cout << "There was some error with the file!" << std::endl;
                exit(0);
            }
        } catch (...) {
            std::cout << "There was some error with the file!" << std::endl;
            exit(0);
        }
    }

    std::pair<std::string, std::string> findLongestCompoundWords() {
        std::string longest_word = "";
        int longest_length = 0;
        std::string second_longest = "";

        while (!queue.empty()) {
            std::pair<std::string, std::string> word_suffix = queue.front();
            queue.pop_front();
            std::string word = word_suffix.first;
            std::string suffix = word_suffix.second;

            if (trie.contains(suffix) && word.length() > longest_length) {
                second_longest = longest_word;
                longest_word = word;
                longest_length = word.length();
            } else {
                std::vector<std::string> prefixes = trie.getPrefixes(suffix);
                for (const std::string& prefix : prefixes) {
                    queue.push_back(std::make_pair(word, suffix.substr(prefix.length())));
                }
            }
        }

        return std::make_pair(longest_word, second_longest);
    }
};

int main() {
    Solution sol;
    clock_t start = clock();
    sol.buildTrie("Input_02.txt");
    std::pair<std::string, std::string> result = sol.findLongestCompoundWords();
    clock_t end = clock();
    double elapsed_time = double(end - start) / CLOCKS_PER_SEC;

    std::cout << "Longest Compound Word: " << result.first << std::endl;
    std::cout << "Second Longest Compound Word: " << result.second << std::endl;
    std::cout << "Time taken: " << elapsed_time << " seconds" << std::endl;

    return 0;
}
