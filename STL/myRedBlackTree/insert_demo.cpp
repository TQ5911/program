#include <iostream>
using namespace std;

enum Color{red, black};
typedef struct RBnode{
	Color color;
	int data;
	RBnode* left;
	RBnode* right;
	RBnode(const int value){
		color = red;
		data = value;
		left = right = NULL;
	}
	RBnode(){
		color = red;
		left = right = NULL;
	}
	void setColor(Color c){ color = c; }
	Color getColor(){ return color; }
}RBnode;

/* These outcome from a call to the recursive insertion function describe 
   the following result:
    okay:      The color of the current root(of the subtree) has not changed; the 
			   tree now satisfies the conditions for a red-black tree
    redNode:   The current root has changed from black to red; modification may or
			   may not be needed to restore the red-black properties.
    rightRed:  The current root and its right child are now both red; a color flip
			   or rotation is needed.
    leftRed:   The current root and its left child are now both red; a color flip 
			   or rotation is needed.
    duplicate: The entry being inserted duplicates another entry; this is an error.
*/
enum RBcode{okay, redNode, leftRed, rightRed, duplicate, errorCode};
class RBtree{
	private:
		RBnode* root;
	public:
		RBtree(){
			root = NULL;
		}
		RBnode*& getRoot(){
			return root;
		}
		void setRoot(RBnode* newRoot){
			root = newRoot;
		}
		void insert(const int value);
		RBcode rb_insert(RBnode* &current, const int value);
		RBcode modifyLeft(RBnode* &current, RBcode &childStatus);
		RBcode modifyRight(RBnode* &current, RBcode &childStatus);
		void pre_order_traversal(RBnode* node);
		void in_order_traversal(RBnode* node);
	protected:
		RBcode SingleRotateRight(RBnode* &subroot);
		RBcode SingleRotateLeft(RBnode* &subroot);
		RBcode DoubleRotateRight(RBnode* &subroot);
		RBcode DoubleRotateLeft(RBnode* &subroot);
		RBcode flipColor(RBnode* &subroot);
};

void testLeftSubtree(){
	cout << "---- TEST THE LEFT SUBTREE INSERTION ----" << endl;
	RBtree tree;
	// LL:red, aunt:black
	tree.insert(9);
	tree.insert(7);
	tree.insert(5);
	cout << "LL:red, aunt:black" << endl;
	cout << "中序遍历："; tree.in_order_traversal(tree.getRoot()); cout << endl;
	cout << "前序遍历："; tree.pre_order_traversal(tree.getRoot()); cout << endl; 
	cout << endl;
	
	// LL:red, aunt:red
	tree.insert(4); // special case: root should always be black
	cout << "LL:red, aunt:red, special case" << endl;
	cout << "中序遍历："; tree.in_order_traversal(tree.getRoot()); cout << endl;
	cout << "前序遍历："; tree.pre_order_traversal(tree.getRoot()); cout << endl; 
	cout << endl;
	tree.insert(6);
	tree.insert(1);
	cout << "LL:red, aunt:red" << endl;
	cout << "中序遍历："; tree.in_order_traversal(tree.getRoot()); cout << endl;
	cout << "前序遍历："; tree.pre_order_traversal(tree.getRoot()); cout << endl; 
	cout << endl;
	
	// LR:red, aunt:black
	tree.insert(3);
	cout << "LR:red, aunt:black" << endl;
	cout << "中序遍历："; tree.in_order_traversal(tree.getRoot()); cout << endl;
	cout << "前序遍历："; tree.pre_order_traversal(tree.getRoot()); cout << endl; 
	cout << endl;
	
	// LR:red, aunt:red, two-time adjustment
	tree.insert(2);
	cout << "LR:red, aunt:red" << endl;
	cout << "中序遍历："; tree.in_order_traversal(tree.getRoot()); cout << endl;
	cout << "前序遍历："; tree.pre_order_traversal(tree.getRoot()); cout << endl; 
	cout << endl;
}

void testRightSubtree(){
	cout << "---- TEST THE RIGHT SUBTREE INSERTION ----" << endl;
	RBtree tree;
	// RR:red, aunt:black
	tree.insert(1);
	tree.insert(3);
	tree.insert(5);
	cout << "RR:red, aunt:black" << endl;
	cout << "中序遍历："; tree.in_order_traversal(tree.getRoot()); cout << endl;
	cout << "前序遍历："; tree.pre_order_traversal(tree.getRoot()); cout << endl; 
	cout << endl;
	
	// RR:red, aunt:red
	tree.insert(6); // special case: root should always be black
	cout << "RR:red, aunt:red, special case" << endl;
	cout << "中序遍历："; tree.in_order_traversal(tree.getRoot()); cout << endl;
	cout << "前序遍历："; tree.pre_order_traversal(tree.getRoot()); cout << endl; 
	cout << endl;
	tree.insert(4);
	tree.insert(9);
	cout << "RR:red, aunt:red" << endl;
	cout << "中序遍历："; tree.in_order_traversal(tree.getRoot()); cout << endl;
	cout << "前序遍历："; tree.pre_order_traversal(tree.getRoot()); cout << endl; 
	cout << endl;
	
	// RL:red, aunt:black
	tree.insert(7);
	cout << "RL:red, aunt:black" << endl;
	cout << "中序遍历："; tree.in_order_traversal(tree.getRoot()); cout << endl;
	cout << "前序遍历："; tree.pre_order_traversal(tree.getRoot()); cout << endl; 
	cout << endl;
	
	// RL:red, aunt:red, two-time adjustment
	tree.insert(8);
	cout << "RL:red, aunt:red" << endl;
	cout << "中序遍历："; tree.in_order_traversal(tree.getRoot()); cout << endl;
	cout << "前序遍历："; tree.pre_order_traversal(tree.getRoot()); cout << endl; 
	cout << endl;
}

