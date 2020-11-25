/** Name: Kristine Monsada, 2001381858, Assignment 8*
Description:
	oh boy, it's like i'm in elementary school again and i'm playing pick up sticks!
	our pick up sticks will be maintained in an adjacency list where we will iterate thru using depth first search
	in order to detect a cycle, this is necessary because if there is a cycle, there lies dependancies thus as we simulate this game,
	we cannot pick up a stick if it's vulnerable to another stick. that is why we will only display order of what stick COULD be picked with
	cases that do not have a cycle. once we find a case with no cycle, we create another stack array  to perform a topological sort to
	determine a correct order to remove sticks from the pile of sticks
Input:
	PickUpSticks.txt
	PickThemUpAgain.txt
	OneMoreTime.txt
	text file that contains the number of vertices & the number of edges (the first two nums)
	following the blank line, a whole bunch of numbers where RHS is the node and LHS is where that node will be directed to
	these numbers will be the data that forms our graph
Output:
   IF NO CYCLE
	in each test cast output the order integers,
	listing the sticks in the order in which they could be picked
	upwithout ever picking up a stick with another stick on top of it
	(order will be maintained with topological sort when an item will get "removed")
   IF CYCLE
	you really can't pick up sticks bc of this dependency, thus the game is "IMPOSSIBLE"
*/

#include <iostream>
#include <cstdlib>

using namespace std;

// class provided by jimi :-)
template <class Type >
class vertex
{
	struct node
	{
		Type item;
		node* link;
	};
public:
	class edgeIterator
	{
	public:
		friend class vertex;
		edgeIterator();
		edgeIterator(node*);
		edgeIterator operator ++(int);
		Type operator *();
		bool operator ==(const edgeIterator&);
		bool operator !=(const edgeIterator&);
	private:
		node* current;
	};
	vertex();
	vertex(const vertex&);
	const vertex& operator =(const vertex&);
	~vertex();
	edgeIterator begin();
	edgeIterator end();
	void addEdge(const Type&);
private:
	node* neighbors;
};

/*
Constructor Name: edgeIterator
Parameters: constructor, none
Return value: constructor, none
Description: sets current to NULL
*/
template<class Type>
vertex<Type>::edgeIterator::edgeIterator()
{
	current = NULL;
}

/*
Constructor Name: edgeIterator
Parameters: constructor, none
Return value: constructor, none
Description: takes in the given edge and sets it to current
*/
template<class Type>
vertex<Type>::edgeIterator::edgeIterator(node* edge)
{
	current = edge;
}

/*
Function Name: operator++
Parameters: int
Return value: edgeIterator object
Description: iteratess to the next node and returns the edgeIterator object 
*/
template<class Type>
typename vertex<Type>::edgeIterator vertex<Type>::edgeIterator::operator++(int)
{
	// go to next object of the current
	current = current->link;
	//vertex<type>::edgeIterator iter;
	edgeIterator iter;
	// the iterator now is assigned that next's item
	iter = current;

	return iter;
}

/*
Function Name: operator*
Parameters: none
Return value: edgeIterator object
Description: returns the current item that the iterator is pointing to
*/
template<class Type>
Type vertex<Type>::edgeIterator::operator*()
{
	return current->item;
}

/*
Function Name: operator==
Parameters: edgeIterator object
Return value: returns true or false
Description: sees if the 2 objects have the same address
*/
template<class Type>
bool vertex<Type>::edgeIterator::operator==(const edgeIterator& rhs)
{
	if (current == rhs.current)
		return true;
	return false;
}

/*
Function Name: operator!=
Parameters: edgeIterator object
Return value: returns true or false
Description: sees if the 2 objects do not have the same address
*/
template<class Type>
bool vertex<Type>::edgeIterator::operator!=(const edgeIterator& rhs)
{
	if (current == rhs.current)
		return false;
	return true;
}

/*
Constructor Name: vertex
Parameters: constructor, none
Return value: constructor, none
Description: sets neighbors to NULL
*/
template<class Type>
vertex<Type>::vertex()
{
	neighbors = NULL;
}


/*
Constructor Name: vertex
Parameters: vertex object
Return value: vertex object
Description: makes a deep copy of the paseed in params with lhs
*/
template<class Type>
vertex<Type>::vertex(const vertex& copy)
{
	// no interference
	~vertex();

	while (copy != NULL)
	{
		//creates a node
		node* temp;
		temp = new node;
		//copies info into copy object
		temp->item = copy->item;
		temp->link = copy->link;
		//goes to next node
		copy = copy->link;
	}
}

/*
Function Name: operator=
Parameters: vertex object
Return value: vertex object
Description: makes a deep copy of the rhs params with lhs
*/
template<class Type>
const vertex<Type>& vertex<Type>::operator=(const vertex& rhs)
{
	if (this != &rhs)
	{
		// no interference
		~vertex();

		// while rhs does not equal NULL, keep interating and copying
		while (rhs != NULL)
		{
			// creates new node
			node* temp;
			temp = new node;
			// stores item into rhs object
			temp->item = rhs->item;
			temp->link = rhs->link;
			// goes to next node
			rhs = rhs->link;
		}
	}
	return *this;
}

/*
Function Name: deconstructor
Parameters: deconstructor, none
Return value: deconstructor, none
Description: deallocates the neighbors adjacency list
*/
template<class Type>
vertex<Type>::~vertex()
{
	node* temp;
	while (neighbors != NULL) {

		temp = neighbors;
		neighbors = neighbors->link;
		delete temp;
	}
}

/*
Function Name: begin()
Parameters: none
Return value: edgeIterator object
Description: assigns neighbor to the current object for the vertex object
*/
template<class Type>
typename vertex<Type>::edgeIterator vertex<Type>::begin()
{
	//vertex<type>::edgeIterator iter;
	edgeIterator iter;
	iter.current = neighbors;
	return iter;
}

/*
Function Name: end()
Parameters: none
Return value: edgeIterator object
Description: assign an edgeIterator object to NULL
*/
template<class Type>
typename vertex<Type>::edgeIterator vertex<Type>::end()
{
	//vertex<type>::edgeIterator iter;
	edgeIterator iter;
	iter.current = NULL;
	return iter;
}

/*
Function Name: addEdge()
Parameters: a Type edge
Return value: void, none
Description: does a head insert into the adjacency list
*/
template<class Type>
void vertex<Type>::addEdge(const Type& edge)
{
	// create a new head insert node
	node* insert = new node;

	// assign the item to what is passed in
	insert->item = edge;

	// make sure that if neighbors is null
	// the node that we just created next is null so no floaty garbage
	if (neighbors == NULL) {
		insert->link = NULL;
	}
	
	// make the next attatches it itself
	insert->link = neighbors;
	// make neighbors now point to what we just added
	neighbors = insert;
	// now that neighbors is inserted correctly, now to have insert point to nothing
	insert = NULL;
}
