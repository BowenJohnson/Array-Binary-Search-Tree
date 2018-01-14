#include <iostream>
#include <iomanip>
#include "bst.h"

using namespace std;

const char	BST::YOUR_NAME[]{"Bowen Johnson"};

const bool	BST::PREMIUM_VERSION{false};

BST::BST(int capacity) :
	size{0},
	parent{0},
	gcst{},
	items(new Item[capacity])
{

	maxsize = capacity;
	items->isLeaf = true;

	for (int index = 0; index < maxsize; index++)
	{
	this->items[index].empty = true;
	}

}

BST::~BST()
{
	delete[] items;
}

void BST::insert(int parent, const GCS& gcs)
{

	if (parent >= maxsize) // size check
	{
		this->expand(maxsize); // grow array if need more room
	}

	if (items[parent].empty) // add if empty
	{
		items[parent].gcs = gcs;
		items[parent].empty = false;
		size++;
	}
	else if (gcs < items[parent].gcs) // left child placement
	{
		parent = (2 * parent) + 1;
		this->insert(parent, gcs);
	}
	else
	{
		parent = (2 * parent) + 2; // right child placement
		this->insert(parent, gcs);
	}

}

void BST::expand(int& maxsize) 
{
	Item* swap = new Item[maxsize * 2];

	for (int idx = 0; idx < maxsize * 2; idx++) //make all spots in new array empty
	{
		swap[idx].empty = true;
	}

	for (int idx = 0; idx < maxsize; idx++)
	{
		if (!items[idx].empty)
		{
			swap[idx].gcs = items[idx].gcs;
			swap[idx].empty = items[idx].empty;
		}
	}

	maxsize = maxsize * 2;
	delete[] items;
	items = NULL;
	items = swap;

}
								
bool BST:: retriever(const char* key, GCS const*& gcs, int& parent)const
{
	
		if (!items[parent].empty && parent <= maxsize)
		{
		
			if (key == items[parent].gcs)
			{
			
				gcst = key;
				*&gcs = &gcst;
				return true;	
			}
			else if (key < items[parent].gcs) // search left side
			{
				parent = (2 * parent) + 1;
				retriever(key, gcs, parent);
			}
			else							// search right side
			{
				parent = (2 * parent) + 2;
				retriever(key, gcs, parent);
			}
	
		}	

  return false;

}

void BST::displayHeaders(ostream& out)const
{
	out << endl;
	out << right;
	out << "name "
		<< setw(26) << "leaf?" << setw(7)
		<< "index" << setw(7)
		<< endl;

	out << left;
	out << setw(27)
		<< "----"
		<< setw(7) << "----"
		<< setw(9) << "----"
		<< endl;
}

bool BST::remove(int parent)
{

	// leaf deletion
	if (!items[parent].isLeaf)
	{
		items[parent].empty = true;
		size--;
	}

	// if it only has 1 child
	else if ((items[2*parent+1].empty && !items[2*parent+2].empty) || (!items[2*parent+1].empty && items[2*parent+2].empty))
	{
		if (!items[2*parent+1].empty && items[2*parent+2].empty)
		{
			items[parent].gcs = items[2*parent+1].gcs;
			items[2*parent+1].empty = true;
			size--;
		}
		else
		{
			parent = 2*parent+2;
			size--;
			return true;
		}
	}
	else // two children
	{
		int index;
		index = SearchinorderSuccessor(2*parent+2);

		items[parent] = items[index]; // copy successor to root
		items[parent].gcs = items[index].gcs;

		if (!items[index].isLeaf)
		{
			items[parent].isLeaf = true;
		}

		if (!items[2*index+2].empty)
		{
			items[index].gcs = items[2*index+2].gcs;
			items[2*index+2].empty = true;
		}

		if (!items[index].isLeaf)
		{
			items[index].empty = true;
			items[index].isLeaf = true;
		}

		size--;
	}

return false;
}

int BST::SearchinorderSuccessor(int parent)
{
	if (!items[2*parent+1].empty) // go left if full
	{
		parent = (2*parent+1);

		if (items[2*parent+1].isLeaf)
		{
			return parent;
		}

		SearchinorderSuccessor(parent);
	}
	else
	{
		return parent;
	}

return false;
}

