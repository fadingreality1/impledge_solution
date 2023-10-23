# Word Composition Problem

To find words constructed by concatenating shorter words also found in the file.

## Input (files)

- Input_01.txt
- Input_02.txt

## Output

```
ratcatdogcat catsdogcats

ethylenediaminetetraacetates ethylenediaminetetraacetate
```

## Approach

Used Trie data structure its a special tree that stores strings. Maximum number of children of a node is equal to size of alphabet. Trie supports search, insert and delete operations in O(k) time where k is length of key/word. This is obviously faster than BST and Hashing. and we can efficiently do Prefix search.

First `searchConcatWords` function read the file text and constructed Trie from the text/words using insert method present inside `trie.cpp` then used `LongestString` function inside a loop to find the longest strings. Then `wordChecker` function checks the string whether it was constructed using small words found in the Trie or not by checking the length of the result using find method present inside `trie.cpp` if greater than 1 increment the index and after loop ends return `true` If not there are two cases: (1) If the index is equal to 1 that means concat word is not found in the Trie and return `false` (2) Else it cuts the previous part and recursively call `wordChecker` function again.