int main(){
	testLeftSubtree();
	cout << endl;
	testRightSubtree();
	
	return 0;
} 

void RBtree::insert(const int value){
	RBcode status = rb_insert(root, value);
	switch(status){
		case redNode:
			// The root of the red-black tree should always be black
			root->setColor(black); 
			break;
		case okay:
			cout << "Insert sucessfully!" << endl;
			break;
		case duplicate:
			cout << "The entry has already existed!" << endl;
			break;
		case rightRed:
			cout << "The internal error detected in rb_insert function!" << endl;
			break;
		case leftRed:
			cout << "The internal error detected in rb_insert function!" << endl;
			break;
		default:
			cout << "Wrong returned value!" << endl;
			break;
	}
}

RBcode RBtree::rb_insert(RBnode* &current, const int value){
	RBcode status, childStatus;
	if(current==NULL){
		current = new RBnode(value);
		status = redNode;
	}
	else if(value==current->data){
		return duplicate;
	}
	else if(value<current->data){
		childStatus = rb_insert(current->left, value);
		if(childStatus==duplicate) return duplicate;
		status = modifyLeft(current, childStatus);
	}
	else if(value>current->data){
		childStatus = rb_insert(current->right, value);
		if(childStatus==duplicate) return duplicate;
		status = modifyRight(current, childStatus);
	}
	return status;
}

RBcode RBtree::modifyLeft(RBnode* &current, RBcode &childStatus){
	RBcode status = okay;
	RBnode* aunt = current->right;
	Color auntColor = black;
	if(aunt!=NULL) auntColor = aunt->getColor();
	switch(childStatus){
		case okay:
			break; // No action is needed, as the tree is already OK.
		case redNode:
			if(current->getColor()==red)
				status = leftRed;
			else
				status = okay;
			break;
		case leftRed:
			if(auntColor==black) status = SingleRotateRight(current);
			else                 status = flipColor(current);
			break;
		case rightRed:
			if(auntColor==black) status = DoubleRotateRight(current);
			else                 status = flipColor(current);
			break;
	}
	return status;
}

RBcode RBtree::modifyRight(RBnode* &current, RBcode &childStatus){
	RBcode status = okay;
	RBnode* aunt = current->left;
	Color auntColor = black;
	if(aunt!=NULL) auntColor = aunt->getColor();
	switch(childStatus){
		case okay:
			break; // No action is needed, as the tree is already OK.
		case redNode:
			if(current->getColor()==red)
				status = rightRed;
			else
				status = okay;
			break;
		case rightRed:
			if(auntColor==black) status = SingleRotateLeft(current);
			else                 status = flipColor(current);
			break;
		case leftRed:
			if(auntColor==black) status = DoubleRotateLeft(current);
			else                 status = flipColor(current);
			break;
	}
	return status;
}

// pre-order:  recursive realization
void RBtree::pre_order_traversal(RBnode* node){
	if(node==NULL) return;
	cout << node->data << "(" << ((node->color==0)?'r':'b') << ")" << " ";
	if(node->left != NULL)
		pre_order_traversal(node->left);
	if(node->right != NULL)
		pre_order_traversal(node->right);
}

// in-order: recursive realization
void RBtree::in_order_traversal(RBnode* node){
	if(node==NULL) return;
	if(node->left != NULL)
		in_order_traversal(node->left);
	cout << node->data << "(" << ((node->color==0)?'r':'b') << ")" << " ";
	if(node->right != NULL)
		in_order_traversal(node->right);
}

RBcode RBtree::SingleRotateRight(RBnode* &subroot){
	if(subroot==NULL || subroot->left==NULL) return errorCode;
	RBnode* grandparent = subroot;
	RBnode* parent = subroot->left;
	grandparent->left = parent->right;
	parent->right = grandparent;
			
	// Update the color of subtree
	grandparent->color = red;
	parent->color = black;
	
	subroot = parent;
	return okay;
}

RBcode RBtree::SingleRotateLeft(RBnode* &subroot){
	if(subroot==NULL || subroot->right==NULL) return errorCode;
	RBnode* grandparent = subroot;
	RBnode* parent = subroot->right;
	subroot->right = parent->left;
	parent->left = subroot;
	
	// Update the color of subtree
	grandparent->color = red;
	parent->color = black;
	
	subroot = parent;
	
	return okay;
}

RBcode RBtree::DoubleRotateRight(RBnode* &subroot){
	RBcode subStatus = SingleRotateLeft(subroot->left);
	if(subStatus==okay)
		return SingleRotateRight(subroot);
	else return subStatus;
}

RBcode RBtree::DoubleRotateLeft(RBnode* &subroot){
	RBcode subStatus = SingleRotateRight(subroot->right);
	if(subStatus==okay)
		return SingleRotateLeft(subroot);
	else return subStatus;
}

RBcode RBtree::flipColor(RBnode* &subroot){
	if(subroot==NULL || subroot->left==NULL || subroot->right==NULL
	|| (subroot->left->left==NULL&&subroot->left->right==NULL
	    &&subroot->right->left==NULL&&subroot->right->right==NULL))
		return errorCode;
	subroot->color = red;
	subroot->left->color = black;
	subroot->right->color = black;
	
	root->setColor(black);
	return redNode;
}
