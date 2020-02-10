#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

class node {
	public:
	node* prev;
	int key;
	node* next;
};

vector <node> dll;
node *l_head= dll.data();

void dll_fun(char sym, int num, std::ofstream &fp3);
void insertion(int num);
void deletion(int num, std::ofstream &fp3);
bool search(int num); 
int search_index(int num);

int main(int argc, char* argv[]) {
	ifstream fp(argv[1], ios::in);
	ofstream fp3("dll1.txt", ios::out);
	//cout << (l_head==nullptr) << endl;
	char sym;
	int num;
	if(fp.fail())
		return 0;
	fp>> sym;
	while (!(fp.eof())) {
		if (sym!='!') {
			fp>> num;
		}
		dll_fun(sym, num, fp3);
		fp >> sym; 
	}
	// for (int i=0; i< dll.size(); i++) {
		// cout << dll[i].key << endl;
	// }
	return 0;
}

void dll_fun(char sym, int num, std::ofstream &fp3){
	//if (dll.size()>=2) {
	//	cout << l_head << endl;
//	}
	if (sym =='+') {
		insertion(num);
		fp3 << "inserted " << num << endl;
	}
	if (sym =='-') {
		if (l_head == NULL) {
			fp3 << "cannot delete " << num << endl;
		}
		else {
			deletion(num, fp3);
		}
	}
	 if (dll.size()>=2) {
		 cout << l_head << " ";
		 cout << dll[dll.size()-2].prev << " " << dll.size() << endl;
	 }
}

void insertion(int num) {
	 if (dll.size()>=2) {
		cout << l_head << " ";
		 cout << dll[dll.size()-2].prev << " " << dll.size() << endl;
	 }
	node another;
	another.next = l_head;
	another.key= num;
	dll.push_back(another);
	if ((dll.size()-1) != 0) {
		l_head->prev = &dll.back();
		//cout << l_head->prev << " "; 
	}
	l_head= &dll.back(); 
}

void deletion(int num, std::ofstream &fp3) {
	bool res= search(num);
	if (!res) {
		fp3 << "cannot delete " << num << endl;
	}
	else {
		int result= search_index(num);
		//cout << result << endl; 
		node *resPoint= &dll[result];
		//cout << resPoint << " " << l_head << endl;
		//cout << l_head->key << " " << resPoint->key <<  endl;
		//cout << (resPoint->next==l_head->next && l_head->next == nullptr) << endl;
		if ((resPoint == l_head) && (dll.size()==1)) {
			l_head=NULL;
			dll.pop_back(); 
		}
		else if (resPoint == l_head) {
			cout << "hello1" << endl;
			(resPoint->next)->prev = NULL;
			l_head= resPoint->next; 
			//cout << (resPoint->next) << endl; 
			dll.pop_back();
		}
		else if (resPoint->next == NULL) {
			(resPoint->prev)->next = NULL;
			dll.erase(dll.begin());
		}
		else {
			(resPoint->next)->prev = resPoint->prev;
			
			(resPoint->prev)->next = resPoint->next;
			dll.erase(dll.begin()+result); 
		}
		fp3 << "deleted " << num << endl; 
	}	
}

bool search(int num) {
	bool res= false;
	for (int i=0; i<dll.size(); i++) {
		if (dll[i].key == num) {
			res= true; 
			break; 
		}
	}
	return res; 
}

int search_index(int num) {
	int res; 
	for (int i=0; i<dll.size(); i++) {
		//cout << dll[i].key << " "; 
		if (dll[i].key == num) {
			res= i; 
			break; 
		}
	}
	// for (int i=0; i<dll.size(); i++) {
			// cout << dll[i].key << " ";
		// }
	// cout << endl;
	// 
	return res;
}