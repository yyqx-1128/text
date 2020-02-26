
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define INFINITE 0xFFFFFFFF   
#define VertexData unsigned int  //顶点数据
#define UINT  unsigned int
#define vexCounts 6  //顶点数量
char vextex[] = { 'A', 'B', 'C', 'D', 'E', 'F' };
struct node 
{
    VertexData data;                              
    unsigned int lowestcost;                      //最小代价
}closedge[vexCounts];                             //Prim算法中的辅助信息
 
void AdjMatrix(unsigned int adjMat[][vexCounts])  //邻接矩阵表示法
{
    for (int i = 0; i < vexCounts; i++)           //初始化邻接矩阵
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
int Minmum(struct node * closedge)  //返回最小代价边
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
	int sum =0;                                      //求权值和
    for (int i = 0; i < vexCounts;i++)
    {
        closedge[i].lowestcost = INFINITE;
    }      
    closedge[s].data = s;                            //从顶点s开始
    closedge[s].lowestcost = 0;						 
    for (int i = 0; i < vexCounts;i++)               //初始化辅助数组
    {
        if (i != s)
        {
            closedge[i].data = s;
            closedge[i].lowestcost = adjMat[s][i];
        }
    }
    for (int e = 1; e <= vexCounts -1; e++)          //n-1条边时退出
    {
        int k = Minmum(closedge);                    //选择最小代价边
        sum += closedge[k].lowestcost;
        cout << vextex[closedge[k].data] << "--" << vextex[k] << endl;//加入到最小生成树
        closedge[k].lowestcost = 0;                  //代价置为0
        for (int i = 0; i < vexCounts;i++)           //更新v中顶点最小代价边信息
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
    AdjMatrix(adjMat);                              //邻接矩阵
    cout << "Prim :" << endl;
    int sum = MiniSpanTree_Prim(adjMat,0);          //Prim算法，从顶点0开始.
    cout<<sum<<endl;
    return 0;
}
