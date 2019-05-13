Mimic Project

The goal of this assignment was to create a program ‘mimic’ that creates a model of given sample text and then produces random text according to that model. The input to mimic is a non-negative integer n and a text file book containing some sample text. 

When n = 0, the output of mimic is the model : m lines are written to the standard output, where m is the number of different words in book. The rth line of output (for 0 ≤ r ≤ m − 1) is the rth new word in book followed by a list of all the words that immediately follow this word in the text, in the order in which they occur, with duplicates. 

When n > 0, the output of the model is a random book: a sequence of n words is written to standard output, that are generated using the model created from the sample text book. Words are separated by a single space or newline. To generate the sequence, a word from the book is generated at random, where the probability of producing the word w1 equals the number of occurrences of w1 in book divided by the total number of words in book. The next word (wi+1) is generated from the current word (wi) by choosing wi+1 at random from the multi-set of words that immediately follow wi in book. (So, the probability of producing wi+1 equals the number of occurrences of wi wi+1 in book divided by the number of followers (with duplicates) of wi
.) If wi has no followers (and i < n) then wi+1 is generated in the same manner as w1.

To run:
compile the files using the makefile
./mimic n book.txt
where n is >= 0 and book.txt is the name of the text file you wish to model

Acknowledgment of Assistance: 
This project was created and assigned by Jan Manuch at UBC as part of the CPSC 221 curriculum.
Given code was the sample input (book.txt) as well as the headers of functions of the trip ADT  and the definition of Treapnode (treap.h).
It was implemented by Michelle Gallant and Julilla Paul.
Our rotateRight and rotateLeft code is adapted from the Koffman textbook (page 627).

Files Included:
	README.txt (this file)	: details of project
	treap.h			: contains data abstraction for TreapNode and Treap
	treap.cc		: implementation of TreapNode and Treap
	mimic.cc		: implementation of model
	Makefile		: for compilation
	book.txt		: source file of data for model
