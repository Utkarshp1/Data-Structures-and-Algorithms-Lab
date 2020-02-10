#include<iostream>
#include<vector>
#include<cstdlib>
#include<bits/stdc++.h>

using namespace std;

struct lumber {
	int x, y, h, d, c, p;
	int price, weight, profit, direc;
	vector<int> track; 
};

int path();
void printPath(); 
int cutup_profit(int a, vector<int> &temp);
int cutright_profit(int a, vector<int> &temp); 
int cutdown_profit(int a, vector<int> &temp);
int cutleft_profit(int a, vector<int> &temp);   

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
	
	while(t>0) {
		int temp1=0, size;
		if (v.size() > 0) {
			int i= path();
			//cout << i << endl;
			vector<lumber>:: iterator it;
			vector<int> copy;
			it = v.begin(); 
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
			//cout << v[2].direc << endl;
			t= t- v[i].d;
			sort(v[i].track.begin(), v[i].track.end()); 
			size= v[i].track.size(); 
			copy= v[i].track;
			for (int j=0; j<size; j++) {
				//cout << v[i].track[j] << endl;
				int temp= copy[j];
				temp = temp- j;
				//cout << temp << endl;
				v.erase(it + temp);
				it = v.begin();
			}
			for (int j=0; j<v.size(); j++) {
				if (n_x == v[j].x && n_y == v[j].y) {
					temp1= j; 
					break;
				}
			}
		
			v.erase(it+temp1);
			for (int j=0; j<v.size(); j++) {
				//cout << v[j].x << " " << v[j].y << endl;
				v[j].track.clear(); 
				v[j].profit = v[j].price;
			}
			c_x= n_x;
			c_y= n_y;
		}
		else {
			break; 
		}
	}
	return 0; 
}

int path() {
	float max_para=0;
	int n_i=0;
	for (int i=0; i<v.size(); i++) {
		int cost= abs(v[i].x-c_x) + abs(v[i].y-c_y) + v[i].d;
		if (cost <= t) {
			vector<int> temp;
			vector<int> track; 
			int upProfit=0, rightProfit=0, downProfit=0, leftProfit=0; 
			int dprofit=0; 
		
			upProfit= cutup_profit(i, temp);
			track = temp;
			dprofit= upProfit;
		
			temp.clear();
			rightProfit= cutright_profit(i, temp);
			if (rightProfit > dprofit) {
				dprofit= rightProfit;
				track.clear();
				track= temp;
				v[i].direc= 1; 
			}
		
			temp.clear();
			downProfit= cutdown_profit(i, temp);
			if (downProfit > dprofit) {
				//cout << i << " " << "hello" << endl;
				dprofit= downProfit;
				//cout << dprofit << endl;
				track.clear();
				track= temp;
				v[i].direc= 2;
				//cout << i << " " << v[2].direc << endl;
			}
			temp.clear(); 
			leftProfit= cutleft_profit(i, temp);
			if (leftProfit > dprofit) {
				dprofit= leftProfit;
				track.clear();
				track= temp;
				v[i].direc=3; 
			}
			v[i].profit += dprofit;
			v[i].track= track;
			
			//for (int j=0; j<track.size(); j++) {
				//cout << i << " " <<  track[j] << endl;
			// int temp= v[5].track[j];
			// v.erase(it + temp);
			// it = v.begin();
		//}
				
			float para= (float)v[i].price/cost; 
			if (max_para < para) {
				max_para= para;
				n_i= i; 
			}
		}
	}
	
	//cout << max_para << " " << n_i << endl; 
	return n_i;   
}

// void path() {
	// int cost= abs((c_x-(v[0].x)) + (c_y-(v[0].y))); 
	// int pos;
	// int n_x=v[0].x, n_y=v[0].y;
	// for (int i=1; i<v.size(); i++) {
		// int cost1= abs((c_x-(v[i].x))+(c_y-(v[i].y)));
		// if( cost > cost1) {
			// pos=i;
			// n_x= v[pos].x;
			// n_y= v[pos].y;
		// }
	// }
	//v.erase(v.begin()+pos);
// }

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

int cutup_profit(int a, vector<int> &temp) {
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
			temp.push_back(min);
			int temp1= cutup_profit(min, temp);
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

int cutright_profit(int a, vector<int> &temp) {
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
			temp.push_back(min); 
			int temp1= cutright_profit(min, temp);
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

int cutdown_profit(int a, vector<int> &temp) {
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
			temp.push_back(max);
			int temp1= cutdown_profit(max, temp);
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

int cutleft_profit(int a, vector<int> &temp) {
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
			temp.push_back(max); 
			int temp1= cutleft_profit(max, temp);
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
