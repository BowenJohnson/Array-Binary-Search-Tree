#ifndef _BST_H_
#define _BST_H_
#include "gcs.h"

class BST								// a Binary Search Tree (BST)
{
public:
	static const char	YOUR_NAME[];		// used for printing out my name
	static const bool	PREMIUM_VERSION;	

	BST(int capacity = 5);				// constructor (default if no argument supplied)
	~BST();								// destructor

	void insert(const GCS& gcs);		// insert a new item into BST
	bool remove(const char* key);		// remove item associated with key from BST
	bool retrieve(const char* key, GCS const *& gcs) const;	// retrieve item associated with key, if any
	int getSize(void) const;			// return number of items contained in the BST

	// see comments in bst.cpp for what these member functions do
	void displayArrayOrder(std::ostream& out) const;
	void displayPreOrder(std::ostream& out) const;
	void displayInOrder(std::ostream& out) const;
	void displayPostOrder(std::ostream& out) const;

private:

	int size;
	int maxsize;
	int parent;
	GCS mutable gcst;

	struct Item
	{
		bool empty;
		bool  isLeaf;
		GCS		gcs;		
	};

	// pointer to the array
	Item*	items;

	void setName(char const * const name)const; //tryig this
	void expand(int& maxsize);
	void insert(int index, const GCS& gcs);
	void displayHeaders(std::ostream& out)const;
	void displayPreOrder(std::ostream& out, int parent)const;
	void displayInOrder(std::ostream& out, int parent)const; 
	void displayPostOrder(std::ostream& out, int parent)const; 
	bool retriever(const char* key, GCS const*& gcs, int& parent)const; 
	void itemsPrinted(std::ostream& out, int size)const;
	bool Searchremove(const char* key, int parent); 		
	bool remove(int parent); 								
	void printRecord(std::ostream& out, int index)const;		
	int SearchinorderSuccessor(int parent);				

};

#endif
