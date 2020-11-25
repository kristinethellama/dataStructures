/** Name: Kristine Monsada, 2001381858, Assignment 6*
Description:
	let's make life slightly hard by wanting to build a custom hash class
	through this class, we want to insert words into our hash table in unique indexes so we
	are able to successfully create a hash table with fastest run time; this is because we have
	2 tables and 2 hashFunctions which will allow linear probing to be the last method we use
	in the end, every word SHOULD have a unique cubby and we will output that
Input:
	input01.txt - a file with a buncha random words
	we should be extracting this, and make all words lower case as well as remove any punctuation
Output:
	every unique word found within the txt file as well as the number of occurances that was in the file
*/

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

// hash class provided by jimi owo
template  <class  Type1, class  Type2>
class  myHash { 
	public:
		myHash(); 
		myHash(const  myHash <Type1, Type2 >&); 
		const  myHash <Type1, Type2 >& operator =(const  myHash <Type1, Type2 >&); 
		~myHash(); 
		Type2& operator [](Type1); 
		size_t getEntries();
	private:
		struct  tableItem {
			Type1  key;
			Type2  value;
		}; 
		
		size_t  hashFunction01(const  Type1&)  const; 
		size_t  hashFunction02(const  Type1&)  const; 
		void  resize(); 
		size_t  size; 
		size_t  entries; 
		tableItem* table1; 
		tableItem* table2; 
};

/*
Constructor Name: myHash constructor
Parameters: constructor, none
Return value: constructor, none
Description: makes a dynamic array to hold the hash table elements,
sets the size to 10 and sets the keys and value to their defaults and entries
variable to 0
*/
template  <class  Type1, class  Type2>
myHash<Type1, Type2>::myHash() {
	// array will be start off as size 10
	size = 10;
	// no entries to start
	entries = 0;
	// make the dynamic array of size 10
	table1 = new tableItem[size];
	table2 = new tableItem[size];

	// fill it with defaults so no garbage is inside
	for (size_t i = 0; i < size; i++) {
		table1[i].key = Type1();
		table1[i].value = Type2();
		table2[i].key = Type1();
		table2[i].value = Type2();
	}
}


/*
Constructor Name: myHash copy constructor
Parameters: myHash copy reference
Return value: copy constructor, none
Description: makes a copy of a myHash object
*/
template  <class  Type1, class  Type2> 
myHash<Type1, Type2>::myHash(const myHash<Type1, Type2>& copy) {
	
	// current object is now the copied object
	*this = copy;
	tableItem* temp1;
	tableItem* temp2;

	// now we want to create new tables that will copy table1
	// make a temp table so we will be able to assign new values
	tableItem* copyTable1 = copy.table1;
	temp1 = new tableItem[copy.size];

	// do the same thing for table 2
	tableItem* copyTable2 = copy.table2;
	temp2 = new tableItem[copy.size];

	// copy values key and values onto the temp which will copy passed in object to current object
	for (size_t i = 0; i < copy.size; i++) {
		temp1[i].key = copyTable1[i].key;
		temp1[i].value = copyTable1[i].value;
		temp2[i].key = copyTable2[i].key;
		temp2[i].value = copyTable2[i].value;
	}


}

/*
Function Name: operator= overloading
Parameters: myHash rhs reference
Return value: the myHash object now with newly copied elements
Description: like the copy constructor, copies the rhs to the actual object thru *this
*/
template  <class  Type1, class  Type2>
const myHash<Type1, Type2>& myHash<Type1, Type2>::operator=(const myHash<Type1, Type2>& rhs) {
	// same logic applies as the copy constructor
	if (this != &rhs) {

		// want to make tableItem copies to point to actual table and the rhs table
		tableItem* assignTable1 = rhs.table1;
		tableItem* temp1;
		tableItem* temp2;
		temp1 = new tableItem[rhs.size];

		// copy items from the rhs to the actual table for table1
		for (size_t i = 0; i < rhs.size; i++) {
			temp1[i].key = assignTable1[i].key;
			temp1[i].value = assignTable1[i].value;
		}

		// same thing for table2
		tableItem* assignTable2 = rhs.table2;
		temp2 = new tableItem[rhs.size];

		// copy items from the rhs to the actual table for table1
		for (size_t i = 0; i < rhs.size; i++) {
			temp2[i].key = assignTable2[i].key;
			temp2[i].value = assignTable2[i].value;
		}
	}
	// return the newly copied table
	return *this;
}


