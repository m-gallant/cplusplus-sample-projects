#include <iostream>
#include <fstream>
#include <algorithm>
#include "dynmatrix.h"
#include <iomanip>

using namespace std;

void usage() {
  cerr << "Usage: upgma species.txt" << endl;
}

// print function for the bonus problem
void toPrint(std::string str, int d=0)
{
	int num = str.length();

	//if it's just a string then print it
	if ((str.at(0) != '(') && (str.at(num - 1) != ')'))
	{
		cout << std::string(3*d, ' ') << str << endl;
		return;
	}

	//otherwise, remove the brackets
	std::string newString = str.substr(1, num - 2);

	//split it at the right comma
	unsigned spot = 0;
	int brackets = 0;
	for (unsigned i=0; i<newString.length(); ++i)
	{
		if (newString.at(i) == '('){ brackets = brackets + 1;}
		else if (newString.at(i) == ')') { brackets = brackets - 1;}
		else if ((newString.at(i) == ',') && (brackets == 0)) 
		{	
			spot = i;	
			break;
		}
	}

	std::string str1 = newString.substr(0,spot);
	std::string str2 = newString.substr(spot+1, std::string::npos);
	 
	//recurse left
	toPrint(str2, ++d);
	--d;		

	//print your dot-node and lines
	cout<< std::string(3*d, ' ') << " /" << endl;
	cout<< std::string(3*d, ' ') << "." << endl;
	cout<< std::string(3*d, ' ') << " \\" << endl;

	//recurse right
	toPrint(str1, ++d);
	--d;

}

int main( int argc, char *argv[] ) {
  if( argc != 2 ) {
    usage();
    return 0;
  }

  // let's start with empty DynMatrix:
  ClusterNode* head = NULL; 
  ClusterNode* tail = NULL;

  int n = 0; // number of species
  ifstream fin( argv[1] );

  if( fin.is_open() ) {

    // read species:
    string species;
    while ((fin.peek() != '\n') && (fin >> species)) {
      n++;
      addCluster(head, tail, species);
    }

    // read distances:
    ClusterNode* current = head;
    for (int i=0; i<n && fin; i++) {
      DistanceNode* dCurrent = current->column;
      for (int j=0; j<n && fin; j++) {
				double d;
				fin >> d;
				dCurrent->distance = d;
				if (dCurrent->nextInColumn != NULL) 
				{
					dCurrent = dCurrent->nextInColumn;
				}
			}
			current = current->next;
		}
		
		fin.close();
	}

	// Code to print rows and columns if desired
	//printRowByRow(head);
	//printColumnByColumn(head);

	//the UPGMA method
	while (head->next != NULL) {	
		ClusterNode* C = tail;
		ClusterNode* D = tail->prev;
 		findMinimum(head, C, D);
		std::string newClusterName = "(" + C->name + "," + D->name + ")";
		addCluster(head, tail, newClusterName);
		tail->clusterSize = C->clusterSize + D->clusterSize;

		DistanceNode* newColumn = tail->column;
		DistanceNode* newRow = tail->row;
		DistanceNode* currentC = C->column;
		DistanceNode* currentD = D->column;
		int speciesInC = C->clusterSize;
		int speciesInD = D->clusterSize;

		while (newColumn != newRow)
		{
			double dist = (((speciesInC * currentC->distance) + (speciesInD * currentD->distance))/(speciesInC + speciesInD));
			newColumn->distance = dist;
			newRow->distance = dist;
			newColumn = newColumn->nextInColumn;
			newRow = newRow->nextInRow;
			currentC = currentC->nextInColumn;
			currentD = currentD->nextInColumn;
		}

		removeCluster(head, tail, C);
		removeCluster(head, tail, D);

		// Code to print updated rows and columns if desired
		// printRowByRow(head);
		// printColumnByColumn(head);
	}

  // print the name of the last remaining cluster
  if (head) {
    cout << head->name << endl;
	}

	// BONUS (optional): print the tree in a nice way
	toPrint(head->name);

  //delete the last remaining cluster to prevent memory leak;
	removeCluster(head, tail, head);

  return 0;
}
