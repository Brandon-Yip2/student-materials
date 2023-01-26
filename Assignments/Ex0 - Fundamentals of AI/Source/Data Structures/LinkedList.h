#include <iterator>


// LinkedList class should go in the "ufl_cap4053::fundamentals" namespace!
namespace ufl_cap4053 { namespace fundamentals {

	template <class T>
	class LinkedList {
	
	public:

		struct Node {
			T data;
			Node* next;
		};

		class Iterator {


		};

			
			
			//Return the element at the iterator's current position in the queue.
			T operator*() const {

			};
			 
			//Pre - increment overload; advance the operator one position in the list.Return this iterator.NOTE: if the
			//iterator has reached the end of the list(past the last element), it should be equal to LinkedList<T>::end().
			Iterator & operator++() {
				
			};
			
			//Returns true if both iterators point to the same node in the list, and false otherwise.
			bool operator==(Iterator const& rhs) {

			};
			
			//Returns false if both iterators point to the same node in the list, and true otherwise.
			bool operator!=(Iterator const& rhs) {

			};


			//This is the constructor for LinkedList.
			LinkedList<T>() {
				this->head = nullptr;
				this->numOfNodes = 0;
			};

			//Returns an Iterator pointing to the beginning of the list.
			Iterator begin() const {

			};

			//Returns an Iterator pointing past the end of the list(an invalid, unique state).
			Iterator end() const {

			};

			//Returns true if there are no elements, false otherwise.
			bool isEmpty() const {

			};
			
			//Returns the first element in the list.
			T getFront() const {

			};
			
			//Returns the last element in the list.
			T getBack() const {

			};
			
			//Inserts the specified element at the end of the list.
			void enqueue(T element) {

			};
			
			//Removes the first element from the list.
			void dequeue() {

			};
			
			//Removes the last element from the list.
			void pop() {

			};
			
			//Removes all elements from the list.
			void clear() {

			};
			
			//Returns true if you find a node whose data equals the specified element, false otherwise.
			bool contains(T element) const {

			};
			
			//Removes the first node you find whose data equals the specified element.
			void remove(T element) {

			};
			



		private:
			Node* head;
			int numOfNodes;




	};



} }  // namespace ufl_cap4053::fundamentals
