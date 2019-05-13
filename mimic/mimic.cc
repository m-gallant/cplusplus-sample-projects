#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "treap.h"
#include <vector>

using namespace std;

// Replace all characters except letters (A-Z,a-z) in line with ' ',
// except keep '-' or '\'' if they are between letters.
void lowercaseWords(string & line) {
  for( string::iterator it = line.begin(); it != line.end(); ++it ) {
    if( !isalpha(*it) ) {
      if( (*it != '-' && *it != '\'') ||
	  it == line.begin() || it+1 == line.end() ||
	  !isalpha(*(it-1)) || !isalpha(*(it+1)) ) {
	*it = ' ';
      }
    } else {
      *it = tolower(*it);
    }
  }
}

int main(int argc, char *argv[]) {
  if( argc < 2 || argc > 3 ) {
    cerr << "Usage: " << argv[0] << " n book.txt" << endl;
    exit(1);
  }

  int n = atoi(argv[1]);

  ifstream fin;
  fin.open(argv[2]);
  if( !fin.is_open() ) {
    cerr << "Unable to open " << argv[1] << endl;
    exit(2);
  }

  //initializing rank, Treap, vectors to hold the words and follower_ranks, and previousWordRank
  int rank = 0;
  Treap T = Treap();
  // words[r] is the r-th word
  vector<string> words;
  // ranks of all words in the text
  vector<int> all_word_ranks;
  // follower_ranks[r] is a vector of ranks of followers of words[r]
  vector<vector<int> > follower_ranks;
  // the rank of the previous word
  int previousWordRank = -1;

  string line;
  string word;
  while( !fin.eof() ) {
    getline(fin,line);
    lowercaseWords(line);
    istringstream iss(line, istringstream::in);

    while( iss >> word ) {
      //check if the word is in the Treap
      int wordRank = T.find(word);
      //if the word is not already in the Treap, insert it
      if (wordRank == -1){
        T.insert(word, rank);
	//add word to words vector
        words.push_back(word);
	//initialize follower_ranks vector for word
        follower_ranks.push_back(vector<int>());
	//update wordRank to rank of current word
        wordRank = rank;
	//update rank
        rank++;
      }

      //add wordRank to the previous word's follower_ranks
      if (previousWordRank != -1) {
          follower_ranks[previousWordRank].push_back(wordRank);
      }

      //add wordRank to the vector of all word ranks
      all_word_ranks.push_back(wordRank);
      //update previousWordRank
      previousWordRank = wordRank;
    }
  }
  fin.close();

  if (n == 0) {
    //output the model
    for (unsigned int i = 0; i<words.size(); i++){
      //print each word
      cout<<words[i]<<" : ";
      for(unsigned int j = 0; j<follower_ranks[i].size(); j++){
        //print each of the word's followers
        cout<<words[follower_ranks[i][j]]<<" ";
      }
      cout<<endl;
    }
  }

  if (n > 0){
    //output a random book
    vector<int> A = all_word_ranks;
    //for formatting, seperates text into 5 words per line
    int wordCounter = 0;
    for (int j = 0; j<n; j++){
      int i = rand() % A.size();
      cout<<words[A[i]]<<" ";
      if (!follower_ranks[A[i]].empty()){
        A = follower_ranks[A[i]];
      }
      wordCounter++;
      //if there are 5 words, end line and reset counter to zero
      if (wordCounter == 5){
        cout<<endl;
        wordCounter = 0;
      }
    }
    if (wordCounter != 0) {
      cout<<endl;
  }
  return 0;
  }
}
