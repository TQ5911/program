#include <iostream>
using namespace std;

enum Color{RED, BLACK};
typedef struct node{
	Color color;
	int data;
	node* left;
	node* right;
	node* parent;
	node(){
		color = BLACK;
	}
}*RBnode;

class RBtree{
private:
	RBnode Nil;  // Sentinel Nodes
	RBnode root; // root of the tree 
	
public:
	RBtree(){
		Nil = new node;
		root = Nil;
	}
	RBnode getRoot(){
		return root;
	}
	
	// insert node into the red-black tree
	void rb_insert(int value);
			
	// recover the property of the red-black tree after insertion
	void rb_insert_fixup(RBnode z);
			
	// using a subtree V whose tree is v to replace 
	// a subtree U whose tree is u. the parent of U
	// becomes the parent node of subtree V
	void rb_transplant(RBnode u, RBnode v);
			
	// delete a node from the tree
	void rb_delete(RBnode z);
			
	// recover the property of the red-black tree after deletion
	void rb_delete_fixup(RBnode x);
			
	// find the successor node of node x
	RBnode rb_tree_minimum(RBnode x);
			
	// search for a node with key value
	RBnode search_node(int key);
			
	void pre_order_traversal(RBnode node);
	void in_order_traversal(RBnode node);
	
protected:
	void SingleRotateRight(RBnode subroot);
	void SingleRotateLeft(RBnode subroot);		
};

void testLeftSubtree();
void testRightSubtree();

int main(){
	testLeftSubtree();
	testRightSubtree();
}

void RBtree::rb_insert(int value){
	RBnode z = new node;
	z->color = RED;
	z->data = value; 
	z->left = z->right = z->parent = Nil;
	RBnode y = Nil;
	RBnode x = root;
	while(x != Nil){ // Find out the insertion point
		y = x;
		if(z->data == x->data){
			cout << "The value has existed!" << endl;
			return;
		}
		if(z->data < x->data)
			x = x->left;
		else
			x = x->right;
	}
	z->parent = y;
	if(y==Nil) // z is the root
		root = z;
	else if(z->data < y->data)
		y->left = z;
	else
		y->right = z;
	rb_insert_fixup(z);
}

