#include <string>
#include <vector>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define ALPHABET_SIZE 26

#define CHAR_TO_INDEX(c) ((int)c - (int)'a')
#define INDEX_TO_CHAR(c) ((int)'a' + (int)c)

size_t MAX_KEY_LEN = 0;

struct TrieNode {
  struct TrieNode *children[ALPHABET_SIZE];
  bool isLeaf;
};

struct TrieNode *newNode() {
  struct TrieNode *pNode = NULL;
  pNode = (struct TrieNode *) malloc(sizeof(struct TrieNode));

  if (pNode) {
    pNode->isLeaf = false;

    for (int i = 0; i < ALPHABET_SIZE; i++) {
      pNode->children[i] = NULL;
    }
  }

  return pNode;
}

void insert(struct TrieNode *root, const char *key) {
  int level;
  int length = strlen(key);
  int index;

  if ((size_t) length > MAX_KEY_LEN) { // @FIXME so bad cast
    MAX_KEY_LEN = length;
  }

  struct TrieNode *pCrawl = root;

  for (level = 0; level < length; level++) {
    index = CHAR_TO_INDEX(key[level]);

    if (!pCrawl->children[index]) {
      pCrawl->children[index] = newNode();
    }

    pCrawl = pCrawl->children[index];
  }

  pCrawl->isLeaf = true;
}

// @TODO how to autocomplete when the user entered for example the first 2 characters?
//       add tests (maybe minunit)

bool search(struct TrieNode *root, const char *key) {
  int level;
  int length = strlen(key);
  int index;

  struct TrieNode *pCrawl = root;

  for (level = 0; level < length; level++) {
    index = CHAR_TO_INDEX(key[level]);

    if (!pCrawl->children[index]) {
      return false;
    }

    pCrawl = pCrawl->children[index];
  }

  return (pCrawl != NULL); // add  && pCrawl->isLeaf to only get full matches, not only prefixes
}

void walk(struct TrieNode *root, std::vector<char>& a, std::vector<std::string>& b);

std::vector<std::string> completion(struct TrieNode *root, const char *key) {
  int level;
  int length = strlen(key);
  int index;

  struct TrieNode *pCrawl = root;

  //  std::vector<char> tmp;
  std::vector<char> a(key, key + length); // use this as prefix
  std::vector<std::string> b;

  for (level = 0; level < length; level++) {
    index = CHAR_TO_INDEX(key[level]);

    if (!pCrawl->children[index]) {
      break;
    }

    if (level == length - 1) {
      for (int j = 0; j < ALPHABET_SIZE; j++) {
        if (pCrawl->children[j] != NULL) {
          //printf(">> Possible completions for %s\n", key);

          walk(pCrawl->children[j], a, b); // b contains now all words (@FIXME whitespaces are replaced with t though)
        }
      }
    }

    pCrawl = pCrawl->children[index];
  }

  return b;
}

void walk(struct TrieNode *root, std::vector<char>& a, std::vector<std::string>& b) {
  // sigh, really need a iterable container here
  for (int i = 0; i < ALPHABET_SIZE; i++) {
    struct TrieNode *tmp = root->children[i];

    if (tmp == NULL) {
      continue;
    }

    //printf("%c", INDEX_TO_CHAR(i));
    a.push_back(INDEX_TO_CHAR(i));
    walk(tmp, a, b);
    a.pop_back();
  }

  if (root->isLeaf) {
    std::string curKey(a.begin(), a.end());

    //printf(">> %s\n", curKey.c_str());
    b.push_back(curKey);
  }
}

void lcString(char *str) {
  for (; *str; str++) *str = tolower(*str);
}
