#include<iostream>
#include<vector>

using namespace std;

int main() {
	vector<int> v1;
	vector<int> v2;
	v1.push_back(1);
	v2.push_back(2);
	v2= v1;
	for (int i=0; i<v2.size(); i++) {
		cout << v2[i] << endl;
	}
	return 0;
}