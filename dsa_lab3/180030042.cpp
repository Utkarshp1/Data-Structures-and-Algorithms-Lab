#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

vector<int> v;

int parent(int i);
int left_child(int i);
int right_child(int i);
void max_heapify (int i);
void increase_key(int i, int key);
void insert(int key);
int maximum();
void extract_max(); 
void heapsort(std::ofstream &fp1);
void max_heapify_a (int* a, int i, int heap_size); 

int main(int argc, char* argv[]) {
	ifstream fp(argv[1], ios::in);
	ofstream fp1("heap.txt", ios::out);
	string task;
	int num, num1;
	while (!(fp.eof())) {
		fp >> task;
		if (task != "maximum" && task != "extract-max" && task != "sort") {
			fp >> num;
		}
		if (task == "increase-key") {
			fp >> num1;
			if (v.size()==0) {
				fp1 << endl;
			}
			else {
				if (num > (v.size()-1)) {
					fp1 << endl;
				}
				else {
					if (v[num] > num1) {
						fp1 << num1 << " is less than the current key at " << num << endl;
					}
					else if (v[num] == num1) {
						fp1 << "Key at " << num << " changed to " << num1 << endl;
					}
					else {
						increase_key(num, num1);
						fp1 << "Key at " << num << " changed to " << num1 << endl;
					}
				}
			}
		}
		if (task == "insert") {
			insert(num);
			fp1 << num << " inserted" << endl;
		}
		if (task == "maximum") {
			if (v.size() == 0) {
				fp1 << endl;
			}
			else {
				int max= maximum();
				fp1 << max << endl;
			}
		}
		if (task == "extract-max") {
			if (v.size() ==0) {
				fp1 << endl;
			}
			else {
				fp1 << v[0] << endl;
				extract_max();
			}
		}
		if (task == "sort") {
			heapsort(fp1); 
		}
		task =""; 
	}
	
	return 0;
}

int parent(int i) {
	int res= ((i-1)/2);
	return res;
}

int left_child(int i) {
	int res= (2*i+1);
	return res;	
}

int right_child(int i) {
	int res= (2*i +2);
	return res;
}

void max_heapify (int i) {
	int l= left_child(i);
	int r= right_child(i);
	int largest;
	if (l< v.size() && v[l] > v[i]) {
		largest=l;
	}
	else {
		largest= i;
	}
	if (r < v.size() && v[r] > v[largest]) {
		largest =r;
	}
	if (largest !=i) {
		swap(v[i], v[largest]);
		max_heapify(largest); 
	}
}

void increase_key(int i, int key) {
	v[i]= key;
	while (i>0 && v[i] > v[parent(i)]) {
		swap(v[i], v[parent(i)]);
		i= parent(i);
	}
}

void insert(int key) {
	v.push_back(-1);
	increase_key(v.size()-1, key); 
}

int maximum() {
	return v[0];
}

void extract_max() {
	int max= v[0];
	v[0] = v[v.size()-1];
	v.pop_back();
	max_heapify(0);
}

void heapsort(std::ofstream &fp1) {
	if (v.size() == 0) {
		fp1 << endl;
	}
	else {
		int a[v.size()];
		int heap_size= v.size();
		for (int i=0; i<v.size(); i++) {
			a[i]= v[i];
		}
		while (heap_size>1) {
			swap(a[0], a[heap_size -1]);
			heap_size--;
			max_heapify_a(a, 0, heap_size);
		} 
		for(int i=0; i<v.size(); i++) {
			if (i== v.size()-1) {
				fp1 << a[i] << endl;
			}
			else {
				fp1 << a[i] << " ";
			}
		}
	}
}

void max_heapify_a (int* a,int i, int heap_size) {
	int l= left_child(i);
	int r= right_child(i);
	int largest;
	if (l< heap_size && a[l] > a[i]) {
		largest=l;
	}
	else {
		largest= i;
	}
	if (r < heap_size && a[r] > a[largest]) {
		largest =r;
	}
	if (largest !=i) {
		swap(a[i], a[largest]);
		max_heapify_a(a, largest, heap_size); 
	}
}