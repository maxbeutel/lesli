#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>

#include <lesli/trie.hpp>

char **character_name_completion(const char *, int, int);
char *character_name_generator(const char *, int);

struct TrieNode *root = newNode();

int main(void) {
  // prepare trie lookup
  insert(root, "singapore");
  insert(root, "sincity");
  insert(root, "sinister");
  insert(root, "somethingelse");

  // @FIXME free :-)

  // setup autocomplete
  char *buf = NULL;
  rl_attempted_completion_function = character_name_completion;

  while ((buf = readline("\n> ")) != NULL) {
    rl_bind_key('\t', rl_complete);
    printf("\ngot cmd [%s]\n", buf);
  }

  free(buf);

  return 0;
}

char ** character_name_completion(const char *text, int, int) { // start, end
  rl_attempted_completion_over = 1;
  return rl_completion_matches(text, character_name_generator);
}

char *character_name_generator(const char *text, int state) {
  static int list_index = 0, len = 0; // @FIXME should be size_t?

  // @ FIXME not so nice to load all completions for every generator call
  // should be only on state=0, but also needs to be truncated again
  auto completions = completion(root, text); // use reference here?

  if (!state) {
    list_index = 0;
    len = strlen(text);

    //printf("### got %lu completions\n", completions.size());
  }

  while (list_index < completions.size()) {
    auto name = completions[list_index];
    list_index++;

    if (strncmp(name.c_str(), text, len) == 0) {
      return strdup(name.c_str());
    }
  }

  return NULL;
}
