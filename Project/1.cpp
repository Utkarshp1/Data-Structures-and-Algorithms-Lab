#include<iostream>
#include<vector>
#include<cstdlib>

using namespace std;

struct lumber {
	int x, y, h, d, c, p;
	int price, weight, profit, direc;
	string color;
	vector<int> track; 
};

int path();
int path1();
void calculate_profit(); 
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
		v[i].color= "white";
	}
	calculate_profit(); 
	while (t>0) {
			int i;
			if (v.size() != 793) {
				i = path();
			}
			else {
				i = path1(); 
			}
			if (v[i].color == "white") {
				vector<int> temp;
				n_x= v[i].x;
				n_y= v[i].y;
				printPath();
				if (v[i].direc == 0 && t>0) {
					cout << "cut up" << endl;
					int temp1= cutup_profit(i, temp); 
				}
				if (v[i].direc == 1 && t>0) {
					cout << "cut right" << endl;
					int temp1= cutright_profit(i, temp);
				}
				if (v[i].direc == 2 && t>0) {
					cout << "cut down" << endl;
					int temp1= cutdown_profit(i, temp);
				}
				if (v[i].direc == 3 && t>0) {
					cout << "cut left" << endl;
					int temp1= cutleft_profit(i, temp);
				}
				t= t- v[i].d;
				for (int j=0; j<temp.size(); j++) {
					v[temp[j]].color= "black";
				}
				v[i].color = "black";
				c_x = n_x;
				c_y = n_y;
				for (int j=0; j<v[i].track.size(); j++) {
					for (int k=0; k<v.size(); k++) {
						for (int l=0; l< v[k].track.size(); l++) {
							if (v[k].track[l] == v[i].track[j]) {
								v[k].profit=- v[v[i].track[j]].price;
							}
						}
					}
				}
			}
			else {
				break;
			}
	}
	return 0;
}

void calculate_profit() {
	for (int i=0; i<v.size(); i++) {
		int cost= abs(v[i].x-c_x) + abs(v[i].y-c_y) + v[i].d;
		//if (cost <= t) {
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
			//if (v[i].y >= v[i].h) {
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
			//}
			
			//if (v[i].x >= v[i].h) {
				leftProfit= cutleft_profit(i, temp);
				if (leftProfit > dprofit) {
					dprofit= leftProfit;
					track.clear();
					track= temp;
					v[i].direc=3; 
				}
				v[i].profit += dprofit;
				v[i].track= track;
			//}
			// for (int j=0; j< v[i].trackx.size(); j++) {
				// cout << i << " " << v[i].trackx[j] << " " << v[i].tracky[j] << endl;
			// }
	//}
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

int cutup_profit(int a, vector<int> &temp) {
	int profit=0; 
	int min=-1;
	int i; 
	for (i=0; i<v.size(); i++) {
		if (v[i].x == v[a].x && v[i].y > v[a].y && v[i].color == "white") {
			min = i;
			break;
		}
	}
	for (int j=i+1; j<v.size(); j++) {
		if (v[j].x == v[a].x && v[j].y > v[a].y && v[j].y < v[min].y && v[j].color == "white") {
			min = j;
		}
	}
	//cout << min << endl;
	if (min >0) {
		if (v[a].weight > v[min].weight && v[a].h > v[min].y-v[a].y && v[min].color == "white") {
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
		if (v[i].y == v[a].y && v[i].x > v[a].x && v[i].color == "white") {
			min = i;
			break;
		}
	}
	//cout << min << endl;
	for (int j=i+1; j<v.size(); j++) {
		//cout << v[i].x <<" " << v[a].x << " " << v[j].x << " " << v[min].x << endl;  
		if (v[j].y == v[a].y && v[j].x > v[a].x && v[j].x < v[min].x && v[j].color == "white") {
			min = j;
		}
	}
	//cout << min << endl;
	if (min >0) {
		//cout << v[a].weight << " " << v[min].weight << " " << v[a].h << " " << v[min].x-v[a].x << endl;
		if (v[a].weight > v[min].weight && v[a].h > v[min].x-v[a].x && v[min].color == "white") {
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
		if (v[i].x == v[a].x && v[i].y < v[a].y && v[i].color == "white") {
			max = i;
			break;
		}
	}
	for (int j=i+1; j<v.size(); j++) {
		if (v[j].x == v[a].x && v[j].y < v[a].y && v[j].y > v[max].y && v[j].color == "white") {
			max = j;
		}
	}
	if (max >0) {
		if (v[a].weight > v[max].weight && v[a].h > v[a].y-v[max].y && v[max].color == "white") {
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
		if (v[i].y == v[a].y && v[i].x < v[a].x && v[i].color == "white") {
			max = i;
			break;
		}
	}
	for (int j=i+1; j<v.size(); j++) {
		//cout << v[i].x <<" " << v[a].x << " " << v[j].x << " " << v[min].x << endl;  
		if (v[j].y == v[a].y && v[j].x < v[a].x && v[j].x > v[max].x && v[j].color == "white") {
			max = j;
		}
	}
	//cout << max << endl;
	if (max >0) {
		//cout << v[a].weight << " " << v[min].weight << " " << v[a].h << " " << v[min].x-v[a].x << endl;
		if (v[a].weight > v[max].weight && v[a].h > v[a].x-v[max].x && v[max].color == "white") {
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

int path() {
	float max_para=0;
	int n_i=0;
	for (int i=0; i<v.size(); i++) {
		int cost= abs(v[i].x-c_x) + abs(v[i].y-c_y) + v[i].d;
		if (cost <= t && v[i].color == "white") {
			//cost = cost * cost;
			float para= (float)v[i].profit/cost; 
			para= para + 2/para;
			if (max_para < para) {
				max_para = para;
				n_i= i; 
			}
		}
	}
	return n_i; 
}

int path1() {
	float max_para=0;
	int n_i=0;
	for (int i=0; i<v.size(); i++) {
		int cost= abs(v[i].x-c_x) + abs(v[i].y-c_y) + v[i].d;
		if (cost <= t && v[i].color == "white") {
			//cost = cost * cost;
			float para= (float)v[i].price/cost;  
			if (max_para < para) {
				max_para = para;
				n_i= i; 
			}
		}
	}
	return n_i; 
}