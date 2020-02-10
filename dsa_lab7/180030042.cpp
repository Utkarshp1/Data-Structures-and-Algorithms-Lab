#include<iostream>
#include<vector>
#include<fstream>
#include<cmath>

using namespace std;

struct edge {
	int u;
	int v;
	int w;
};

void make_set(int x);
int find_set(int x);
void union_set(int x, int y); 
void quick_sort(int p, int r);
int partition (int p, int r);
void kruskal();

vector<edge> g;
vector<int> f;
vector<int> r;
vector<edge> a;

int main(int argc, char* argv[]) {
	ifstream fp(argv[1], ios::in);
	ofstream fp1("mst.txt", ios::out);
	while(!(fp.eof())) {
		int u, v, w;
		int i= g.size();
		fp >> u >> v >> w;
		g.push_back(edge());
		g[i].u = u;
		g[i].v = v;
		g[i].w = w;
	}
	int max_u=0, max_v=0, size=0;
	for (int i=0; i<g.size(); i++) {
		if (g[i].u > max_u) {
			max_u = g[i].u;
		}
	}
	for (int i=0; i<g.size(); i++) {
		if (g[i].v > max_v) {
			max_v = g[i].v;
		}
	}
	if (max_u > max_v) {
		size = max_u;
	}
	else {
		size = max_v;
	}
	make_set(size);
	kruskal();
	for (int i=0; i<a.size(); i++) {
		fp1 << a[i].u << " " << a[i].v << " " << a[i].w << endl;
	}
	return 0;
}

void make_set(int x) {
	for (int i=0; i<=x; i++) {
		f.push_back(i);
		r.push_back(0);
	}
}

int find_set(int x) {
	if (f[x] != x) {
		f[x]= find_set(f[x]);
	}
	return f[x];
}

void union_set(int x, int y) {
	int xset = find_set(x);
	int yset = find_set(y);
	if (r[xset] > r[yset]) {
		f[yset] = xset;
	}
	else {
		f[xset] = yset;
		if (r[xset] == r[yset]) {
			r[yset] = r[yset] + 1;
		}
	}
}

void quick_sort(int p, int r) {
	if (p < r) {
		int q= partition(p, r);
		quick_sort(p, q-1);
		quick_sort(q+1, r); 
	}
}

int partition (int p, int r) {
	int x= g[r].w;
	int i= p-1;
	for (int j= p; j<r; j++) {
		if (g[j].w <= x) {
			i=i+1;
			swap(g[i], g[j]);
		}
	}
	swap(g[i+1], g[r]);
	return i+1;
}

void kruskal() {
	quick_sort(0, g.size()-1);
	for(int i=0; i<g.size(); i++) {
		if (find_set(g[i].u) != find_set(g[i].v)) {
			a.push_back(g[i]);
			union_set(g[i].u, g[i].v);
		}
	}
}
