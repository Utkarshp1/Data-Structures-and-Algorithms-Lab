#include<iostream>

using namespace std;

struct gcd {
	int d;
	int x;
	int y;
};

gcd extended_euclid(int a, int b);

int main(int argc, char* argv[]) {
	if (argc == 3) {
		int a= atoi(argv[1]);
		int b= atoi(argv[2]);
		gcd result= extended_euclid(a,b);
		cout << result.d << " " << result.x << " " << result.y << endl;
	}	
	else {
		cout << "Please enter two numbers" << endl;
	}
	
	return 0;
}

gcd extended_euclid(int a, int b) {
	if (b==0) {
		gcd another;
		another.d = a;
		another.x = 1;
		another.y = 0;
		return another;
	}
	else {
		gcd result1= extended_euclid(b, a%b);
		gcd another;
		another.d= result1.d;
		another.x= result1.y;
		int c= a/b;
		another.y= result1.x - (c*(result1.y));
		return another;
	}
}