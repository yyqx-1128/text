 
#include<stdio.h>
#include<stdlib.h>
#define MaxVertexNum 100
#define INFINITY  65535
typedef int Vertex;
typedef int WeightType;
typedef char DataType;

//图的数据结构 
typedef struct GNode * PtrToGNode;
struct GNode{
	int Nv;
	int Ne;
	WeightType G[MaxVertexNum][MaxVertexNum];
	DataType Data[MaxVertexNum]; 
};
typedef PtrToGNode MGraph;
 
typedef struct ENode * PtrToENode;
struct ENode{
	Vertex V1,V2;
	WeightType Weight;
};
typedef PtrToENode Edge;
//队列的数据结构 
typedef int ElementType;
typedef struct QNode * PtrToQNode;
struct QNode{
	int * Data;
	int Front,Rear;
	int MaxSize;
}; 
typedef PtrToQNode Queue;
 
bool Visited[]={false};
 
//创建队列
Queue CreateQueue(int MaxSize){
	Queue Q = (Queue)malloc (sizeof(struct QNode));
	Q->Data=(ElementType *)malloc(MaxSize * sizeof(ElementType));
	Q->Front=Q->Rear=0;
	Q->MaxSize=MaxSize;
	return Q; 
} 
 
//入队
bool IsFull(Queue Q){
	return ((Q->Rear+1) % Q->MaxSize == Q->Front);
} 
 
bool AddQ(Queue Q,int X){
	if(IsFull(Q)){
		printf("队列满\n");
	}else{
		Q->Rear=(Q->Rear+1) % Q->MaxSize;
		Q->Data[Q->Rear] = X;
		return true;
	}
}
 
bool IsEmpty(Queue Q){
	return (Q->Front==Q->Rear);
} 
 
#define ERROR -1
int DeleteQ(Queue Q){
	if(IsEmpty(Q)){
		printf("队列空\n");
		return ERROR;
	}else{
		Q->Front=(Q->Front+1) % Q->MaxSize;
		return Q->Data[Q->Front];
	}
}
 
MGraph CreateGraph(int VertexNum){
	Vertex V,W;
	MGraph Graph;
	
	Graph=(MGraph)malloc(sizeof(struct GNode));
	Graph->Nv=VertexNum;
	Graph->Ne=0;
	for(V=0;V<Graph->Nv;V++)
		for(W=0;W<Graph->Nv;W++)
			Graph->G[V][W]=INFINITY;
	return Graph;
}
 
void InsertEdge(MGraph Graph,Edge E){
	Graph->G[E->V1][E->V2]=E->Weight;
	Graph->G[E->V2][E->V1]=E->Weight;
}
 
MGraph BuildGraph(){
	MGraph Graph;
	Edge E;
	Vertex V;
	int Nv,i;
	
	printf("请输入顶点个数: "); 
	scanf("%d",&Nv);
	Graph=CreateGraph(Nv);
	
	printf("请输入边的个数: "); 
	scanf("%d",&(Graph->Ne));
	if(Graph->Ne!=0){
		E=(Edge)malloc(sizeof(struct ENode));
		for(i=0;i<Graph->Ne;i++){ 
			printf("读入边，格式为起点 终点 权重。请输入: "); 
			scanf("%d %d %d",&E->V1,&E->V2,&E->Weight);
			InsertEdge(Graph,E);
		}
	}
	return Graph;
}

Vertex FindMinDist(MGraph Graph,int dist[],int collected[]){
	Vertex MinV,V;
	int MinDist=INFINITY;
	
	for(V=0;V<Graph->Nv;V++) {
		if(collected[V]==false&&dist[V]<MinDist){
			MinDist=dist[V];
			MinV=V;
		}
	}
	if(MinDist<INFINITY)
		return MinV;
	else return ERROR;
}
 
bool Floyd(MGraph Graph,WeightType D[][MaxVertexNum],Vertex path[][MaxVertexNum]){
	Vertex i,j,k;
	
	for(i=0;i<Graph->Nv;i++)
		for(j=0;j<Graph->Nv;j++){
			D[i][j]=Graph->G[i][j];
			path[i][j]=-1;
		} 
		
	for(k=0;k<Graph->Nv;k++)
		for(i=0;i<Graph->Nv;i++)
			for(j=0;j<Graph->Nv;j++)
				if(D[i][k]+D[k][j]<D[i][j]){
					D[i][j]=D[i][k]+D[k][j];
					if(i==j&&D[i][j]<0)
						return false;
					path[i][j]=k;
				}
	return true;
}
 
int main(){
	MGraph graph= BuildGraph();
	int D[30][MaxVertexNum],path[30][MaxVertexNum];
	int z,i,j;
	Floyd(graph,D,path);
	for(i=0;i<graph->Nv-1;i++)
		for(j=i+1;j<graph->Nv;j++)
			printf("顶点%d到顶点%d之间的最小距离为:%d \n",i,j,D [i][j]);
	return 0;
}