/*
Function Name: deconstructor
Parameters: deconstructor, none
Return value: deconstructor, none
Description: deallocates the myHash object
*/
template  <class  Type1, class  Type2>
myHash<Type1, Type2>::~myHash() {
	// deallocate our dynamic table1/2
	delete[] table1;
	delete[] table2;
}


/*
Function Name: hashFunction01 
Parameters: the key, in main it should be of string type
Return value: the conputed index for the even indexes of passed string
Description: should take the key and iterate thru its individual char elements
	adds up all ascii values within the even index and then mods by the hash table size
	so it has a proper index to store the word
*/
template  <class  Type1, class  Type2>
size_t myHash<Type1, Type2>::hashFunction01(const Type1& key) const {
	// this will be the even index
	size_t evenLength = 0;
	// iterates thru whole string
	for (size_t i = 0; i < key.length(); i++) {
		// add all the even indices, such as 0 2 4, etc
		if (i % 2 == 0) { 
			// add up that ascii value in key's ith index
			evenLength += key[i];
		}
	}

	// mod by size to be able to index properly
	evenLength = evenLength % size;
	return evenLength;
}

/*
Function Name: hashFunction02
Parameters: the key, in main it should be of string type
Return value: the conputed index for the odd indexes of passed string
Description: should take the key and iterate thru its individual char elements
	adds up all ascii values within the odd index, if index only has 1 character, 
	we want to muliply so we get actual value and then mods by the hash table size
	so it has a proper index to store the word
*/
template  <class  Type1, class  Type2>
size_t myHash<Type1, Type2>::hashFunction02(const Type1& key) const {
	// this will be the odd index
	size_t oddLength = 0;
	// iterates thru whole string
	for (size_t i = 0; i < key.length(); i++) {
		// we only want to add up odd indexes, such as 1 3 5 ...
		if (i % 2 == 1) {
			// sometimes we run into the issue of only having 1 char string
			// thus to take account for it, we multiply by 2 add it onto the index length 
			if (key.length() == 1) {
				oddLength += key[0] * 2;
			}
			else {
				// add
				oddLength += key[i];
			}
		}
	}

	// mod by size to get the correct index spot
	oddLength = oddLength % size;
	return oddLength;
}

