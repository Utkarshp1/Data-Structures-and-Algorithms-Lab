#include<iostream>
#include<vector>
#include<cstdlib>
#include<bits/stdc++.h>

using namespace std;

struct lumber {
	int x, y, h, d, c, p;
	int price, weight, profit, direc;
	vector<int> trackx;
	vector<int> tracky; 
};

int path();
void calculate_profit(); 
void printPath(); 
int cutup_profit(int a, vector<int> &tempx, vector<int> &tempy); 
int cutright_profit(int a, vector<int> &tempx, vector<int> &tempy);  
int cutdown_profit(int a, vector<int> &tempx, vector<int> &tempy);
int cutleft_profit(int a, vector<int> &tempx, vector<int> &tempy); 

vector<lumber> v;
int c_x=0, c_y=0;
int n_x, n_y;
int t, n, k;

int main() {
	cin >> t >> n >> k;
	for (int i=0; i<k; i++) {
		v.push_back(lumber());
		cin>> v[i].x;
		cin>> v[i].y;
		cin>> v[i].h;
		cin>> v[i].d;
		cin>> v[i].c;
		cin>> v[i].p;
		v[i].weight= v[i].c*v[i].d*v[i].h;
		v[i].price= v[i].p*v[i].h*v[i].d;
		v[i].profit= v[i].price; 
		v[i].direc=0; 
	}
	calculate_profit(); 
	while (t>0) {
		if (v.size() > 0) {
			int i = path(); 
			vector<int> copyx;
			vector<int> copyy; 
			vector<lumber>:: iterator it;
			it= v.begin();
			n_x= v[i].x;
			n_y= v[i].y;
			printPath();
			if (v[i].direc == 0 && t>0) {
				cout << "cut up" << endl;
			}
			if (v[i].direc == 1 && t>0) {
				cout << "cut right" << endl;
			}
			if (v[i].direc == 2 && t>0) {
				cout << "cut down" << endl;
			}
			if (v[i].direc == 3 && t>0) {
				cout << "cut left" << endl;
			}
			t= t- v[i].d;
			copyx= v[i].trackx;
			copyy= v[i].tracky;
			for (int j=0; j<copyx.size(); j++) {
				for (int k=0; k<v.size(); k++) {
					if (v[k].x == copyx[j] && v[k].y == copyy[j]) {
						v.erase(it+ k);
						break;
					}
				}
				it= v.begin();
			}
			for (int j=0; j<v.size(); j++) {
				if (v[j].x == n_x && v[j].y == n_y) {
					v.erase(it + j);
					break;
				}
			}
			c_x = n_x;
			c_y = n_y;
		}
		else {
			break;
		}
	}
	return 0;
}

void calculate_profit() {
	for (int i=0; i<v.size(); i++) {
			vector<int> tempx;
			vector<int> tempy; 
			vector<int> trackx;
			vector<int> tracky;
			int upProfit=0, rightProfit=0, downProfit=0, leftProfit=0; 
			int dprofit=0; 
		
			upProfit= cutup_profit(i, tempx, tempy);
			trackx = tempx;
			tracky = tempy;
			dprofit= upProfit;
		
			tempx.clear();
			tempy.clear(); 
			rightProfit= cutright_profit(i, tempx, tempy);
			if (rightProfit > dprofit) {
				dprofit= rightProfit;
				trackx = tempx;
				tracky = tempy;
				v[i].direc= 1; 
			}
		
			tempx.clear();
			tempy.clear(); 
			downProfit= cutdown_profit(i, tempx, tempy);
			if (downProfit > dprofit) {
				//cout << i << " " << "hello" << endl;
				dprofit= downProfit;
				//cout << dprofit << endl;
				trackx = tempx;
				tracky = tempy;
				v[i].direc= 2;
				//cout << i << " " << v[2].direc << endl;
			}
			
			tempx.clear();
			tempy.clear();  
			leftProfit= cutleft_profit(i, tempx, tempy);
			if (leftProfit > dprofit) {
				dprofit= leftProfit;
				trackx = tempx;
				tracky = tempy;
				v[i].direc=3; 
			}
			v[i].profit += dprofit;
			v[i].trackx= trackx;
			v[i].tracky= tracky;
			// for (int j=0; j< v[i].trackx.size(); j++) {
				// cout << i << " " << v[i].trackx[j] << " " << v[i].tracky[j] << endl;
			// }
	}
}

void printPath() {
	if (n_x > c_x){
		for (int i=0; i<(n_x-c_x) && t>0; i++) {
			cout << "move right" << endl;
			t--;
		}
	}
	else {
		for (int i=0; i< (c_x - n_x) && t>0; i++) {
			cout << "move left" << endl;
			t--;
		}
	}
	if (n_y > c_y) {
		for (int i=0; i< (n_y - c_y) && t>0; i++) {
			cout << "move up" << endl;
			t--;
		}
	}
	else {
		for (int i=0; i< (c_y-n_y) && t>0; i++) {
			cout << "move down" << endl;
			t--; 
		}
	}	
}

