#include<iostream>
#include<vector>
#include<fstream>

using namespace std;

void radix_sort(vector<int> &v, int d);
void counting_sort(int a[][2], int *b, int f); 

int main(int argc, char* argv[]) {
	ifstream fp(argv[1], ios::in);
	ofstream fp1("radix.txt", ios::out);
	vector<int> v;
	int num;
	int d = atoi(argv[2]);
	while (!(fp.eof())) {
		if (fp >> num) {
			v.push_back(num);
		}
	}
	// for (int i=0; i<v.size(); i++) {
		// cout << v[i] << endl;
	// }
	radix_sort(v,d);
	for(int i=0; i<v.size()-1; i++) {
		fp1 << v[i] << endl;
	}
	fp1 << v[v.size()-1]; 
	return 0;
}
void radix_sort(vector<int> &v,  int d) {
	int a[v.size()][2];
	int e[v.size()-1];
	for (int i=0; i<v.size(); i++) {
		a[i][0]= v[i];
	}
	// for (int i=0; i<v.size(); i++) {
		// cout << a[i][0] << endl;
	// }
	for (int i=0; i<d; i++) {
		for(int j=0; j<v.size(); j++) {
			int b, c;
			c= a[j][0]; 
			for (int k=0; k<=i; k++) {
				b= c%10;
				c/=10;
			}
			a[j][1]= b; 
		} 
		// for (int j=0; j<v.size(); j++) {
			// cout << a[j][1] << endl;
		// }
		counting_sort(a, e, v.size());
		for (int j=0; j<v.size(); j++) {
			//cout << e[j] << endl;
			a[j][0]= e[j]; 
		}
	}
	for (int i=0; i<v.size(); i++) {
		v[i]= a[i][0]; 
	}
}

void counting_sort(int a[][2], int *b, int f) {
	int c[10];
	for (int i=0; i<10; i++) {
		c[i]=0;
	}
	for (int j=0; j<f; j++) {
		c[a[j][1]]= c[a[j][1]]+1;
	}
	// for (int i=0; i<10; i++) {
		// cout << c[i] << endl;
	// }
	for (int i=1; i<10; i++) {
		c[i]= c[i] + c[i-1];
	}
	//cout << c[9] << endl;
	for (int j= f-1; j>=0; j--) {
		b[c[a[j][1]]-1]= a[j][0]; 
		c[a[j][1]]= c[a[j][1]] - 1;
	}
}