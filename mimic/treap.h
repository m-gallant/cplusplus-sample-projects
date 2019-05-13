#ifndef __TREAP
#define __TREAP
#include <string>
#include <cstdlib>

struct TreapNode {
  std::string key;
  int value;
  int priority;
  TreapNode* left;
  TreapNode* right;
  //constructor
    TreapNode(std::string key, int value):
      key(key),value(value),priority(rand()),left(NULL),right(NULL){}
};

class Treap {
  TreapNode *root;
  //helper functions
  TreapNode* rotateLeft(TreapNode*& parent);
  TreapNode* rotateRight(TreapNode*& parent);
  TreapNode* insertRecursively(TreapNode* root, TreapNode* nodeToInsert);
  int findNode(TreapNode* node, const std::string& key);

 public:
  Treap() { // constructor
    srand(time(0));
    //initialise root
    root = NULL;
  }

  int find(const std::string& key);
  void insert(const std::string& key, int value);
};

#endif