/*
Function Name: operator[] overloading
Parameters: the key, in main it should be of string type
Return value: the address of the occurance counts of each word, in main this should be an int
Description: this function is the big boi, which will basically take in this key
	extract the individual characters using the hashFunctions01/02 and assign it to a specific index
	now, it will iterate thru our two tables, it first checks for an empty spot of table 1, index 1 then the key
	now checks for empty spot of table 1, index 2 then the key and then the same for table 2
	this is so we have less preventions for collisons BUT, if we do have collisons we want to increment index1/2, mod by size once again
	and repeat the process
	also when we do find an empty spot, we will also prompt to check if there the loadfactor is >=50% which we will then wanna resize 
	so more elements can get stored as main iterates thru more words :-)
*/
template  <class  Type1, class  Type2>
Type2& myHash<Type1, Type2>::operator[](Type1 key) {
	// call the hashFunctions and assign them to index1 and index 2,
	// we will further use these to check the tables1 and 2 so we find a proper space to into the hash table
	size_t index1 = hashFunction01(key);
	size_t index2 = hashFunction02(key);
	// bool to iterate thru
	// will only iterate again if we had a full linear probing collision
	bool isEmpty = true;

	while (isEmpty) {

		// set to false bc we wanna assume there is a spot
		isEmpty = false;

		//cout << static_cast<double>(entries * 1.0f / size * 1.0f) << endl;

		//cout << endl;
		//cout << "this is index1 for " << key << ": " << index1 << endl;
		//cout << "this is index2 for " << key << ": " << index2 << endl;

		/*
		CHECK IF TABLE 1, INDEX 1 IS EMPTY FIRST
			make key passed in have a new home
			increment entries bc now a unique word
			if loadfactor is >= 50% resize so elements don't get lost when we add more words onto table
			and return value address
		CHECK IF TABLE 1, INDEX 1 HAS MATCHING KEY
			simply return value address bc not unique anymore
		*/
		if (table1[index1].key == Type1()) {
			table1[index1].key = key;

			entries++;
			if (static_cast<double>(entries * 1.0f / size * 1.0f) >= static_cast<double>(0.5)) {
				resize();
			};
			return table1[index1].value;
		}
		// this if no collision on table1
		if (table1[index1].key == key) {
			return table1[index1].value;
		}

		/*
		CHECK IF TABLE 1, INDEX 2 IS EMPTY FIRST
			make key passed in have a new home
			increment entries bc now a unique word
			if loadfactor is >= 50% resize so elements don't get lost when we add more words onto table
			and return value address
		CHECK IF TABLE 1, INDEX 2 HAS MATCHING KEY
			simply return value address bc not unique anymore
		*/
		if (table1[index2].key == Type1()) {
			table1[index2].key = key;
			entries++;
			if (static_cast<double>(entries * 1.0f / size * 1.0f) >= static_cast<double>(0.5)) {
				resize();
			};
			return table1[index2].value;
		}
		// if collision on index1 of table1
		if (table1[index2].key == key) {
			return table1[index2].value;
		}

		/*
		CHECK IF TABLE 2, INDEX 1 IS EMPTY FIRST
			make key passed in have a new home
			increment entries bc now a unique word
			if loadfactor is >= 50% resize so elements don't get lost when we add more words onto table
			and return value address
		CHECK IF TABLE 2, INDEX 1 HAS MATCHING KEY
			simply return value address bc not unique anymore
		*/
		// collisions on table1, move on to table2 and repeat same ordeal
		if (table2[index1].key == Type1()) {
			table2[index1].key = key;
			entries++;
			if (static_cast<double>(entries * 1.0f / size * 1.0f) >= static_cast<double>(0.5)) {
				resize();
			};
			return table2[index1].value;
		}
		// this if no collision on table2
		if (table2[index1].key == key) {
			return table2[index1].value;
		}

		/*
		CHECK IF TABLE 2, INDEX 2 IS EMPTY FIRST
			make key passed in have a new home
			increment entries bc now a unique word
			if loadfactor is >= 50% resize so elements don't get lost when we add more words onto table
			and return value address
		CHECK IF TABLE 2, INDEX 2 HAS MATCHING KEY
			simply return value address bc not unique anymore
		*/
		// if collision on index1 of table2
		// check index2
		if (table2[index2].key == Type1()) {
			table2[index2].key = key;
			entries++;
			if (static_cast<double>(entries * 1.0f / size * 1.0f) >= static_cast<double>(0.5)) {
				resize();
			};
			return table2[index2].value;
		}
		if (table2[index2].key == key) {
			return table2[index2].value;
		}

		// this is done last if index1/2 of table 1/2 has no spots for this key word
		// want to increment so we go to the next spot
		else {
			// collsion counter
			index1 = (index1 + 1) % size;
			index2 = (index2 + 1) % size;
			// set flag to true so we iterate thru again rechecking all cases
			isEmpty = true;
		}
	}	
}

/*
Function Name: resize()
Parameters: none
Return value: none
Description: when called, this function will double the table size and rehash everything
	we sent temps to point to old tables and then create larger new ables
	then eloquently rehash using the [] operator inside hash
*/
template  <class  Type1, class  Type2>
void myHash<Type1, Type2>::resize() {
	// save old size bc we're gonna need this for rehashing
	size_t oldSize = size;

	// old table
	tableItem* temp1 = table1;
	tableItem* temp2 = table2;

	// double size bc we want a larger table now
	size = size * 2;
	// set entries to 0 to prevent duplicates bc all we wanna do is reassign keys to its correct spot
	entries = 0;

	// new tables
	table1 = new tableItem[size];
	table2 = new tableItem[size];

	// set this new table to be empty so no garbage inside
	for (size_t i = 0; i < size; i++) {
		table1[i].key = Type1();
		table1[i].value = Type2();
		table2[i].key = Type1();
		table2[i].value = Type2();
	}

	// rehash time, basically does all the [] functionality
	// gets that key from the old table to put into new table as well as making sure the value counter is maintained and assigned
	// correctly for that word
	for (size_t i = 0; i < oldSize; i++) {
		// don't wanna rehash blanks
		if(temp1[i].key != Type1())
			(*this)[temp1[i].key] = temp1[i].value;
	}

	// loop as above but for table 2
	for (size_t i = 0; i < oldSize; i++) {
		// don't wanna rehash blanks
		if(temp2[i].key != Type1())
			(*this)[temp2[i].key] = temp2[i].value;
	}

	// deallocate to prevent mem leaks
	delete[] temp1;
	delete[] temp2;
}