// Recover the properties after insertion
void RBtree::rb_insert_fixup(RBnode z){
	// z is the node volidating the property 4
	while(z->parent->color==RED){
		// left subtree
		if(z->parent==z->parent->parent->left){
			RBnode y = z->parent->parent->right; // aunt node
			if(y->color==BLACK){
				if(z==z->parent->right){  // case 2
					z = z->parent;
					SingleRotateLeft(z);
				}
				z->parent->color = BLACK; // case 1
				z->parent->parent->color = RED;
				SingleRotateRight(z->parent->parent);
			}
			else{ // case 3 & case 4
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
		}
		// right subtree
		else{ 
			RBnode y = z->parent->parent->left; // aunt node
			if(y->color==BLACK){
				if(z==z->parent->left){ // case 2
					z = z->parent;
					SingleRotateRight(z);
				}
				z->parent->color = BLACK; // case 1
				z->parent->parent->color = RED;
				SingleRotateLeft(z->parent->parent);
			}
			else{
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
		} 
	} 
	root->color = BLACK;
}

void RBtree::rb_transplant(RBnode u, RBnode v){
	if(u->parent == Nil)
		root = v;
	else if(u == u->parent->left)
		u->parent->left = v;
	else 
		u->parent->right = v;
	v->parent = u->parent;
}

RBnode RBtree::rb_tree_minimum(RBnode x){
	if(x->left == Nil)
		return x;
	return rb_tree_minimum(x->left);
}

void RBtree::rb_delete(RBnode z){
	RBnode x = NULL;
	RBnode y = z;
	Color ycolor = y->color;
	if(z->left == Nil){ // only right child
		x = z->right;
		rb_transplant(z, z->right);
	}
	else if(z->right == Nil){ // only left child
		x = z->left;
		rb_transplant(z, z->left);
	}
	else{
		y = rb_tree_minimum(z->right); // the left-most node in right subtree
		ycolor = y->color;
		x = y->right;
		if(y->parent == z)
			x->parent = y;
		else{
			rb_transplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		rb_transplant(z, y);
		y->left = z->left;
		z->left->parent = y;
		y->color = z->color;
	}
	if(ycolor==BLACK)
		rb_delete_fixup(x);
}
void RBtree::rb_delete_fixup(RBnode x){
	while(x != root && x->color == BLACK){
		// left subtree
		if(x == x->parent->left){
			RBnode w = x->parent->right; // sibling node
			// Case 1
			if(w->color == RED){
				w->color = BLACK;
				x->parent->color = RED;
				SingleRotateLeft(x->parent);
				w = x->parent->right;
			} 
			// Case 2
			if(w->left->color==BLACK && w->right->color==BLACK){
				w->color = RED;
				x = x->parent;
			}
			else{
				// Case 3
				if(w->right->color==BLACK){
					w->color = RED;
					w->left->color = BLACK;
					SingleRotateRight(w);
					w = x->parent->right;
				}
				// Case 4
				w->color = w->parent->color;
				w->parent->color = BLACK;
				w->right->color = BLACK;
				SingleRotateLeft(x->parent);
				x = root; // break
			}
		}
		// right subtree
		else{ 
			RBnode w = x->parent->left;
			if(w->color==RED){ // Case 1
				w->parent->color = RED;
				w->color = BLACK;
				SingleRotateRight(x->parent);
				w = x->parent->left;
			}
			// Case 2
			if(w->left->color==BLACK && w->right->color==BLACK){
				w->color = RED;
				x = x->parent;
			}
			else{
				if(w->left->color==BLACK){   // Case 3
					w->right->color = BLACK;
					w->color = RED;
					SingleRotateLeft(w);
					w = x->parent->left;
				}
				// Case 4
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->left->color = BLACK;
				SingleRotateRight(x->parent);
				x = root; // break
			}
		}
	}
	x->color = BLACK;
}

RBnode RBtree::search_node(int key){
	RBnode cur = root;
	while(cur != Nil){
		if(cur->data==key) return cur;
		if(cur->data<key) cur = cur->right;
		else              cur = cur->left;
	}
	return NULL;
}

void RBtree::pre_order_traversal(RBnode node){
	if(node==Nil) return;
	cout << node->data << "(" << ((node->color==0)?'r':'b') << ")" << " ";
	if(node->left != Nil)
		pre_order_traversal(node->left);
	if(node->right != Nil)
		pre_order_traversal(node->right);
}

void RBtree::in_order_traversal(RBnode node){
	if(node==Nil) return;
	if(node->left != Nil)
		in_order_traversal(node->left);
	cout << node->data << "(" << ((node->color==0)?'r':'b') << ")" << " ";
	if(node->right != Nil)
		in_order_traversal(node->right);
}

// Three Step(x is original root and y is the new root):
// Step1. the right child of y becomes the left child of x
// Step2. the left child of x becomes the new root
// Step3. x becomes the right child of y
void RBtree::SingleRotateRight(RBnode x){
	RBnode y = x->left; // Step1
	x->left = y->right;
	if(y->right != Nil)
		y->right->parent = x;	
			
	y->parent = x->parent; // Step2
	if(x->parent == Nil)
		root = y;
	else if(x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->right = x; // Step3
	x->parent = y;
}

// Three Step(x is original root and y is the new root):
// Step1. the left child of y becomes the right child of x
// Step2. the right child of x becomes the new root
// Step3. x becomes the left child of y
void RBtree::SingleRotateLeft(RBnode x){
	RBnode y = x->right; // Step1
	x->right = y->left; 
	if(y->left!=Nil){
		y->left->parent = x;
	}
	
	y->parent = x->parent; // Step2
	if(x->parent==Nil){ // x is root
		root = y;
	}
	else if(x==x->parent->left)
		x->parent->left=y;
	else
		x->parent->right=y;
		
	y->left = x; // Step3
	x->parent = y; 
}

//////////////////////// Test the function ////////////////////////
void testLeftSubtree(){
	cout << "---- TEST THE LEFT SUBTREE INSERTION ----" << endl;
	
	RBtree tree;
	// LL:red, aunt:black
	tree.rb_insert(22);
	tree.rb_insert(19);
	tree.rb_insert(13);
	cout << "LL:red, aunt:black" << endl;
	cout << "中序遍历："; tree.in_order_traversal(tree.getRoot()); cout << endl;
	cout << "前序遍历："; tree.pre_order_traversal(tree.getRoot()); cout << endl; 
	cout << endl;
	
	// LL:red, aunt:red
	tree.rb_insert(10); // special case: root should always be black
	cout << "LL:red, aunt:red, special case" << endl;
	cout << "中序遍历："; tree.in_order_traversal(tree.getRoot()); cout << endl;
	cout << "前序遍历："; tree.pre_order_traversal(tree.getRoot()); cout << endl; 
	cout << endl;
	tree.rb_insert(16);
	tree.rb_insert(1);
	cout << "LL:red, aunt:red" << endl;
	cout << "中序遍历："; tree.in_order_traversal(tree.getRoot()); cout << endl;
	cout << "前序遍历："; tree.pre_order_traversal(tree.getRoot()); cout << endl; 
	cout << endl;
	
	// LR:red, aunt:black
	tree.rb_insert(7);
	cout << "LR:red, aunt:black" << endl;
	cout << "中序遍历："; tree.in_order_traversal(tree.getRoot()); cout << endl;
	cout << "前序遍历："; tree.pre_order_traversal(tree.getRoot()); cout << endl; 
	cout << endl;
	
	// LR:red, aunt:red, two-time adjustment
	tree.rb_insert(4);
	cout << "LR:red, aunt:red" << endl;
	cout << "中序遍历："; tree.in_order_traversal(tree.getRoot()); cout << endl;
	cout << "前序遍历："; tree.pre_order_traversal(tree.getRoot()); cout << endl; 
	cout << endl;
	
	cout << "------------ TEST DELETION ------------" << endl;
	// Form a tree for deletion test
	tree.rb_insert(15);
	cout << "Insert 15" << endl;
	cout << "中序遍历："; tree.in_order_traversal(tree.getRoot()); cout << endl;
	cout << "前序遍历："; tree.pre_order_traversal(tree.getRoot()); cout << endl; 
	cout << endl;
	// Case4
	tree.rb_delete(tree.search_node(19));
	cout << "right_subtree_case4: delete node valued 19" << endl;
	cout << "中序遍历："; tree.in_order_traversal(tree.getRoot()); cout << endl;
	cout << "前序遍历："; tree.pre_order_traversal(tree.getRoot()); cout << endl; 
	cout << endl;
	// Case3
	tree.rb_delete(tree.search_node(7));
	cout << "left_subtree_case3: delete node valued 7" << endl;
	cout << "中序遍历："; tree.in_order_traversal(tree.getRoot()); cout << endl;
	cout << "前序遍历："; tree.pre_order_traversal(tree.getRoot()); cout << endl; 
	cout << endl;
}

void testRightSubtree(){
	cout << "---- TEST THE RIGHT SUBTREE INSERTION ----" << endl;

	RBtree tree;
	// RR:red, aunt:black
	tree.rb_insert(1);
	tree.rb_insert(4);
	tree.rb_insert(10);
	cout << "RR:red, aunt:black" << endl;
	cout << "中序遍历："; tree.in_order_traversal(tree.getRoot()); cout << endl;
	cout << "前序遍历："; tree.pre_order_traversal(tree.getRoot()); cout << endl; 
	cout << endl;
	
	// RR:red, aunt:red
	tree.rb_insert(13); // special case: root should always be black
	cout << "RR:red, aunt:red, special case" << endl;
	cout << "中序遍历："; tree.in_order_traversal(tree.getRoot()); cout << endl;
	cout << "前序遍历："; tree.pre_order_traversal(tree.getRoot()); cout << endl; 
	cout << endl;
	tree.rb_insert(7);
	tree.rb_insert(22);
	cout << "RR:red, aunt:red" << endl;
	cout << "中序遍历："; tree.in_order_traversal(tree.getRoot()); cout << endl;
	cout << "前序遍历："; tree.pre_order_traversal(tree.getRoot()); cout << endl; 
	cout << endl;
	
	// RL:red, aunt:black
	tree.rb_insert(16);
	cout << "RL:red, aunt:black" << endl;
	cout << "中序遍历："; tree.in_order_traversal(tree.getRoot()); cout << endl;
	cout << "前序遍历："; tree.pre_order_traversal(tree.getRoot()); cout << endl; 
	cout << endl;
	
	// RL:red, aunt:red, two-time adjustment
	tree.rb_insert(19);
	cout << "RL:red, aunt:red" << endl;
	cout << "中序遍历："; tree.in_order_traversal(tree.getRoot()); cout << endl;
	cout << "前序遍历："; tree.pre_order_traversal(tree.getRoot()); cout << endl; 
	cout << endl;
	
	cout << "------------ TEST DELETION ------------" << endl;
	// Form a tree for deletion test
	tree.rb_insert(0);
	cout << "Insert 0" << endl;
	cout << "中序遍历："; tree.in_order_traversal(tree.getRoot()); cout << endl;
	cout << "前序遍历："; tree.pre_order_traversal(tree.getRoot()); cout << endl; 
	cout << endl;
	// Case3
	tree.rb_delete(tree.search_node(4));
	cout << "left_subtree_case3: delete node valued 0" << endl;
	cout << "中序遍历："; tree.in_order_traversal(tree.getRoot()); cout << endl;
	cout << "前序遍历："; tree.pre_order_traversal(tree.getRoot()); cout << endl; 
	cout << endl;
	// Case4
	tree.rb_delete(tree.search_node(16));
	cout << "right_subtree_case4: delete node valued 16" << endl;
	cout << "中序遍历："; tree.in_order_traversal(tree.getRoot()); cout << endl;
	cout << "前序遍历："; tree.pre_order_traversal(tree.getRoot()); cout << endl; 
	cout << endl;
}
