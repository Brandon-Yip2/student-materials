#include <vector>
#include <queue>
#include <iostream>
using namespace std;

// TreeNode class should go in the "ufl_cap4053::fundamentals" namespace!
namespace ufl_cap4053 { namespace fundamentals {

	template <typename T>
	class TreeNode {
	
	private:
		T val;
		std::vector<TreeNode<T>*> childNodes;
		size_t numChildren;

	public:
			//Constructor for TreeNode.Should store a default - constructed data value and start with no children.
			TreeNode<T>();
			//Constructor for TreeNode.Should store element as its data valueand start with no children.
			TreeNode<T>(T element);
			//Returns a reference to the stored data.
			const T& getData() const;
			//Returns the number of children of this node.
			size_t getChildCount() const;
			//Returns the child node as specified by index.
			TreeNode<T>* getChild(size_t index);
			//Returns the child node as specified by index.Note: this is the const version of this method.
			TreeNode<T>* getChild(size_t index) const;
			//Add child to the children of this node.
			void addChild(TreeNode<T>* child);
			//Remove the child node as specified by index.
			void removeChild(size_t index);
			//Breadth - first traversal starting at this node.Calls dataFunction on the element to process it.
			void breadthFirstTraverse(void (*dataFunction)(const T)) const;
			//Pre - order traversal starting at this node.Calls dataFunction on the element to process it.
			void preOrderTraverse(void (*dataFunction)(const T)) const;
			//Post - order traversal starting at this node.Calls dataFunction on the element to process it.
			void postOrderTraverse(void (*dataFunction)(const T)) const;
		};

	//Constructor for TreeNode.Should store a default - constructed data value and start with no children.
	template <typename T>
	TreeNode<T>::TreeNode<T>() {
		this->numChildren = 0;
	}

	//Constructor for TreeNode.Should store element as its data valueand start with no children.
	template <typename T>
	TreeNode<T>::TreeNode<T>(T element) {
		this->val = element;
		this->numChildren = 0;
	}
	template <typename T>
	const T& TreeNode<T>::getData() const {
		return this->val;
	}
	template <typename T>
	size_t TreeNode<T>::getChildCount() const {
		return this->numChildren;
	}
	template <typename T>
	TreeNode<T>* TreeNode<T>::getChild(size_t index) {
		return childNodes[index];
	}

	template <typename T>
	TreeNode<T>* TreeNode<T>::getChild(size_t index) const {
		return childNodes[index];
	}

	template <typename T>
	void TreeNode<T>::addChild(TreeNode<T>* child) {
		//Make a new node
		//TreeNode<T>* adding = new TreeNode<T>();
		//adding->val = child->val;
		//adding->numChildren = child->numChildren;
		//adding->childNodes = child->childNodes;
		this->numChildren++;

		this->childNodes.push_back(child);

	

	}

	template <typename T>
	void TreeNode<T>::removeChild(size_t index) {
		
	}

	template <typename T>
	void TreeNode<T>::breadthFirstTraverse(void (*dataFunction)(const T)) const {
	
		//This Breadth first search does not need duplicate checking since we can only go down the tree, not back up ***ASSUMPTION***

		queue<TreeNode> q;
		q.push(*this);

		while (!q.empty()) {
			//Store first node
			TreeNode current = q.front();
			//Print that node
			dataFunction(q.front().val);
			//pop off the node since we already printed
			q.pop();
			//If there are children, add them to the q
			if (current.childNodes.size() > 0) {
				for (int i = 0; i < current.childNodes.size(); i++) {
					q.push(*current.childNodes[i]);
				}
			}

		}
		
	}

	template <typename T>
	void TreeNode<T>::preOrderTraverse(void (*dataFunction)(const T)) const {
	

		dataFunction(this->val);

		for (int i = 0; i<this->getChildCount(); i++) {
			(*this->childNodes[i]).preOrderTraverse(*dataFunction);
		}

	}

	template <typename T>
	void TreeNode<T>::postOrderTraverse(void (*dataFunction)(const T)) const {
	
		for (int i = 0; i < this->getChildCount(); i++) {
			(*this->childNodes[i]).postOrderTraverse(*dataFunction);
		}

		dataFunction(this->val);
	}

	
} } // namespace ufl_cap4053::fundamentals
