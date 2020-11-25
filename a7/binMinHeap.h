/** Name: Kristine Monsada, 2001381858, Assignment 7*
Description:
	the horrid day comes: *registration day*, students are savages and they all want to get into the same class
	HOWEVER, depending on your registration day, you might not get into the class you want (or worse have to take the bad professor)
	the student is usain bolt, with a few extra caveats: you DO wanna be the person who enrolls earliest but sometimes your gpa, status,
	and drop class count DOES matter in order for you to get in
	getting thru the students, we maintain these checks thru a priority queue built with a binary MIN heap
	this heap will insert the students to the back of the array, then bubble up accordingly so its in the correct spot
	once we have all the students inside the heap, THE RACE IS ON!
	evaluate the heap by checking students enrollment day, gpa, status, and drop
	people that enrolled first get priority over others and then check for the rest
	program should display students to got into the class, students that are waitlisted, and students that didn't make it (RIP)
Input:
	enrollment.txt, contains the maximun enrollment capacity and the maximum waitlist capacity
	following, has all the student names and their enrollment day, gpa, status (F,SP,J,SR), and # of drops in this order
Output:
	all these students from most priority to least priority on:
	who got into the class
	who got waitlisted
	who got rejected
*/

#include <iostream>
#include <cstdlib>

using namespace std;

// templated class provided by jimi :o
template  <class  Type >
class  binMinHeap { 
	public:
		binMinHeap(int = 10); 
		binMinHeap(const  binMinHeap <Type >&); 
		~binMinHeap(); 
		const  binMinHeap <Type >& operator =(const  binMinHeap <Type >&); 
		void  insert(const  Type&); 
		void  deleteMin(); 
		Type  getMin()  const; 
		bool  isEmpty()  const;
		void  bubbleUp(size_t); 
		void  bubbleDown(size_t); 
		size_t  getSize()  const; 
	private:
		size_t  capacity;
		size_t  size; 
		Type* heapArray; 
};

/*
Constructor Name: binMaxHeap constructor
Parameters: int, capacity
Return value: constructor, none
Description: sets the capacity to given value, 
	creates a dynamic heap array, and sets size
*/
template<class Type>
binMinHeap<Type>::binMinHeap(int capacity)
{
	// assigns the objects capacity to the passed in size
	this->capacity = capacity;
	// makes new dynamic array of size capacity
	heapArray = new Type[capacity];
	// makes size 0
	size = 0;
}

/*
Constructor Name: binMaxHeap copy constructor
Parameters: binMaxHeap reference
Return value: copy constructor, none
Description: makes a deep copy of a binMaxHeap object
*/
template<class Type>
binMinHeap<Type>::binMinHeap(const binMinHeap<Type>& copy)
{
	// call destructor so no interference
	~binMinHeap();
	
	// copy the size and capacity
	this->capacity = copy.capacity;
	this->size = copy.size;
	// let heapArray be this new copied capacity
	heapArray = new Type[copy.capacity];

	// deep copy all the elements from our copy into our actual object
	for (int i = 1; i < capacity; i++)
		heapArray[i] = copy.heapArray[i];
}

/*
Function Name: deconstructor
Parameters: deconstructor, none
Return value: deconstructor, none
Description: deallocates the binMaxHeap object 
*/
template<class Type>
binMinHeap<Type>::~binMinHeap()
{
	// deallocates heapArray
	delete[] heapArray;
}

/*
Function Name: operator=
Parameters: binMaxHeap reference
Return value: void, none
Description: makes a copy of the rhs binMaxHeap object into the lhs object 
*/
template<class Type>
const binMinHeap<Type>& binMinHeap<Type>::operator=(const binMinHeap<Type>& rhs)
{
	if (this != &rhs) {

		// call destrutor so no interference
		~binMinHeap();

		// copy the size and capacity
		this->capacity = rhs.capacity;
		this->size = rhs.size;
		// let heapArray be this rhs's size
		heapArray = new Type[rhs.capacity];

		// deep copy all the elements from our copy into our actual object
		for (int i = 1; i < capacity; i++)
			heapArray[i] = rhs.heapArray[i];
	}

	// return our current object
	return *this;
}

