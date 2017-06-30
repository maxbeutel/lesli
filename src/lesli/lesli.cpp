#include <string>
#include <sstream>
#include <fstream>

#include <assert.h>

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>


#define ALPHABET_SIZE 26

#define CHAR_TO_INDEX(c) ((int)c - (int)'a')


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

  return (pCrawl != NULL && pCrawl->isLeaf);
}

void lcString(char *str) {
  for (; *str; str++) *str = tolower(*str);
}


int main() {
  std::ifstream infile("/Users/max/Desktop/links.org");

  std::string line;
  std::string prefix("* ");

  struct TrieNode *root = newNode();

  while (std::getline(infile, line)) {
    const char *ptr = strstr(line.c_str(), prefix.c_str());

    if (ptr != NULL) {
      char *headline = strdup(ptr + prefix.length()); // @FIXME free
      lcString(headline); // @FIXME trie structure can only work with lowercase chars

      printf("> detected headline: |%s|\n", headline);

      insert(root, headline);
      assert(search(root, headline) == true && "Failed to find inserted headline in trie");
    }
  }

  return 0;
}

// autocomplete example:
/*
static char** my_completion(const char*, int ,int);
char* my_generator(const char*,int);
char * dupstr (char*);
void *xmalloc (int);

char* cmd [] ={ "hello", "world", "hell" ,"word", "quit", " ", "\r"};

int main()
{
    // http://cc.byexamples.com/2008/06/16/gnu-readline-implement-custom-auto-complete/
    char *buf;

    rl_completion_append_character = '\0';

    while((buf = readline("\n>> "))!=NULL) {
      if (rl_attempted_completion_function) {
        // read category
        printf("cat [%s]\n",buf);

        rl_bind_key('\t', NULL);
        rl_attempted_completion_function = NULL;

      } else {
        // read link
        printf("lnk [%s]\n",buf);

        rl_bind_key('\t',rl_complete);
        rl_attempted_completion_function = my_completion;
      }
    }

    free(buf);

    return 0;
}


static char** my_completion( const char * text , int start,  int end)
{
    char **matches;

    matches = (char **)NULL;

    if (start == 0)
        matches = rl_completion_matches ((char*)text, &my_generator);
    else
      rl_bind_key('\t',rl_insert);

    return (matches);

}

char* my_generator(const char* text, int state)
{
    static int list_index, len;
    char *name;

    if (!state) {
        list_index = 0;
        len = strlen (text);
    }

    //    while (name = cmd[list_index])
    while ((name = cmd[list_index]) && strncmp(cmd[list_index], "\r", 1) != 0)  {
        list_index++;

        if (strncmp (name, text, len) == 0)
            return (dupstr(name));
    }

    // If no names matched, then return NULL.
    return ((char *)NULL);

}

char * dupstr (char* s) {
  char *r;

  r = (char*) xmalloc ((strlen (s) + 1));
  strcpy (r, s);
  return (r);
}

void * xmalloc (int size)
{
    void *buf;

    buf = malloc (size);
    if (!buf) {
        fprintf (stderr, "Error: Out of memory. Exiting.'n");
        exit (1);
    }

    return buf;
}
*/
