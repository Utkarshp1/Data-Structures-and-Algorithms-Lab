#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

struct node {
	public:
	node* prev;
	int key;
	node* next;
};

node *l_head=NULL;

void push(int *stack, int num, int s_top); 
int pop(int *stack, int s_top);
bool linear_search(int* stack, int num, int s_top);
void display_stack(int* stack, int s_top, std::ofstream &fp1);

void queue_fun(int* queue, char sym, int num, std::ofstream &fp2, int length);
void enqueue(int* queue, int num, int q_tail);
int dequeue(int* queue, int q_tail); 
bool linear_search_queue(int* queue, int num, int length, int q_head, int q_tail);
void display_queue(int* queue, int q_head, int q_tail, std::ofstream &fp2, int length);  

void dll_fun(char sym, int num, std::ofstream &fp3);
void insertion(int num);
void deletion(int num, std::ofstream &fp3); 
node* search(int num); 
void display_dll(std::ofstream &fp3); 


int main(int argc, char* argv[]) {
	ifstream fp(argv[1], ios::in);
	ofstream fp1("stack.txt", ios::out);
	ofstream fp2("queue.txt", ios::out);
	ofstream fp3("dll.txt", ios::out);
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
		if (sym=='+') {
			if ((s_top+1) < length) {
				s_top++;
				push(stack, num, s_top);
				fp1<< "pushed "<< num << endl;
			}
			else {
				fp1<< "overflow"<< endl;
			} 
		}
		if (sym =='-') {
			if(s_top== (-1)) {
				fp1<< "underflow"<< endl;
			}
			else {
				int rem= pop(stack, s_top); 
				fp1 << "popped " << rem << endl; 
				s_top--; 
			}
		}
		if (sym=='?') {
			bool result = linear_search(stack, num, s_top); 
			if (result == true) {
				fp1<< "found " << num << endl;
			}
			else {
				fp1<< "not found "<< num << endl; 
			}
		}
		if (sym=='!') {
			display_stack(stack, s_top, fp1); 
		}
		queue_fun(queue, sym, num, fp2, length+1);
		dll_fun(sym, num, fp3);
		//cout << dll.size() << '\n' << endl; 
		fp>> sym;
	}
	// for(int i=0; i<dll.size(); i++) {
		// cout<< dll[i].key << endl;
	// }
	return 0;
}

void push(int *stack, int num, int s_top) {
	stack[s_top]= num;	
}

int pop(int *stack, int s_top) {
	return stack[s_top]; 
}

bool linear_search(int* stack, int num, int s_top) {
	bool result; 
	for(int i=0; i<=s_top; i++) {
		if(stack[i]== num){
			result= true;
			break;
		}
		else if(i== s_top) {
			result= false;
		}
		else {
			continue; 
		}
	}
	return result; 
}

void display_stack(int* stack, int s_top, std::ofstream &fp1) {
	int num; 
	for(int i= s_top; i>=0; i--) { 
		num = stack[i]; 
		fp1 << num << " "; 
	}
	fp1<< endl; 
}

void queue_fun(int* queue, char sym, int num, std::ofstream &fp2, int length) {
	static int q_head=0, q_tail=0;
	if (sym =='+') {
		if (((q_tail+1)%length)== q_head) {
			fp2<< "overflow"<< endl;
		}
		else{
			enqueue(queue, num, q_tail);
			q_tail=(q_tail+1)%length;
			// if (q_tail== length-1) {
				// q_tail= (q_tail+1)%length;
				// enqueue(queue, num, q_tail);
				// q_tail= (q_tail+1)%length; 
			// }
			// else{
				// enqueue(queue, num, q_tail);
				// q_tail= (q_tail+1)%length;
			// }
			fp2<< "enqueued " << num << endl; 
		}
	}
	if (sym == '-') {
		int rem; 
		if (q_tail == q_head){
			fp2<< "underflow" << endl;
		}
		else {
			rem= dequeue(queue, q_head);
			q_head= (q_head+1)%length;
			// if (q_head== length-1){	
				// q_head= (q_head+1)%length;
				// rem= dequeue(queue, q_head);
				// q_head= (q_head+1)%length; 
			// }
			// else{
				// rem= dequeue(queue, q_head);
				// q_head= (q_head+1)%length;
			// }
			fp2 << "dequeued " << rem << endl;
		} 
	}
	if (sym == '?') {
		bool res= linear_search_queue(queue, num, length, q_head, q_tail);
		if (res) {
			fp2 << "found " << num << endl; 
		}
		else{
			fp2 << "not found " << num << endl; 
		}
	}
	if (sym == '!') {
		display_queue(queue, q_head, q_tail, fp2, length); 
	}
}


void enqueue(int* queue, int num, int q_tail){
	queue[q_tail]=num; 
}

int dequeue(int* queue, int q_head) {
	int rem; 
	rem=queue[q_head];
	return rem; 
}

bool linear_search_queue(int* queue, int num, int length, int q_head, int q_tail) {
	bool res;
	if (q_head < q_tail) {
		for (int i=q_head; i<q_tail; i++) {
			if( queue[i]== num){
				res= true;
				break; 
			}
			else if (i== q_tail-1) {
				res= false;
			}
			else {
				continue; 
			}
		}
	}
	else if (q_head > q_tail) {
		for (int i=0; i<q_tail; i++) {
			if( queue[i]== num){
				res= true;
				break; 
			}
			else if (i== q_tail-1) {
				res= false;
			}
			else {
				continue; 
			}
		}
		if (!res){
			for (int i=q_head; i<length-1; i++) {
				if( queue[i]== num){
					res= true;
					break; 
				}
				else if (i== length-2) {
					res= false;
				}
				else {
					continue; 
				}
			}
		}
	}
	return res;
}

void display_queue(int* queue, int q_head, int q_tail, std::ofstream &fp2, int length) {
	if(q_head < q_tail) {
		for (int i=q_head; i<q_tail; i++){
			fp2 << queue[i] << " ";
		}
	}
	else if (q_head > q_tail) {
		for (int i=q_head; i<=length-1; i++) {
			fp2 << queue[i] << " ";
		}
		for (int i=0; i<q_tail; i++) {
			fp2 << queue[i] << " ";
		}
	}
	fp2 << endl;
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
