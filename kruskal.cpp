#ifndef __mixspantree__
#define __mixspantree__

#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <memory.h>
#include <stdlib.h>


#define Default_vertex_size 20

#define T char
#define E int
#define MAX_COST 0x7FFFFFFF


typedef struct GraphMtx{
  int MaxVertices;//最大定点数量
  int NumVertices;//实际定点数量
  int NumEdges;//边的数量

  T* VerticesList;//定点列表
  int** Edge;
}GraphMtx;

typedef struct Edge{
  int begin;//边的起点
  int end;  //边的终点
  E   cost; //边的权值
}Edge;

void init_graph(GraphMtx* gm);
//打印二维数组
void show_graph(GraphMtx* gm);
//插入顶点
void insert_vertex(GraphMtx* gm, T v);
//添加顶点间的线
void insert_edge(GraphMtx* gm, T v1, T v2, E cost);
//用kruskal算法构造最小生成树
void minSpanTree_kruskal(GraphMtx* gm);

#endif

void init_graph(GraphMtx* gm){
  gm->MaxVertices = Default_vertex_size;
  gm->NumEdges = gm->NumVertices = 0;

  //开辟顶点内存空间
  gm->VerticesList = (T*)malloc(sizeof(T) * (gm->MaxVertices));
  assert(NULL != gm->VerticesList);

  //创建二维数组
  gm->Edge = (int**)malloc(sizeof(int*) * (gm->MaxVertices));
  assert(NULL != gm->Edge);
  //开辟gm->MaxVertices组，能存放gm->MaxVertices个int的内存空间
  for(int i = 0; i < gm->MaxVertices; ++i){
    gm->Edge[i] = (int*)malloc(sizeof(int) * gm->MaxVertices);
  }

  //初始化二维数组
  for(int i = 0; i < gm->MaxVertices; ++i){
    for(int j = 0; j < gm->MaxVertices; ++j){
      if(i == j)
    gm->Edge[i][j] = 0;
      else
    gm->Edge[i][j] = MAX_COST;
    }
  }
}

//打印二维数组
void show_graph(GraphMtx* gm){
  printf("  ");
  for(int i = 0; i < gm->NumVertices; ++i){
    printf("%c  ", gm->VerticesList[i]);
  }
  printf("\n");
  for(int i = 0; i < gm->NumVertices; ++i){
    printf("%c:", gm->VerticesList[i]);
    for(int j = 0; j < gm->NumVertices; ++j){
      if(gm->Edge[i][j] == MAX_COST){
    printf("%c  ", '*');
      }
      else{
    printf("%d  ", gm->Edge[i][j]);
      }
    }
    printf("\n");
  }
  printf("\n");
}
//插入顶点
void insert_vertex(GraphMtx* gm, T v){
  //顶点空间已满，不能再插入顶点了
  if(gm->NumVertices >= gm->MaxVertices){
    return;
  }
  gm->VerticesList[gm->NumVertices++] = v;
}

int getVertexIndex(GraphMtx* gm, T v){
  for(int i = 0; i < gm->NumVertices; ++i){
    if(gm->VerticesList[i] == v)return i;
  }
  return -1;
}
//添加顶点间的线
void insert_edge(GraphMtx* gm, T v1, T v2, E cost){
  if(v1 == v2)return;
  
  //查找2个顶点的下标
  int j = getVertexIndex(gm, v1);
  int k = getVertexIndex(gm, v2);
  if(j != -1 && k != -1 ){
    //因为是无方向，所以更新2个值
    gm->Edge[j][k] = gm->Edge[k][j] = cost;
    gm->NumEdges++;
  }
}

//比较边的权重
int cmp(const void* a, const void* b){
  return ((*(Edge*)a).cost - (*(Edge*)b).cost);
}
//判断参数的2个顶点的父节点是否相同
bool is_same(int* father, int begin, int end){
  while(father[begin] != begin){
    begin = father[begin];
  }
  while(father[end] != end){
    end = father[end];
  }
  return begin == end;
}
//找到end节点的父节点x，再找到begin节点的父节点y，更新x节点的父节点为y
void mark_same(int* father, int begin, int end){
  while(father[begin] != begin){
    begin = father[begin];
  }
  while(father[end] != end){
    end = father[end];
  }
  father[end] = begin;

}
//用kruskal算法构造最小生成树
void minSpanTree_kruskal(GraphMtx* g){

  int n = g->NumVertices;
  Edge* edge = (Edge*)malloc(sizeof(Edge) * n*(n-1)/2);
  assert(edge != NULL);

  int k = 0;
  //查找一半的矩阵，把各条边的起点，终点，权重，放到edge数组里
  for(int i = 0; i < n; ++i){
    for(int j = i; j < n; j++){
      if(g->Edge[i][j] != 0 && g->Edge[i][j] != MAX_COST){
    edge[k].begin = i;
    edge[k].end = j;
    edge[k].cost = g->Edge[i][j];
    k++;
      }
    }
  }

  //按照权重来排序
  qsort(edge, k, sizeof(Edge), cmp);

  //初始化每个节点的父节点，让每个节点的父节点为自身
  int *father = (int*)malloc(sizeof(int) * n);
  assert(NULL != father);
  for(int i = 0; i < n; ++i){
    father[i] = i;
  }

  for(int i = 0; i < n; ++i){
    //判断2个节点的父节点是否相同
    if(!is_same(father, edge[i].begin, edge[i].end)){
      printf("%c->%c:%d\n",g->VerticesList[edge[i].begin],g->VerticesList[edge[i].end], edge[i].cost);
      //连接后，找到节点end的父节点x，再找到节点begin的父节点y，把节点x的父节点更新为y
      mark_same(father, edge[i].begin, edge[i].end);
    }
  }
}

int main(){
  GraphMtx gm;
  //初始化图
  init_graph(&gm);

  //插入顶点
  insert_vertex(&gm, 'A');
  insert_vertex(&gm, 'B');
  insert_vertex(&gm, 'C');
  insert_vertex(&gm, 'D');
  insert_vertex(&gm, 'E');
  insert_vertex(&gm, 'F');

  //添加连线
  insert_edge(&gm, 'A', 'B', 6);
  insert_edge(&gm, 'A', 'D', 5);
  insert_edge(&gm, 'A', 'C', 1);
  insert_edge(&gm, 'B', 'E', 3);
  insert_edge(&gm, 'B', 'C', 5);
  insert_edge(&gm, 'C', 'E', 6);
  insert_edge(&gm, 'C', 'D', 5);
  insert_edge(&gm, 'C', 'F', 4);
  insert_edge(&gm, 'F', 'E', 6);
  insert_edge(&gm, 'D', 'F', 2);

  //打印图
  show_graph(&gm);

  minSpanTree_kruskal(&gm);

}