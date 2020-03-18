# include<iostream>
using namespace std;

void Merge(int [], int, int, int, int []);
// �鲢���򻮷ֹ���
void MergeSort(int a[], int left, int right, int temp[])
{
    if(left < right)
    {
        int mid = (left + right) >> 1;
        MergeSort(a,left,mid,temp);
        MergeSort(a,mid+1,right,temp);
        Merge(a,left,mid,right,temp);
    }
}

// �鲢����ϲ�����
void Merge(int a[], int left, int mid, int right, int temp[])
{
    int p0 = 0;
    int p1 = left, p2 = mid + 1;
    while(p1<=mid && p2<=right)
    {
        if(a[p1] < a[p2])
            temp[p0++] = a[p1++];
        else
            temp[p0++] = a[p2++];
    }
    while(p1<=mid)
        temp[p0++] = a[p1++];
    while(p2<=right)
        temp[p0++] = a[p2++];
    for(int i=0; i<right-left+1;++i)
        a[left+i] = temp[i];
}
int main()
{
    int array [] = {55,2,6,4,32,12,9,73,26,37};
    int len = sizeof(array) / sizeof(int);
    cout<<"�����ԭʼ����:  ";
    for(int i=0; i<len; i++) 
        cout<<array[i]<<",";
    cout<<endl<<endl;

    cout<<"  ----��������---- " << endl;
    int *temp = new int [len];
    MergeSort(array,0,len-1,temp); 
    for(int j=0; j<len; j++)
        cout<<array[j]<<",";
    return 0;
}

