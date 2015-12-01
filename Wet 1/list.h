#ifndef LIST_H
#define LIST_H 1

#include <iostream>
#include <string>
#include <cstdlib>
#include <cassert>

using std::string;

template<class T> class List;
template<class T> class Iterator;
template<class T> class Node;

/** NODE **/
template<class T>
class Node {
	T element;
	Node* next;

public:
	explicit Node(const T& newElement);
	Node(const Node& copy);
	friend class Iterator<T> ;
	friend class List<T> ;
};

template<class T>
Node<T>::Node(const T& newElement) :
		element(newElement) {
	next = NULL;
}

template<class T>
Node<T>::Node(const Node<T>& copy) :
		element(copy.element) {
	next = NULL;
}

/** ITERATOR **/
template<class T>
class Iterator {
	Node<T>* index;
	List<T>* list;

public:
	/** Constructor
	 *
	 * @param list the list the iterator points to
	 * @param node the node the iterator points to
	 */
	explicit Iterator(List<T>* list, Node<T>* node);

	/** Copy Constructor
	 *
	 * @param copy the target iterator which we copy from
	 */
	Iterator(const Iterator& copy);

	/** Increment operator (prefix)
	 *
	 * @return
	 * reference to the iterator
	 */
	Iterator& operator++();

	/** Increment operator (postfix)
	 *
	 * @param dummy parameter
	 * @return
	 * reference to the iterator
	 */
	Iterator operator++(int);

	/** Dereference
	 *
	 * @return
	 * the element of the Node the iterator points to
	 */
	T& operator*() const;

	/** Assignment operator
	 *
	 * @param node the node which we assign from
	 * @return
	 * reference to the iterator
	 */
	Iterator& operator=(const Node<T>* node);

	/** Assignment operator
	 *
	 * @param i the iterator which we assign from
	 * @return
	 * reference to the iterator
	 */
	Iterator& operator=(const Iterator& i);

	/** Equals operator
	 *
	 * @param i i the iterator that we check if is equal to Iterator
	 * @return
	 * true if the iterators points at the same node, false otherwise
	 */
	bool operator==(const Iterator& i) const;

	/** Not Equals operator
	 *
	 * @param i the iterator that we check if is not equal to Iterator
	 * @return
	 * true if the iterators don't point at the same node, false otherwise
	 */
	bool operator!=(const Iterator& i) const;

	friend class List<T> ;

};

template<class T>
Iterator<T>::Iterator(List<T>* list, Node<T>* node) {
	index = node;
	this->list = list;
}

template<class T>
Iterator<T>::Iterator(const Iterator<T>& copy) {
	index = copy.index;
	list = copy.list;
}

template<class T>
Iterator<T>& Iterator<T>::operator++() {
	index = index->next;
	return *this;
}

template<class T>
Iterator<T> Iterator<T>::operator ++(int) {
	Iterator result = *this;
	++*this;
	return result;
}

template<class T>
T& Iterator<T>::operator*() const {
	assert(index);
	return index->element;
}

template<class T>
Iterator<T>& Iterator<T>::operator=(const Node<T>* node) {
	index = node;
	return *this;
}

template<class T>
Iterator<T>& Iterator<T>::operator=(const Iterator<T>& i) {
	index = i.index;
	return *this;
}

template<class T>
bool Iterator<T>::operator==(const Iterator<T>& i) const {
	return (list == i.list && index == i.index);
}

template<class T>
bool Iterator<T>::operator!=(const Iterator<T>& i) const {
	return (!(*this == i));
}

/** LIST **/

template<class T>
/*
 * Fields of the Linked list structure
 */
class List {
	Node<T>* head;
	int size;

public:

	/** A constructor of List. This constructor takes no arguments
	 *
	 * @return
	 * A new List object
	 *
	 */
	List();

	/** The copy constructor of List. The function takes a List object as a
	 * parameter and creates a new List object with the contents of the
	 * parameter
	 *
	 * @param copy the List object to copy it's contents from
	 *
	 * @return
	 *  A new List object
	 *
	 */
	List(const List<T>& copy);

	/** A destructor of List
	 */
	~List();

	/** This method defines the = (assignment) operator and allows to assign
	 * one List to another
	 *
	 * @param list the List object to assign the existing list from
	 *
	 * @return
	 * A reference to the existing list that was assigned with the list
	 * parameter
	 *
	 */
	List<T>& operator=(const List<T>& list);

	/** This method returns the number of elements in the linked list
	 *
	 * @return
	 *  The List's size
	 *
	 */
	int getSize() const;

	/** This method returns an iterator object that points at the first
	 * element of the list
	 *
	 * @return
	 * An iterator object
	 *
	 */
	Iterator<T> begin();

	/** This method returns an iterator object that points at the end of the
	 * list, which is the place the last element points at (NULL)
	 *
	 * @return
	 * An iterator object
	 *
	 */
	Iterator<T> end();

	/** This method allows to insert a new element to the linked list. It
	 * inserts the element right before the place the iterator points at
	 *
	 * @param data the content of the new element
	 * @param iterator the new element will be inserted before the place
	 * this iterator points at
	 *
	 */
	void insert(const T& data, Iterator<T> iterator);

	/** This method allows to remove an existing element from the list. It
	 * removes the element that the iterator is pointing at
	 *
	 * @param iterator the iterator that points at the element to remove
	 *
	 */
	void remove(Iterator<T> iterator);

