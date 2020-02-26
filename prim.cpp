
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define INFINITE 0xFFFFFFFF   
#define VertexData unsigned int  //��������
#define UINT  unsigned int
#define vexCounts 6  //��������
char vextex[] = { 'A', 'B', 'C', 'D', 'E', 'F' };
struct node 
{
    VertexData data;                              
    unsigned int lowestcost;                      //��С����
}closedge[vexCounts];                             //Prim�㷨�еĸ�����Ϣ
 
void AdjMatrix(unsigned int adjMat[][vexCounts])  //�ڽӾ����ʾ��
{
    for (int i = 0; i < vexCounts; i++)           //��ʼ���ڽӾ���
        for (int j = 0; j < vexCounts; j++)
        {
            adjMat[i][j] = INFINITE;
        }
    adjMat[0][1] = 6; adjMat[0][2] = 1; adjMat[0][3] = 5;
    adjMat[1][0] = 6; adjMat[1][2] = 5; adjMat[1][4] = 3;
    adjMat[2][0] = 1; adjMat[2][1] = 5; adjMat[2][3] = 5; adjMat[2][4] = 6; adjMat[2][5] = 4;
    adjMat[3][0] = 5; adjMat[3][2] = 5; adjMat[3][5] = 2;
    adjMat[4][1] = 3; adjMat[4][2] = 6; adjMat[4][5] = 6;
    adjMat[5][2] = 4; adjMat[5][3] = 2; adjMat[5][4] = 6;
}
int Minmum(struct node * closedge)  //������С���۱�
{
    unsigned int min = INFINITE;
    int index = -1;
    for (int i = 0; i < vexCounts;i++)
    {
        if (closedge[i].lowestcost < min && closedge[i].lowestcost !=0)
        {
            min = closedge[i].lowestcost;
            index = i;
        }
    }
    return index;
}
int MiniSpanTree_Prim(unsigned int adjMat[][vexCounts], VertexData s)										                                 
{                                                   
	int sum =0;                                      //��Ȩֵ��
    for (int i = 0; i < vexCounts;i++)
    {
        closedge[i].lowestcost = INFINITE;
    }      
    closedge[s].data = s;                            //�Ӷ���s��ʼ
    closedge[s].lowestcost = 0;						 
    for (int i = 0; i < vexCounts;i++)               //��ʼ����������
    {
        if (i != s)
        {
            closedge[i].data = s;
            closedge[i].lowestcost = adjMat[s][i];
        }
    }
    for (int e = 1; e <= vexCounts -1; e++)          //n-1����ʱ�˳�
    {
        int k = Minmum(closedge);                    //ѡ����С���۱�
        sum += closedge[k].lowestcost;
        cout << vextex[closedge[k].data] << "--" << vextex[k] << endl;//���뵽��С������
        closedge[k].lowestcost = 0;                  //������Ϊ0
        for (int i = 0; i < vexCounts;i++)           //����v�ж�����С���۱���Ϣ
        {
            if ( adjMat[k][i] < closedge[i].lowestcost)
            {
                closedge[i].data = k;
                closedge[i].lowestcost = adjMat[k][i];
            }
        }
    }
    return sum;
}
 
 
int main()
{
    unsigned int  adjMat[vexCounts][vexCounts] = { 0 };
    AdjMatrix(adjMat);                              //�ڽӾ���
    cout << "Prim :" << endl;
    int sum = MiniSpanTree_Prim(adjMat,0);          //Prim�㷨���Ӷ���0��ʼ.
    cout<<sum<<endl;
    return 0;
}
