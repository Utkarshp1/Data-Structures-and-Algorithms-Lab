#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<bits/stdc++.h>

using namespace std;

struct word {
	string q;
	word* next;
};

int ascii_value(string word);
void insert(string q, word* words, int sum, int size);
void search(string q, word* words, int sum, int size, std::ofstream &fp);

int main(int argc, char* argv[]) {
	ifstream fp1(argv[1], ios::in);
	ifstream fp2(argv[3], ios::in);
	ofstream fp("anagrams.txt", ios::out);
	int size= atoi(argv[2]);
	word words[size];
	for(int i=0; i<size; i++) {
		words[i].q = "-1";
		words[i].next = NULL;
	}
	while(!(fp1.eof())) {
		string word;
		fp1 >> word;
		if (word != "") {
			int sum= ascii_value(word);
			//cout << sum << endl;
			insert(word, words, sum, size);
		}
		else {
			continue;
		}
	}
	// word* x;
	// for (int i=0; i<size; i++) {
		// x= &words[i];
		// x= x->next;
		// while(x != NULL) {
			// cout << x->q << " ";
			// x= x->next;
		// }
		// cout << endl;
	// }
	while(!(fp2.eof())) {
		string word;
		fp2 >> word;
		if (word != "") {
			int sum= ascii_value(word);
			search(word, words, sum, size, fp);
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

void insert(string q, word* words, int sum, int size) {
	int slot= sum%size;
	word* another= new word();
	another->q = q;
	another->next = words[slot].next;
	words[slot].next = another;
}

void search(string q, word* words, int sum, int size, std::ofstream &fp) {
	//cout << q << endl;
	int s= q.length(); 
	int slot= sum%size;
	word* x;
	x= &words[slot];
	x= x->next;
	while (x != NULL) {
		vector<int> w1;
		vector<int> w2;
		// int flag=s;
		// int flag1=s;
		//cout << x->q.length() << endl;
		if (s == x->q.length()) {
			for (int i=0; i<s; i++) {
				int a= q[i];
				w1.push_back(a);
			}
			for(int j=0; j<s; j++) {
				int a= x->q[j];
				w2.push_back(a);
			}
			sort(w1.begin(), w1.end());
			sort(w2.begin(), w2.end());
			
			// for (int i=0; i<s; i++) {
				// for (int j=0; j<s; j++) {
					// if (x->q[j] != q[i]) {
						// if (j == s-1) {
							// flag = flag-1;
						// }
					// }
					// else {
						// break;
					// }
				// }
			// }
			// for (int i=0; i<s; i++) {
				// for (int j=0; j<s; j++) {
					// if (x->q[i] != q[j]) {
						// if (j == s-1) {
							// flag1 = flag1-1;
						// }
					// }
					// else {
						// break;
					// }
				// }
			// }
		}
		else {
			x=x->next;
			continue;
		}
		//cout << flag << endl;
		if (w1 == w2) {
			fp << x->q << " ";
		}
		x= x->next;
	}
	fp << endl;
}