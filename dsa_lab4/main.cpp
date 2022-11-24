#include<iostream>
#include<fstream>
#include<cmath>
#include<vector>

using namespace std;

vector<int> m;
vector<int> q;

void mergesort(int p, int r);
void merge(int p, int q, int r); 
void quicksort(int p, int r);
int partition(int p, int r); 

int main(int argc, char* argv[]) {
	ifstream fp(argv[1], ios::in);
	ofstream fp1("mergesort.txt", ios::out);
	ofstream fp2("quicksort.txt", ios::out);
	int num;
	while (!(fp.eof())) {
		if (fp >> num) {
			m.push_back(num);
			q.push_back(num);
		}
	}
	mergesort(0, m.size()-1);
	quicksort(0, q.size()-1);
	for(int i=0; i<m.size()-1; i++) {
		fp1 << m[i] << endl;
	}
	fp1 << m[m.size()-1]; 
	for(int i=0; i<q.size()-1; i++) {
		fp2 << q[i] << endl;
	}
	fp2 << q[q.size()-1]; 
	return 0;
}

void mergesort(int p, int r) {
	if (p<r) {
		int q= floor((p+r)/2);
		mergesort(p,q);
		mergesort(q+1, r);
		merge(p,q,r);
	}
}

void merge(int p, int q, int r) {
	int n1= q-p;
	int n2= r-q-1;
	int a[q-p], b[r-q-1];
	for (int i=0; i<=(q-p); i++) {
		a[i]= m[p+i];
	}
	for(int i=0; i<=(r-q-1); i++) {
		b[i]= m[q+i+1];
	}
	int i=0, j=0;
	for(int k=p; k<=r; k++) {
		if (i>n1) {
			m[k]= b[j];
			j=j+1;
		}
		else if ( j> n2) {
			m[k]= a[i];
			i=i+1;
		}
		else if (a[i]<=b[j]) {
			m[k]= a[i];
			i=i+1;
		}
		else {
			m[k]=b[j];
			j=j+1;
		}
	}
}

void quicksort(int p, int r) {
	if (p<r) {
		int q = partition(p, r);
		quicksort(p, q-1);
		quicksort(q+1, r);
	}
}

int partition(int p, int r) {
	int a= q[r];
	int i= p-1;
	for (int j=p; j<r; j++) {
		if (q[j] <=a) {
			i=i+1; 
			swap(q[i], q[j]);
		}
	}
	swap(q[i+1], q[r]);
	return i+1; 
}