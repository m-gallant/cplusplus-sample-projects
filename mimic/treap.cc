#include "treap.h"

// return value for given key if found in treap
// if key is not found return -1
int Treap::find(const std::string& key){
  //check if the root exists. if it does, recurse on the treap
  if (root != NULL) {
  	return findNode(root, key);
  }
  //if the root is null, return -1
  return -1;
}

//traverse through the treap looking for the key. if you find the key, return the value
//if you don't find the key, check to see if there are children nodes you can recurse on
//and go in the appropriate direction. if there are no children, return -1
int Treap::findNode(TreapNode* node, const std::string& key){
    //check the key of the node you are at
    if (key == node->key) return node->value;
    //if the key is smaller than the key of the node you're at and the left child exists
    //recurse left looking for the key
    if ((key < node->key) && (node->left != NULL)) {
      return findNode(node->left, key);
    //otherwise, if the right child exists, recurse right looking for the key
  } else if (node->right != NULL){
      return findNode(node->right, key);
  }
    //if there are no children, return -1
    else return -1;
}

//creates a node and passes it to insertRecursively along with the root to insert into treap
//assumes the user has called find (as done in main) to ensure no duplicates are added
void Treap::insert(const std::string& key, int value){
    //make a new node with given key and value
    TreapNode* nodeToInsert = new TreapNode(key, value);
    //the root will now equal the new root of the treap, once the new node is inserted
    root = insertRecursively(root, nodeToInsert);
}

//recurses through the tree, looking for the correct spot to insert the node
//follows BST structure for insertion and rotates at each level to follow heap property
TreapNode* Treap::insertRecursively(TreapNode* node, TreapNode* nodeToInsert) {
  //if the node you are given is null, this is where the new node belongs
  if (node == NULL ) { return node = nodeToInsert;}
  //otherwise, check to see which branch to recurse down.
  //after recursive call returns, check priority, rotate if necessary
  else {
    if (node->key < nodeToInsert->key){
        node->right = insertRecursively(node->right, nodeToInsert);
        if(node->right->priority < node->priority){
          node = rotateLeft(node);
        }
    } else {
        node->left = insertRecursively(node->left, nodeToInsert);
        if(node->left->priority < node->priority){
          node = rotateRight(node);
        }
      }
    }
  return node;
}

//takes a node and rotates it right within the Treap
//adapted from course textbook Koffman pg.627
TreapNode* Treap::rotateRight(TreapNode*& node) {
  TreapNode* temp = node->left;
  node->left = temp->right;
  temp->right = node;
  node = temp;
  return node;
}

//takes a node and rotates it left within the Treap
//adapted from rotateRight
TreapNode* Treap::rotateLeft(TreapNode*& node) {
  TreapNode* temp = node->right;
  node->right = temp->left;
  temp->left = node;
  node = temp;
  return node;
}
