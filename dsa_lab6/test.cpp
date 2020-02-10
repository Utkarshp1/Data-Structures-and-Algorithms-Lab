#include<iostream>
#include<vector>

using namespace std;

int main() {
	vector<int> v;
	vector<int>:: iterator it;
	v.push_back(1);
	v.push_back(2);
	it = v.begin();
	cout << v.size() << endl;
	v.erase(it);
	cout << "hello" << endl;
	cout << v[0] << endl;
	return 0;
}