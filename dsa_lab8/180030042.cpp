#include<iostream>
#include<fstream>
#include<vector>
#include<limits>

using namespace std;

struct node {
	node* next;
	int key;
	int weight;
};

struct vertex {
	int key;
	int d;
};

void insert(int temp, int v, int w);
void dijkstra(int s);
void initialize_single_source(int s);
int extract_min();
void relax (int x, int y, int w);

vector<node> g; 
vector<vertex> v;
vector<vertex> a;

int main(int argc, char* argv[]) {
	ifstream fp(argv[1], ios::in);
	ofstream fp1("dijkstra.txt", ios::out);
	int s= atoi(argv[2]);
	while(!(fp.eof())) {
		int u, v, w;
		int temp=-1;
		fp >> u >> v >> w; 
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
			another.weight=0;
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
			insert(temp, v, w);
		}
		else {
			temp= g.size();
			node another;
			another.key = u;
			another.weight= 0;
			another.next = NULL;
			g.push_back(another);
			insert(temp, v, w);
		}
	}
	// for (int i=0; i<g.size(); i++) {
		// node* x;
		// x= &g[i];
		// while (x != NULL) {
			// cout << x->key << "/" << x->weight << " ";
			// x= x->next;
		// }
		// cout << endl;
	// }
	dijkstra(s);
	for (int i=0; i<a.size(); i++) {
		int x= std::numeric_limits<int>::max(); 
		if (a[i].d != x) {
			fp1 << a[i].key << " " << a[i].d << endl;
		}
		else {
			fp1 << a[i].key << " " << "-1" << endl;
		}
	}
	return 0;
}

void insert(int temp, int v, int w) {
	node* another= new node();
	another->key = v;
	another->weight= w;
	another->next= g[temp].next;
	g[temp].next= another;
}

void dijkstra(int s) {
	initialize_single_source(s);
	// for (int i=0; i<v.size(); i++) {
		// cout << v[i].d << endl;
	// }
	while(v.size()!= 0) {
		int u= extract_min();
		//cout << u << endl;
		if (u>=0) {
			a.push_back(v[u]);
			vector<vertex>:: iterator it;
			it= v.begin();
			v.erase(it+u);
			//cout << a[a.size()-1].key << endl;
			int temp= -1;
			for (int i=0; i<g.size(); i++) {
				if (g[i].key == a[a.size()-1].key) {
					temp= i;
					break;
				}
			}
			//cout << temp << endl;
			node* x;
			x= &g[temp];
			x= x->next; 
			while (x != NULL) {
				relax(g[temp].key, x->key, x->weight);
				x= x->next;
			}
		}
		else {
			for (int i=0; i<v.size(); i++) {
				a.push_back(v[i]);
			}
			break;
		}
		//cout << v.size() << endl;
		// for (int i=0; i<v.size(); i++) {
			// cout << v[i].d << endl;
		// }
		// cout << endl;
	}
}

void initialize_single_source(int s) {
	for (int i=0; i<g.size(); i++) {
		v.push_back(vertex());
		v[i].d= std::numeric_limits<int>::max();
		//v[i].pi= NULL;
		v[i].key= i;
	}
	v[s].d=0;
}

int extract_min() {
	int min=-1;
	int distance= std::numeric_limits<int>::max();
	for (int i=0; i<v.size(); i++) {
		if (v[i].d < distance) {
			min= i;
			distance = v[i].d;
		}
	}
	return min;
}

void relax (int x, int y, int w) {
	int x_i=-1, y_i=-1;
	// for (int i=0; i<v.size(); i++) {
		// if (v[i].key == x) {
			// x_i= i;
			// break;
		// }
	// } 
	for (int i=0; i<v.size(); i++) {
		if (v[i].key == y) {
			y_i= i;
			break;
		}
	} 
	if (v[y_i].d > a[a.size()-1].d + w) {
		//cout << x << " " << y << " " << w << endl;
		//cout << a[a.size()-1].d << " " << w << endl;
		v[y_i].d = a[a.size()-1].d + w;
		//cout << v[y_i].d << " " << v[y_i].key <<  endl;
		//v[y_i].pi = &v[x_i]; 
	}
}
