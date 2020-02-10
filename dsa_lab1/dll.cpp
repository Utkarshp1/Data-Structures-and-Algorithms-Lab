#include<iostream>
#include<fstream>

using namespace std;

struct node {
	node* prev;
	int key;
	node* next;
};

void dll_fun(char sym, int num, std::ofstream &fp3);
void insertion(int num);
void deletion(int num, std::ofstream &fp3); 
node* search(int num); 
void display_dll(std::ofstream &fp3); 

node *l_head=NULL;


int main(int argc, char* argv[]) {
	ifstream fp(argv[1], ios::in);
	ofstream fp1("stack1.txt", ios::out);
	ofstream fp2("queue1.txt", ios::out);
	ofstream fp3("dll1.txt", ios::out);
	char sym;
	int num; 
	int s_top= -1;
	int length= atoi(argv[2]);  
	int stack[length];
	int queue[length+1];  
	fp>> sym;
	while (!(fp.eof())){		
		if (sym!='!') {
			fp>> num;
		} 
		dll_fun(sym, num, fp3);
		//cout << dll.size() << '\n' << endl; 
		fp>> sym;
	}
return 0;
}

void dll_fun(char sym, int num, std::ofstream &fp3){
	if (sym== '+') {
		insertion(num);
		fp3 << "inserted " << num << endl;
	}
	if (sym =='-') {
		deletion(num, fp3); 
	}
	if (sym =='?') {
		node* res= search(num); 
		if (res== NULL) {
			fp3 << "not found " << num << endl;
		}
		else {
			fp3 << "found " << num << endl;
		}
	}
	if (sym=='!') {
		display_dll(fp3); 
	}
}

void insertion(int num) {
	node* another=new node();
	another->key= num;
	
	if (l_head != NULL) {
		another->next= l_head;
		l_head->prev= another;
		l_head= another;
	}
	else {
		l_head= another; 
	}
	 
}

void deletion(int num, std::ofstream &fp3) {
	node *x = search(num);
	if (x==NULL) {
		fp3 << "cannot delete " << num << endl;
	}
	else{
		if (x== l_head && x->next==NULL) {
			l_head == NULL;
		}  
		else if (x==l_head) {
			(x->next)->prev = NULL;
			l_head= x->next;
		}
		else if (x->next == NULL) {
			(x->prev)->next = NULL;
		}
		else {
			(x->next)->prev = x->prev;
			(x->prev)->next= x->next;
		}
		fp3 << "deleted " << num << endl;
	}
	
}

node* search(int num) {
	node *x= l_head; 
	while(x!=NULL) {
		if (x->key == num) { 
			return x;  
		}
		x= x->next; 
	}
	return x; 
}
void display_dll(std::ofstream &fp3) {
	node* x= l_head;
	while (x!= NULL) {
		fp3 << x->key << " ";
		x= x->next; 
	}
	fp3 << endl;
} 
