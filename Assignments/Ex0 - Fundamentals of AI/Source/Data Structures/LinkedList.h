

// LinkedList class should go in the "ufl_cap4053::fundamentals" namespace!
namespace ufl_cap4053 { namespace fundamentals {

	template <class T>
	class LinkedList {
	private:
		T var;

	public:
			
			//LinkedList<T>::Iterator
			public T operator*() const {

			};
			//Return the element at the iterator's current position in the queue. 

			public Iterator & operator++() {

			};
			//Pre - increment overload; advance the operator one position in the list.Return this iterator.NOTE: if the
			//iterator has reached the end of the list(past the last element), it should be equal to LinkedList<T>::end().

			public bool operator==(Iterator const& rhs) {

			};
			//Returns true if both iterators point to the same node in the list, and false otherwise.

			public bool operator!=(Iterator const& rhs) {

			};
			//Returns false if both iterators point to the same node in the list, and true otherwise.

			//LinkedList<T>
			public LinkedList<T>() {

			};
			//This is the constructor for LinkedList.

			public Iterator begin() const {

			};
			//Returns an Iterator pointing to the beginning of the list.

			public Iterator end() const {

			};
			//Returns an Iterator pointing past the end of the list(an invalid, unique state).

			public bool isEmpty() const {

			};
			//Returns true if there are no elements, false otherwise.

			public T getFront() const {

			};
			//Returns the first element in the list.

			public T getBack() const {

			};
			//Returns the last element in the list.

			public void enqueue(T element) {

			};
			//Inserts the specified element at the end of the list.

			public void dequeue() {

			};
			//Removes the first element from the list.

			public void pop() {

			};
			//Removes the last element from the list.

			public void clear() {

			};
			//Removes all elements from the list.

			public bool contains(T element) const {

			};
			//Returns true if you find a node whose data equals the specified element, false otherwise.

			public void remove(T element) {

			};
			//Removes the first node you find whose data equals the specified element.














	};



} }  // namespace ufl_cap4053::fundamentals
