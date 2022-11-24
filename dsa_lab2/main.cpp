#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

struct node {
	node* left;
	node* p;
	node* right;
	int key;
}; 

void insert(int num); 
void inorder(node* x, std::ofstream &fp1);
void preorder(node* x, std::ofstream &fp1);
void postorder(node* x, std::ofstream &fp1); 
node* search(node* x, int num); 
node* minimum(node* x);
node* maximum(node* x);
node* successor(node* x); 
node* predecessor(node* x);
void transplant(node* u, node* v);
void tree_delete(node* z); 
 
node *t_root = NULL; 
vector<int> v;

int main(int argc, char* argv[]){
	ifstream fp(argv[1], ios::in);
	ofstream fp1("bst.txt", ios::out);
	string task;
	int num; 
	while (!(fp.eof())) {
		fp>> task;
		if (task !="inorder" && task!="preorder" && task!="postorder" && task!="minimum" && task!="maximum") {
			fp >> num; 
		}
		if (task == "insert") {
			insert(num);
			fp1 << num << " inserted" << endl;
		}
		if (task == "inorder") {
			inorder(t_root, fp1);
			fp1 << endl;
		}
		if (task== "preorder") {
			preorder(t_root, fp1);
			fp1 << endl;
		}
		if (task== "postorder") {
			postorder(t_root, fp1);
			fp1 << endl;
		}
		if (task== "search") {
			node* x=search(t_root, num);
			if (x== NULL) {
				fp1 << num << " not found" << endl;
			}
			else {
				fp1 << num << " found" << endl;
			}
		}
		if (task == "minimum") {
			if (t_root== NULL) {
				fp1 << endl;
			}
			else {
				node* res = minimum(t_root);
				if (res!=NULL) {
					fp1 << res->key << endl;
				}
				else {
					fp1 << endl;
				}
			}
		}
		if (task == "maximum") {
			if (t_root == NULL) {
				fp1 << endl;
			}
			else {
				node* res= maximum(t_root);
				if (res!=NULL) {
					fp1 << res->key << endl;
				}
				else {
					fp1 << endl;
				}
			}
		}
		if (task == "successor") {
			node* res= search(t_root, num);
			if (res== NULL) {
				fp1 << num << " does not exist" << endl;
			}
			else {
				node* suc= successor(res); 
				if (suc == NULL) {
					fp1 << "successor of " << num << " does not exist" << endl;
				}
				else {
					fp1 << suc->key << endl;
				}
			}
		}
		if (task == "predecessor") {
			node* res= search(t_root, num);
			if (res== NULL) {
				fp1 << num << " does not exist" << endl;
			}
			else {
				node* pre= predecessor(res); 
				if (pre == NULL) {
					fp1 << "predecessor of " << num << " does not exist" << endl;
				}
				else {
					fp1 << pre->key << endl;
				}
			}
		}
		if (task == "delete") {
			node* res= search(t_root, num);
			if (res == NULL) {
				fp1 << num << " does not exist" << endl;
			}
			else {
				tree_delete(res);
				fp1 << num << " deleted" << endl;
			}
		}
		task="";
	}
	return 0;
}

void insert(int num) {
	node* another= new node(); 
	another->key = num; 
	node *y= t_root;
	node *p = nullptr;
	if (y== NULL) {
		t_root= another; 
	}
	else {
		while (y != NULL) {
			p=y;
			if (another->key < y->key) {
				y=y->left;
			}
			else {
				y=y->right;
			}
		}
		another->p=p;
		if (another->key < p->key) {
			p->left= another;
		}
		else {
			p->right = another; 
		}
	}
}

void inorder(node* x, std::ofstream &fp1) {
	if (x!= NULL) {
		inorder(x->left, fp1);
		fp1 << x->key << " "; 
		inorder(x->right, fp1); 
	}
}


void preorder(node* x, std::ofstream &fp1) {
	if (x!= NULL) {
		fp1 << x->key << " "; 
		preorder(x->left, fp1);
		preorder(x->right, fp1); 
	}
}

void postorder(node* x, std::ofstream &fp1) {
	if (x!= NULL) {
		postorder(x->left, fp1);
		postorder(x->right, fp1);
		fp1 << x->key << " "; 
	}
}

node* search(node* x, int num) {
	if (x== NULL || num == x->key) {
		return x;
	}
	if (num < x->key) {
		return search(x->left, num);
	}
	else {
		return search(x->right, num);
	}
}

node* minimum(node* x) {
	while (x->left !=NULL) {
		x= x->left;
	}
	return x;
}

node* maximum(node* x) {
	while (x->right !=NULL) {
		x= x->right;
	}
	return x; 
}

node* successor(node* x) {
	if (x->right != NULL) {
		return minimum(x->right);
	}
	node* y= x->p;
	while (y!= NULL && x == y->right) {
		x=y;
		y= y->p;
	}
	return y; 
}

node* predecessor(node* x) {
	if (x->left !=NULL) {
		return maximum(x->left);
	}
	node* y= x->p;
	while (y!= NULL && y->left==x) {
		x=y;
		y= y->p;
	}
	return y;
}

void transplant(node* u, node* v) {
	if (u->p == NULL) {
		t_root= v;
	}
	else if (u== (u->p)->left ) {
		(u->p)->left = v;
	}
	else {
		(u->p)->right= v;
	}
	if (v!= NULL) {
		v->p = u->p;
	}
}

void tree_delete(node* z) {
	if (z->left == NULL) {
		transplant(z, z->right);
	}
	else if (z->right == NULL) {
		transplant (z, z->left);
	}
	else {
		node* y= minimum(z->right);
		if (y->p != z) {
			transplant(y, y->right);
			y->right = z->right;
			(y->right)->p = y;
		}
		transplant(z, y);
		y->left = z->left;
		(y->left)->p = y; 
	}
}
