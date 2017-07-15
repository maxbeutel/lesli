#include "minunit.h"

#include <lesli/trie.hpp>

MU_TEST(test_prefixes) {
  struct TrieNode *root = newNode();

  insert(root, "singapore");
  insert(root, "sincity");
  insert(root, "sinister");

  completion(root, "sin");

  //assert(1 == 2);
}

int main(int, char **) {
  MU_RUN_TEST(test_prefixes);
  MU_REPORT();
  return 0;
}