bool BST::Searchremove(const char* key, int parent)
{
	if (!items[parent].empty && parent <= maxsize)
	{
	
		if (key == items[parent].gcs)
		{
			remove(parent);
			return true;
		}
		else if (key < items[parent].gcs)
		{
			parent = (2*parent) + 1;
			Searchremove(key, parent);
		}
		else
		{
			parent = (2*parent) + 2;
			Searchremove(key, parent);
		}
	}
return false;
}

void BST::displayPreOrder(std::ostream& out, int parent) const
{
	if (parent < maxsize)
	{
		printRecord(out, parent);
		displayPreOrder(out, 2 * parent + 1);
		displayPreOrder(out, 2 * parent + 2);
	}

	if (!parent)
	{
		itemsPrinted(out, size);
		out << endl;
	}
}

void BST::displayInOrder(std::ostream& out, int parent) const
{
	if (parent < maxsize)
	{
		displayInOrder(out, 2 * parent + 1);
		printRecord(out, parent);
		displayInOrder(out, 2 * parent + 2);
	}

	if (!parent)
	{
		itemsPrinted(out, size);
		out << endl;
	}
}

void BST::displayPostOrder(std::ostream& out, int parent) const
{
	if (parent < maxsize)
	{
		displayPostOrder(out, 2 * parent + 1); // left side
		displayPostOrder(out, 2 * parent + 2); // right side
		printRecord(out, parent);
	}

	if (!parent)
	{
		itemsPrinted(out, size);
		out << endl;
	}
}

void BST::itemsPrinted(ostream& out, int size) const
{
	out << left
	<< setw(41) << "(items printed)"
	<< setw(0) << "(" << size << ")";
}

void BST::printRecord(std::ostream& out, int index) const
{
	if (index <= maxsize)
	{
		if (!items[index].empty)
		{
			out << left
			<< setw(27) << items[index].gcs;
			out << right << setw(10);

			if (items[index].isLeaf) //changed from !items
			{
				out << left << setw(10) << "leaf";
			}

			out << setw(12) << index;
			out << endl;
		}
	}
}

// insert a new item into the BST
void BST::insert(const GCS& gcs)
{
	this->insert(parent, gcs);
}

// retrieve item associated with key
// returns true if it finds key, false if it can't
bool BST::retrieve(const char* key, GCS const *& gcs) const
{
	int parent = 0;

	retriever(key, gcs, parent);

	if (key == *gcs)
	{
		return true;
	}
	else
	{
		return false;
	}

}

// remove item associated with key from BST
bool BST::remove(const char* key)
{

	Searchremove(key, parent);

	return true;
}

// return number of items contained in the BST
int BST::getSize(void) const
{
	return maxsize;
}

// display items in the tree by traversing the array from beginning to end
void BST::displayArrayOrder(ostream& out) const
{
	displayHeaders(out);

	for (int index = 0; index < maxsize; index++)
	{
		if (!items[index].empty) // if not empty
		{
			out << left << setw(27) << items[index].gcs;
			out << right << setw(10);

			if (index > size) // leaf check
			{
				items[index].isLeaf = true; //changed from false
				out << left << setw(10) << "leaf";
			}

			if (items[2*index+1].empty && items[2*index+2].empty && index < size)
			{
				items[index].isLeaf = true;
				out << left << setw(11) << "leaf";
			}

			out << setw(12) << index;
			out << endl;
		}
	}

	if (!parent)
	{
		itemsPrinted(out, size);
		out << endl;
	}
}

// display items in the tree in preorder
void BST::displayPreOrder(ostream& out) const
{
	displayHeaders(out);
	displayPreOrder(out, parent);
}

// display items in the tree in inorder
void BST::displayInOrder(ostream& out) const
{
	displayHeaders(out);
	displayInOrder(out, parent);
}

// display items in the tree in postorder
void BST::displayPostOrder(ostream& out) const
{
	displayHeaders(out);
	displayPostOrder(out, parent);
}
