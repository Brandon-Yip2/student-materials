

// TreeNode class should go in the "ufl_cap4053::fundamentals" namespace!
namespace ufl_cap4053 { namespace fundamentals {


	template <class T>
	class TreeNode {
	private:
		T var;

	public:

		
			//Constructor for TreeNode.Should store a default - constructed data value and start with no children.
			TreeNode<T>() {

			};

			//Constructor for TreeNode.Should store element as its data valueand start with no children.
			TreeNode<T>(T element) {

			};

			//Returns a reference to the stored data.
			const T& getData() const {

			};

			//Returns the number of children of this node.
			size_t getChildCount() const {

			};

			//Returns the child node as specified by index.
			TreeNode<T>* getChild(size_t index) {

			};

			//Returns the child node as specified by index.Note: this is the const version of this method.
			TreeNode<T>* getChild(size_t index) const {

			};

			//Add child to the children of this node.
			void addChild(TreeNode<T>* child) {

			};

			//Remove the child node as specified by index.
			void removeChild(size_t index) {

			};

			//Breadth - first traversal starting at this node.Calls dataFunction on the element to process it.
			void breadthFirstTraverse(void (*dataFunction)(const T)) const {

			};

			//Pre - order traversal starting at this node.Calls dataFunction on the element to process it.
			void preOrderTraverse(void (*dataFunction)(const T)) const {

			};

			//Post - order traversal starting at this node.Calls dataFunction on the element to process it.
			void postOrderTraverse(void (*dataFunction)(const T)) const {

			};


		};


	
} } // namespace ufl_cap4053::fundamentals
