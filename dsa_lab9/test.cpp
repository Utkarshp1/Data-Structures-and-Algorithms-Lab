#include<iostream>
#include<vector>
#include<fstream>
#include<string>

using namespace std;

int ascii_value(string word);

int main(){
	ifstream fp1("input1.txt", ios::in);
	while(!(fp1.eof())) {
		string word;
		fp1 >> word;
		if (word != "") {
			int sum= ascii_value(word);
			cout << sum << endl;
		}
		else {
			continue;
		}
	}
	return 0;
}

int ascii_value(string word) {
	int l= word.length();
	int sum=0;
	for (int i=0; i<l; i++) {
		int v= word[i];
		sum += v;
	}
	return sum;
}