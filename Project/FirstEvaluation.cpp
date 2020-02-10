#include <bits/stdc++.h>
using namespace std;
int t;
struct lumber
{
    int x,y,h,d,c,p;
    int price,weight;
};
void path(int x1,int y1,int x2,int y2){
    int i;
    if(x2>x1){
    for(i=1;i<=x2-x1;i++){
            if(t>0){
        cout<<"move right\n";
        t--;
        }}
    }
    else{
            for(i=1;i<=x1-x2;i++){
                if(t>0){
            cout<<"move left\n";
            t--;
            }}
    }
    if(y2>y1){
    for(i=1;i<=y2-y1;i++){
            if(t>0){
        cout<<"move up\n";
        t--;
    }}
    }
    else{
            for(i=1;i<=y1-y2;i++){
                    if(t>0){
            cout<<"move down\n";
            t--;
            }}
    }
    }
int main()
{
    int n,k;
    int i,j,m,pos,c=0,ox=0,oy=0,total=0;
    cin>>t>>n>>k;
    lumber a[k];
    for(i=0;i<k;i++){
        cin>>a[i].x>>a[i].y>>a[i].h>>a[i].d>>a[i].c>>a[i].p;
            a[i].price=a[i].p*a[i].h*a[i].d;
            a[i].weight=a[i].c*a[i].d*a[i].h;
    }
    m=abs(a[0].x-ox)+abs(a[0].y-oy);
    pos=0;
    for(i=0;i<k;i++){
            if((abs(a[i].x-ox)+abs(a[i].y-oy))<m){
            m=abs(a[i].x-ox)+abs(a[i].y-oy);
            pos=i;
            }
    }
    if(a[pos].x+a[pos].y+a[pos].d<=t){
        path(ox,oy,a[pos].x,a[pos].y);
        cout<<"cut up";
        total=total+a[pos].price;
    }
    return 0;
}
