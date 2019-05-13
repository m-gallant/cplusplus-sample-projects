Upgma Project

UPGMA (Unweighted Pair Group Method with Arithmetic Mean) is a bottom-up hierarchical clustering method invented by Sokal and Michener, that is used to construct a phylogenetic tree from the pairwise (evolutionary) distances between species. The method works by clustering the species, at each stage joining two clusters together that have the smallest distance.
The input to the algorithm is a sequence of strings with names of the species and distances between the species represented by n rows each containing n numbers, where the j-th decimal number in a row i represents the distance between the i-th species and the j-th species. It was be assumes that the distance between the i-th species and the j-species in the input is the same as the distances between the j-th species and the i-th species.

A data structure called the Dynamic Matrix was implemented for this assignment, containing ClusterNodes and DistanceNodes. This was used to keep track of the name of the clusters as well as the distances between them.

The output of the model is the final cluster/phylogenetic tree. Included in this version is a bonus printing file that prints the final cluster as a tree.

To run:
compile the files using the makefile
./upgma species.txt
where species.txt contains the matrix of the species you wish to model

Acknowledgment of Assistance: 
This project was created and assigned by Jan Manuch at UBC as part of the CPSC 221 curriculum.
Given code was the sample input (species.txt) as well as the headers of functions of addCluster, removeCluster and findMinimum (dynmatrix.h)and the Makefile.
It was implemented by Michelle Gallant and Julilla Paul.

Files Included:
	README.txt (this file)	: details of project
	dynmatrix.h		: contains data abstraction for dynmatrix.cc
	dynmatrix.cc		: implementation of ClusterNode, DistanceNode, add/remove
	main.cc			: implementation of model
	Makefile		: for compilation
	species.txt		: source file of data for model

Special Notes:
The toPrint function included at the top was a requested bonus function, that would take in the string representation of the final cluster and print out the tree in a ‘nice’ recursive manner.