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
     return 0;//�����ҵ������������У����0
 }
 int main(){
     int n,i,j,a[1000],x;
     while(cin>>n){//���������С
         for(i=0;i<n;i++)cin>>a[i];//��������,��Ҫ��С����
         cin>>x;//�����������
         cout<<"�±�Ϊ: "<<BinarySearch(a,n,x)<<"\n\n";//����±�
     }return 0;
 }