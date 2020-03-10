#include<iostream>
using namespace std;

 int BinarySearch(int *a,int n,int x){
     int left=0;
     int right=n-1;
     while(left<=right){
         int mid=(left+right)/2;
         if(x==a[mid]) return mid;
         if(x>a[mid])
             left=mid+1;
         else
             right=mid-1;
     }
     return 0;//若查找的数不在数组中，输出0
 }
 int main(){
     int n,i,j,a[1000],x;
     while(cin>>n){//输入数组大小
         for(i=0;i<n;i++)cin>>a[i];//输入数据,需要从小到大
         cin>>x;//输入待查数据
         cout<<"下标为: "<<BinarySearch(a,n,x)<<"\n\n";//输出下标
     }return 0;
 }