int cutup_profit(int a, vector<int> &tempx, vector<int> &tempy) {
	int profit=0; 
	int min=-1;
	int i; 
	for (i=0; i<v.size(); i++) {
		if (v[i].x == v[a].x && v[i].y > v[a].y) {
			min = i;
			break;
		}
	}
	for (int j=i+1; j<v.size(); j++) {
		if (v[j].x == v[a].x && v[j].y > v[a].y && v[j].y < v[min].y) {
			min = j;
		}
	}
	//cout << min << endl;
	if (min >0) {
		if (v[a].weight > v[min].weight && v[a].h > v[min].y-v[a].y) {
			profit= v[min].price; 
			tempx.push_back(v[min].x);
			tempy.push_back(v[min].y);
			int temp1= cutup_profit(min, tempx, tempy);
			profit= profit + temp1;
			return profit; 
		}
		else {
			return 0; 
		}
	}
	else {
		return 0;
	}
}

int cutright_profit(int a, vector<int> &tempx, vector<int> &tempy) {
	int profit=0; 
	int min=-1;
	int i; 
	for (i=0; i<v.size(); i++) {
		if (v[i].y == v[a].y && v[i].x > v[a].x) {
			min = i;
			break;
		}
	}
	//cout << min << endl;
	for (int j=i+1; j<v.size(); j++) {
		//cout << v[i].x <<" " << v[a].x << " " << v[j].x << " " << v[min].x << endl;  
		if (v[j].y == v[a].y && v[j].x > v[a].x && v[j].x < v[min].x) {
			min = j;
		}
	}
	//cout << min << endl;
	if (min >0) {
		//cout << v[a].weight << " " << v[min].weight << " " << v[a].h << " " << v[min].x-v[a].x << endl;
		if (v[a].weight > v[min].weight && v[a].h > v[min].x-v[a].x) {
			profit= v[min].price;
			tempx.push_back(v[min].x);
			tempy.push_back(v[min].y);
			int temp1= cutright_profit(min, tempx, tempy);
			profit= profit + temp1;
			return profit; 
		}
		else {
			return 0; 
		}
	}
	else {
		return 0;
	}
}

int cutdown_profit(int a, vector<int> &tempx, vector<int> &tempy) {
	int profit=0; 
	int max=-1;
	int i;
	for (i=0; i<v.size(); i++) {
		if (v[i].x == v[a].x && v[i].y < v[a].y) {
			max = i;
			break;
		}
	}
	for (int j=i+1; j<v.size(); j++) {
		if (v[j].x == v[a].x && v[j].y < v[a].y && v[j].y > v[max].y) {
			max = j;
		}
	}
	if (max >0) {
		if (v[a].weight > v[max].weight && v[a].h > v[a].y-v[max].y) {
			profit= v[max].price; 
			tempx.push_back(v[max].x);
			tempy.push_back(v[max].y);
			int temp1= cutdown_profit(max, tempx, tempy);
			profit= profit + temp1;
			return profit; 
		}
		else {
			return 0; 
		}
	}
	else {
		return 0;
	}
}

int cutleft_profit(int a, vector<int> &tempx, vector<int> &tempy) {
	int profit=0; 
	int max=-1;
	int i;
	for (i=0; i<v.size(); i++) {
		if (v[i].y == v[a].y && v[i].x < v[a].x) {
			max = i;
			break;
		}
	}
	for (int j=i+1; j<v.size(); j++) {
		//cout << v[i].x <<" " << v[a].x << " " << v[j].x << " " << v[min].x << endl;  
		if (v[j].y == v[a].y && v[j].x < v[a].x && v[j].x > v[max].x) {
			max = j;
		}
	}
	//cout << max << endl;
	if (max >0) {
		//cout << v[a].weight << " " << v[min].weight << " " << v[a].h << " " << v[min].x-v[a].x << endl;
		if (v[a].weight > v[max].weight && v[a].h > v[a].x-v[max].x) {
			profit= v[max].price;
			tempx.push_back(v[max].x);
			tempy.push_back(v[max].y);
			int temp1= cutleft_profit(max, tempx, tempy);
			profit= profit + temp1;
			return profit; 
		}
		else {
			return 0; 
		}
	}
	else {
		return 0;
	}
}

int path() {
	float max_para=0;
	int n_i=0;
	for (int i=0; i<v.size(); i++) {
		int cost= abs(v[i].x-c_x) + abs(v[i].y-c_y) + v[i].d;
		if (cost <= t) {
			float para= (float)v[i].profit/cost; 
			if (max_para < para) {
				max_para= para;
				n_i= i; 
			}
		}
	}
	return n_i; 
}