/*
Function Name: insert
Parameters: the address of item we inserting
Return value: void, none
Description: inserts the address with all infos into heap's last position
	increases the size, and bubbles up
	resizes IF necessary
*/
template<class Type>
void binMinHeap<Type>::insert(const Type& item)
{
	// resize if necessary
	if (size == capacity) {
		
		// create a new temp dynamic array
		Type* temp; 
		capacity *= 2;
		temp = new Type[capacity];
		// copy all elements back from heapArr to temp
		for (size_t i = 0; i < size; i++)
			temp[i] = heapArray[i];

		// deallocate smaller old array
		delete[] heapArray;
		// heapArray is now larger
		heapArray = temp;
		temp = NULL;
	}

	// new item so size increases
	size++;
	// set the item to the back of the array
	heapArray[size] = item;
	// bubble up so we have item go to up to its correct priority spot
	bubbleUp(size);
}

/*Function Name: deleteMin
Parameters: none
Return value: void, none
Description: puts the last element in the first element spot and deletes
the last element by size--, & bubbles first element to bottom 
*/
template<class Type>
void binMinHeap<Type>::deleteMin()
{	
	// make sure it isn't deleting at root lvl
	if (size != 0) {
		// shove the last element of the array to root level
		// this is the new min, even if its not the true min, we will fix that
		heapArray[1] = heapArray[size];
		// now that the last element in the array is donezo
		size--;
		// starting at root, will bubble down elements to make sure all in correct spot
		bubbleDown(1);
	}
}


/*
Function Name: getMin
Parameters: none
Return value: value of min
Description: returns element 1 of heap to main 
*/
template<class Type>
Type binMinHeap<Type>::getMin() const
{
	// return min, which is the root ALWAYS
	return heapArray[1];
}

/*
Function Name: isEmpty
Parameters: none
Return value: returns true or false
Description: returns true if empty, false if not 
*/
template<class Type>
bool binMinHeap<Type>::isEmpty() const
{
	// if there's nothing inside this heapArray
	// we can see bc size will be decremented everytime we "delete" the min
	if (size == 0)
		return true;
	return false;
}


/*
Function Name: bubbleUp
Parameters: size_t index
Return value: void none
Description: Brings lowest element to the top 
*/
template<class Type>
void binMinHeap<Type>::bubbleUp(size_t index)
{	
	// if its at the root, don't do anything else
	if (index == 1)
		return;

	// get the parent's index, we will use this in comparison
	size_t parent = (index) / 2;
	//size_t parent = (index-1) / 2;

	// is what element we currently (child) on less than the parent?
	// this means it needs to go up top, so SWAP
	if(heapArray[index] < heapArray[parent]) {
		// swap parent and current 
		Type temp;
		temp = heapArray[parent];
		heapArray[parent] = heapArray[index];
		heapArray[index] = temp;
		bubbleUp(parent);
	}
}

/*
Function Name: bubbleDown
Parameters: size_t index
Return value: void, none
Description: brings highest element to the bottom 
*/
template<class Type>
void binMinHeap<Type>::bubbleDown(size_t index)
{
	// get indexes for left and right children
	size_t leftChild = (2 * index);
	size_t rightChild = (2 * index) + 1;
	size_t min = index;

	// leftside is a leaf
	if (leftChild > size)
		return;
	
	// if right side is an only child
	if (rightChild > size) {

		// is left less than its parent at index?
		// if yes, swap
		// now check left
		if (heapArray[leftChild] < heapArray[index]) {
			Type temp;
			temp = heapArray[leftChild];
			heapArray[leftChild] = heapArray[index];
			heapArray[index] = temp;
			bubbleDown(leftChild);
		}
	}

	// if left isn't a leaf 
	// is left less than its parent (at index)?
	// set that left's index to new parent/min
	if (heapArray[leftChild] < heapArray[index])
		min = leftChild;
	// now we wanna check right immediately as we check left
	// if right isn't a leaf 
	// is right less than min changed to leftChild or min still its parent (at index)
	// if so, set that right's index to new parent/min
	if (heapArray[rightChild] < heapArray[min])
		min = rightChild;

	// swap the new min, changed by right/left by the parent at index
	if (min != index) {
		// swapping
		Type temp;
		temp = heapArray[index];
		heapArray[index] = heapArray[min];
		heapArray[min] = temp;
		// recursively continue
		bubbleDown(min);
	}

}

/*
Function Name: getSize
Parameters: none
Return value: returns an int
Description: returns the size of the heap
*/
template<class Type>
size_t binMinHeap<Type>::getSize() const
{
	// return total size of the student pool
	return size;
}