	/** This method finds the first element in the list that fulfills the
	 * condition that was sent to the method, and returns an iterator to it.
	 * If more than one elements fulfill this condition, the method will return
	 * an iterator to the first one that fulfills it.
	 * If no element fulfills that condition, the method returns an iterator
	 * to the end (which is NULL).
	 *
	 * @param predicate a function with a condition that returns true if the
	 * element fulfills the condition and false otherwise
	 *
	 * @return
	 * An iterator object to the element that was found, or NULL if no element
	 * was found.
	 *
	 */
	template<class Predicate>
	Iterator<T> find(const Predicate& predicate);

	/** This method sorts the list according to the comparison function that
	 * is sent to it. After sorting the list, any iterators that were existed
	 * before are no longer valid.
	 *
	 * @param comparer the comparison function that takes two elements of the
	 * list and returns true if they are already in order and false otherwise
	 *
	 */
	template<class Compare>
	void sort(const Compare& comparer);
};

template<class T>
List<T>::List() {
	head = NULL;
	size = 0;
}

template<class T>
List<T>::List(const List<T>& copy) {
	if (copy.size != 0) {
		Node<T>* firstNode = new Node<T>(copy.head->element);
		this->head = firstNode;
		this->size = copy.size;
		Node<T>* fromTemp = copy.head->next;
		Node<T>* toTemp = this->head;
		while (fromTemp) {
			Node<T>* node = new Node<T>(fromTemp->element);
			toTemp->next = node;
			fromTemp = fromTemp->next;
			toTemp = toTemp->next;
		}
	} else {
		head = NULL;
		size = 0;
	}
}

template<class T>
List<T>::~List() {
	while (this->head) {
		Node<T>* temp = this->head->next;
		delete head;
		this->head = temp;
	}
}

template<class T>
List<T>& List<T>::operator=(const List<T>& list) {
	if (this == &list) {
		return *this;
	}
	while (this->head) {
		Node<T>* temp = this->head->next;
		delete head;
		this->head = temp;
	}
	if (list.size != 0) {
		Node<T>* firstNode = new Node<T>(list.head->element);
		this->head = firstNode;
		this->size = list.size;
		Node<T>* fromTemp = list.head->next;
		Node<T>* toTemp = this->head;
		while (fromTemp) {
			Node<T>* node = new Node<T>(fromTemp->element);
			toTemp->next = node;
			fromTemp = fromTemp->next;
			toTemp = toTemp->next;
		}
	} else {
		head = NULL;
		size = 0;
	}

	return *this;
}

template<class T>
int List<T>::getSize() const {
	return this->size;
}

template<class T>
Iterator<T> List<T>::begin() {
	Iterator<T> iterator = Iterator<T>(this, this->head);
	return iterator;
}

template<class T>
Iterator<T> List<T>::end() {
	Iterator<T> iterator = Iterator<T>(this, NULL);
	return iterator;
}

template<class T>
void List<T>::insert(const T& data, Iterator<T> iterator) {
	assert(iterator.list == this);
	// if the list is empty
	if (!this->head) {
		Node<T>* node = new Node<T>(data);
		this->head = node;
		(this->size)++; // Incrementing the list's size
		return;
	}
	if (iterator.index == this->head) {
		Node<T>* node = new Node<T>(data);
		this->head = node;
		node->next = iterator.index;
		(this->size)++; // Incrementing the list's size

		return;
	}
// add the new element before the place the iterator points at
	Node<T>* first = this->head;
	while (first->next != iterator.index) {
		first = first->next;
	}
	Node<T>* node = new Node<T>(data);
	first->next = node;
	node->next = iterator.index;
	(this->size)++; // Incrementing the list's size
}

template<class T>
void List<T>::remove(Iterator<T> iterator) {
	assert(this->getSize() != 0 && iterator.index && iterator.list == this);
	if (this->head == iterator.index) {
		this->head = iterator.index->next;
		delete iterator.index;
		(this->size)--; // Decrementing the list's size
		return;
	}
	Node<T>* first = this->head;
	while (first->next != iterator.index) {
		first = first->next;
	}
	first->next = iterator.index->next;
	delete iterator.index;
	(this->size)--; // Decrementing the list's size
}

template<class T>
template<class Predicate>
Iterator<T> List<T>::find(const Predicate& predicate) {
	Node<T>* temp = this->head;
	while (temp) {
		if (predicate(temp->element)) {
			Iterator<T> iterator = Iterator<T>(this, temp);
			return iterator;
		}
		temp = temp->next;
	}
	Iterator<T> endOfList(this,NULL);
	return endOfList;
}

template<class T>
template<class Compare>
void List<T>::sort(const Compare& comparer) {
	/* The comparison function gets two void* type elements,
	 compare them and returns an int. first one bigger - return negative */

	if (!(this->head) || this->size == 1) {
		return;
	}
	Node<T>* first = this->head;
	Node<T>* second = first->next;

	bool sorted = false;
	while (!sorted) {
		sorted = true;
		while (second) {
			if (!comparer(first->element, second->element)) {
				T temp = first->element;
				first->element = second->element;
				second->element = temp;
				sorted = false;
			}
			first = first->next;
			second = second->next;
		}
		first = this->head;
		second = first->next;
	}
}

#endif /* LIST_H_ */
