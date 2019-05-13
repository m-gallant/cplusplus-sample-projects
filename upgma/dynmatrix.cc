#include "dynmatrix.h"
#include <iomanip>
#include <iostream>

void printRowByRow(ClusterNode *head) {
  while (head) {
    std::cout <<std::setw(10)<<head->name<<":\t";
    DistanceNode *curD = head->row;
    while (curD) {
      std::cout <<curD->distance<<"\t";
      curD = curD->nextInRow;
    }
    std::cout <<std::endl;
    head = head->next;
  }
}

void printColumnByColumn(ClusterNode *head) {
  while (head) {
    std::cout <<std::setw(10)<<head->name<<":\t";
    DistanceNode *curD = head->column;
    while (curD) {
      std::cout <<curD->distance<<"\t";
      curD = curD->nextInColumn;
    }
    std::cout <<std::endl;
    head = head->next;
  }
}


void addCluster(ClusterNode *&head,ClusterNode *&tail,const std::string& name)
// adds a cluster (at the tail) and the corresponding row and column to data structure
// distance of all added DistanceNodes should be initialized to 0.0
// at the end, tail should point to the newly added ClusterNode
{
	//make and add the ClusterNode
	ClusterNode* newNode = new ClusterNode(name);

	if ((head == NULL) && (tail == NULL))
	{
		head = newNode;
		tail = newNode;
		DistanceNode* firstDN = new DistanceNode();
		newNode->row = firstDN;
		newNode->column = firstDN;
		return;
	}

	tail->next = newNode;
	newNode->prev = tail;
	tail = newNode;

	//fill out the matrix
	newNode->row = new DistanceNode();
	newNode->column = new DistanceNode();
	DistanceNode* newRow = newNode->row;
	DistanceNode* newColumn = newNode->column;
	ClusterNode* current = head;
	DistanceNode* dCurrent;

	while (current->next != tail) 
	{
		dCurrent = current->column;
		while (dCurrent->nextInColumn != NULL) 
		{				
			dCurrent = dCurrent->nextInColumn;
		}
		dCurrent->nextInColumn = newRow;			
		newRow->nextInRow = new DistanceNode();
		newRow = newRow->nextInRow;
		current = current->next;
	}

	// the next ClusterNode is the tail
	dCurrent = current->column;
	while (dCurrent->nextInColumn != NULL) 
	{
		dCurrent->nextInRow = newColumn;
		newColumn->nextInColumn = new DistanceNode();
		newColumn = newColumn->nextInColumn;
		dCurrent = dCurrent->nextInColumn;	
	}
	dCurrent->nextInColumn = newRow;
	newRow->nextInRow = new DistanceNode(); 
	dCurrent->nextInRow = newColumn;
	newColumn->nextInColumn = newRow->nextInRow; 	
	return;
}

void removeHead(ClusterNode *&head,ClusterNode *&tail,ClusterNode *toBeRemoved)
// removes a cluster pointed to by toBeRemoved and the corresponding row and column 
// in the situation where toBeRemoved is also the head
{
	if (head == tail)
	{
		delete head->row;
		delete head;
		head = tail = NULL;
		return;
	}

	ClusterNode* current = toBeRemoved->next;
	
	do
	{
		current->row = current->row->nextInRow;
		current->column = current->column->nextInColumn;
		current = current->next;
	} while (current != NULL);

	DistanceNode* dCurrent = toBeRemoved->row->nextInColumn;
	do 
	{
		DistanceNode* temp = dCurrent;
		dCurrent = dCurrent->nextInColumn;
		delete temp;
	} while (dCurrent != NULL);
	
	dCurrent = toBeRemoved->row;
	do
	{
		DistanceNode* temp = dCurrent;
		dCurrent = dCurrent->nextInRow;
		delete temp;
	} while (dCurrent != NULL);

	if (head == tail) 
	{
		head = NULL;
		tail = NULL;
	}
	else 
	{
	head = head->next;
	head->prev = NULL;
	}
	
	delete toBeRemoved;
	return;

}

void removeCluster(ClusterNode *&head,ClusterNode *&tail,ClusterNode *toBeRemoved)
// removes a cluster pointed to by toBeRemoved and the corresponding row and column
// if toBeRemoved is the first or last cluster then head or tail needs to be updated
{
		if (toBeRemoved == head) 
		{
			removeHead(head, tail, toBeRemoved);
			return;
		}
		
		ClusterNode* current = toBeRemoved->prev;
		DistanceNode* dCurrent = current->column;
		do
		{
			DistanceNode* temp = dCurrent->nextInRow;
			dCurrent->nextInRow = dCurrent->nextInRow->nextInRow;
			delete temp;
			dCurrent = dCurrent->nextInColumn;
		} while (dCurrent != NULL);

		dCurrent = current->row;
		
		do
		{
			DistanceNode* temp = dCurrent->nextInColumn;
			dCurrent->nextInColumn = dCurrent->nextInColumn->nextInColumn;
			delete temp;
			dCurrent = dCurrent->nextInRow;
		} while (dCurrent != NULL);

		if (toBeRemoved == tail)
		{
			tail = tail->prev;
			tail->next = NULL;
		}
		else
		{
		toBeRemoved->prev->next = toBeRemoved->next;
		toBeRemoved->next->prev = toBeRemoved->prev;
		}
		
		delete toBeRemoved;
		return;
}


void findMinimum(ClusterNode *head,ClusterNode *&C,ClusterNode *&D)
// finds the minimum distance (between two different clusters) in the data structure 
// and returns the two clusters via C and D. if there is a tie, return the first one you find.
{
	DistanceNode* currentColumn = head->column; //JUL - changed
	DistanceNode* currentRow;
	int currentX = 0;
	int currentY = 0;
	double smallestDistance = currentColumn->nextInColumn->distance; //JUL - changed
	int smallestX = 0;
	int smallestY = 1;

	//go through each distancenode in the dynmatrix until you get to 0, then move down a row
	do
	{
		currentColumn = currentColumn->nextInColumn;
		currentX = 0;
		currentY = currentY + 1;
		currentRow = currentColumn;
		while ((currentRow->distance != 0.0) && (currentRow->nextInRow != NULL))
		{
			if (currentRow->distance < smallestDistance)
			{
				smallestDistance = currentRow->distance;
				smallestX = currentX;
				smallestY = currentY;
			}
			currentX = currentX + 1;
			currentRow = currentRow->nextInRow;
		}
		
	} while (currentColumn->nextInColumn != NULL);

	//use smallestX and smallestY to find the appropriate clusters to return
	ClusterNode* current = head;
	for (int i=0; i <= std::max(smallestX, smallestY); i++) 
	{
		if (i == smallestX) 
		{
			C = current;
		}
		if (i == smallestY)
		{
			D = current;
		}
		current = current->next;
	}
}

