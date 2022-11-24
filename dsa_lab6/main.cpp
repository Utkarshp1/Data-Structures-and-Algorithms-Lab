#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

struct node {
	node* next;
	int key; 
};

struct vertex {
	int key;
	string color;
	int d;
	vertex* pi;
};

struct vertices {
	int key;
	string color;
	vertices* pi;
	int d, f;
};

void insert(int temp, int v); 
void bfs(int s, std::ofstream &fp1); 
void dfs(std::ofstream &fp2);
void dfs_visit (vertices* v, int* time, int i, vector<vertices> &ts); 

vector<node> g;

int main(int argc, char* argv[]) {
	ifstream fp(argv[1], ios::in);
	ofstream fp1("sd.txt", ios::out);
	ofstream fp2("ts.txt", ios::out);
	int s= atoi(argv[2]);
	while(!(fp.eof())) {
		int u, v;
		int temp=-1;
		fp >> u >> v; 
		for (int i=0; i<g.size(); i++) {
			if (g[i].key == v) {
				//cout << g[i].key << endl;
				temp=i;
				break;
			}
		}
		if (temp == -1) {
			node another;
			another.key = v;
			another.next = NULL;
			g.push_back(another);
		}
		temp = -1;
		for (int i=0; i<g.size(); i++) {
			if (g[i].key == u) {
				//cout << g[i].key << endl;
				temp=i;
				break;
			}
		}
		if (temp != -1) {
			insert(temp, v);
		}
		else {
			temp= g.size();
			node another;
			another.key = u;
			another.next = NULL;
			g.push_back(another);
			insert(temp, v);
		}
	}
	// for (int i=0; i<g.size(); i++) {
		// node* x;
		// x= &g[i];
		// while (x != NULL) {
			// cout << x->key << " ";
			// x= x->next;
		// }
		// cout << endl;
	// }
	bfs(s, fp1);
	dfs(fp2);
	return 0;
}

void insert(int temp, int v) {
	node* another= new node();
	another->key = v;
	another->next= g[temp].next;
	g[temp].next= another;
}

void bfs(int s, std::ofstream &fp1) {
	vertex v[g.size()]; 
	int temp= -1;
	for (int i=0; i<g.size(); i++) {
		if (g[i].key != s) {
			v[g[i].key].color = "white";
			v[g[i].key].d = -1;
			v[g[i].key].pi= NULL;
			
		}
		else {
			temp= i;
			v[g[i].key].color = "gray";
			v[g[i].key].d = 0;
			v[g[i].key].pi= NULL;
		}
	}
	// for (int i=0; i<g.size(); i++) {
		// cout << v[i].color << endl;
	// }
	vector<int> v1;
	v1.push_back(g[temp].key);
	//cout << v1[0] << endl;
	while(v1.size()!= 0) {
		int u= v1[0]; 
		vector<int>:: iterator it; 
		it= v1.begin();
		v1.erase(it);
		int temp1= -1; 
		for(int i=0; i<g.size(); i++) {
			if (g[i].key == u) {
				temp1= i;
				break;
			}
		}
		node* x;
		x= &g[temp1];
		x= x->next;
		while (x!= NULL) {
			if (v[x->key].color == "white") {
				v[x->key].color = "gray";
				v[x->key].d = v[u].d + 1;
				v[x->key].pi = &v[u]; 
				v1.push_back(x->key);
			} 
			x=x->next;
		}
		v[u].color = "black";
	}
	for (int i=0; i<g.size(); i++) {
		fp1 << i << " " << v[i].d << endl;
	}
}

void dfs(std::ofstream &fp2) {
	vertices v[g.size()];
	vector<vertices> ts;
	for (int i=0; i<g.size(); i++) {
		v[g[i].key].key = g[i].key;
		v[g[i].key].color = "white";
		v[g[i].key].pi = NULL;
	}
	int time=0;
	for (int i=0; i<g.size(); i++) {
		if (v[i].color == "white") {
			dfs_visit(v, &time, i, ts);
		}
	}
	// for (int i=0; i<g.size(); i++) {
		// cout << i << " " << v[i].f << endl;
	// }
	for (int i=ts.size()-1; i>=0; i--) {
		fp2 << ts[i].key << endl;
	}
}

void dfs_visit (vertices* v, int* time, int i, vector<vertices> &ts) {
	*time = *time + 1;
	v[i].d = *time;
	v[i].color = "gray";
	int temp=-1;
	for (int j=0; j<g.size(); j++) {
		if (g[j].key == i) {
			temp= j;
			break;
		}
	}
	node* x;
	x= &g[temp];
	x = x->next;
	while (x != NULL) {
		if (v[x->key].color == "white") {
			v[x->key].pi = &v[i];
			dfs_visit(v, time, x->key, ts);
		}
		x = x->next;
	}
	v[i].color = "black";
	*time = *time + 1;
	v[i].f = *time;
	ts.push_back(v[i]); 
}

