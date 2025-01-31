#include <iterator>


// LinkedList class should go in the "ufl_cap4053::fundamentals" namespace!
namespace ufl_cap4053 { namespace fundamentals {

	template <class T>
	class LinkedList {
	
	public:

		struct Node {
			T data;
			Node* next;
			Node* prev;

		};

		class Iterator {
		friend class LinkedList;

		private:
			Node* pointing;

		public:

			Iterator() {
				this->pointing = nullptr;
			}

			Iterator(Node* initialize) {
				if (this->pointing != nullptr && initialize != nullptr) {
					this->pointing->data = initialize->data;
				}
				this->pointing = initialize;
			}

			//Return the element at the iterator's current position in the queue.
			T operator*() const {
				return pointing->data;
			};

			//Pre - increment overload; advance the operator one position in the list.Return this iterator.NOTE: if the
			//iterator has reached the end of the list(past the last element), it should be equal to LinkedList<T>::end().
			Iterator& operator++() {

				//Store a pointer to *this to return later
				Iterator current = *this;
				this->pointing = this->pointing->next;
				return current;
	
			};

			//Returns true if both iterators point to the same node in the list, and false otherwise.
			bool operator==(Iterator const& rhs) {
				return (this->pointing == rhs.pointing);
			};

			//Returns false if both iterators point to the same node in the list, and true otherwise.
			bool operator!=(Iterator const& rhs) {
				return (this->pointing != rhs.pointing);
			};

		};

			

			//This is the constructor for LinkedList.
			LinkedList<T>() {
				this->head = nullptr;
				this->numOfNodes = 0;
			};

			//Destructor
			~LinkedList() {
				
				this->clear();

			}

			//Returns an Iterator pointing to the beginning of the list.
			Iterator begin() const {
				if (this->head == nullptr) {
					return Iterator();
				}
				return Iterator(this->head);
			};

			//Returns an Iterator pointing past the end of the list(an invalid, unique state).
			Iterator end() const {
				return Iterator();
			};

			//Returns true if there are no elements, false otherwise.
			bool isEmpty() const {
				if (this->numOfNodes == 0) {
					return true;
				}
				return false;
			};
			
			//Returns the first element in the list.
			T getFront() const {
				return this->head->data;
			};
			
			//Returns the last element in the list.
			T getBack() const {
				return this->tail->data;
			};
			
			//Inserts the specified element at the end of the list.
			void enqueue(T element) {
				this->numOfNodes++;
				//Head doesn't exist (0 length list), make a node and set head to it
				if (this->head == nullptr) {
					Node* newHead = new Node();
					newHead->data = element;
					this->head = newHead;
					this->tail = newHead;

				}
				else {
					//Iterate until the end using curr
					Node* curr = this->head;
					while (curr->next != nullptr) {
						curr = curr->next;
					}
					
					Node* newTail = new Node();
					newTail->data = element;
					curr->next = newTail;
					newTail->prev = curr;

					this->tail = newTail;

				}


				
				
			};
			
			//Removes the first element from the list.
			void dequeue() {
				Node* toDelete = this->head;
				//Only works if the head is not nullptr (list has 1 node)
				if (this->head != nullptr) {
					this->numOfNodes--;
					//If the list has more than one node 
					if (this->head->next != nullptr) {
						//
						this->head = this->head->next;
						this->head->prev = nullptr;
						delete toDelete;

					}
					else {
						this->head = nullptr;
						delete toDelete;
					}

				}

			};
			
			//Removes the last element from the list.
			void pop() {

				Node* curr = this->head;
				
				//if there are elements
				if (this->head != nullptr) {
					this->numOfNodes--;
					while (curr->next != nullptr) {
						curr = curr->next;
					}
					//curr is the last element
					if (curr->prev == nullptr) {
						//curr is the only element (head and tail)
						this->tail = nullptr;
						this->head = nullptr;
						Node* toDelete = curr;
						curr = nullptr;
						delete toDelete;

					}
					else {
						this->tail = curr->prev;
						Node* toDelete = curr;

						Node* before = curr->prev;
						before->next = nullptr;

						curr = nullptr;
						delete toDelete;
				
					}

				}


			};
			
			//Removes all elements from the list.
			void clear() {

				Node* temp = new Node();
				this->tail = nullptr;
				while (this->head != nullptr) {
					temp = head;
					head = head->next;
					free(temp);
				}



			};
			
			//Returns true if you find a node whose data equals the specified element, false otherwise.
			bool contains(T element) const {
					
				//if there are elements
				if (this->head != nullptr) {
					//if head has the element
					if (this->head->data == element) {
						return true;
					}
					
					Node* curr = this->head;
					while (curr->next != nullptr) {
						curr = curr->next;
						if (curr->data == element) {
							return true;
						}
					}
				
				
				}
				return false;


				
			};
			
			//Removes the first node you find whose data equals the specified element.
			void remove(T element) {

				if (this->head != nullptr) {
					//Initial check if there is only a head
					if (this->head->next == nullptr) {
						this->head = nullptr;
						delete this->head;
					}
					else {
						//There is more than one node, iterate and find the first
						Node* curr = this->head;
						while (curr->next != nullptr || curr->data == element) {
							
							//We found the first element, Delete according to 3 rules
							if (curr->data == element) {
								
								//If curr was the head
								if (curr == this->head) {
									Node* toDelete = curr;
									curr->next->prev = nullptr;
									this->head = curr->next;
									delete toDelete;
									break;
								}

								//Curr was in the middle
								else if (curr->prev != nullptr && curr->next != nullptr) {
									Node* before = curr->prev;
									Node* after = curr->next;

									before->next = after;
									after->prev = before;

									delete curr;
									break;


								}
								//If curr was the last
								else {
									this->tail = curr->prev;
									curr->prev->next = nullptr;
									delete curr;
									break;

								}

								
							}

							curr = curr->next;

						}



					}

				}



			};

		private:
			Node* head;
			Node* tail;
			int numOfNodes;

	};



} }  // namespace ufl_cap4053::fundamentals
