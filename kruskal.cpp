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
  int MaxVertices;//��󶨵�����
  int NumVertices;//ʵ�ʶ�������
  int NumEdges;//�ߵ�����

  T* VerticesList;//�����б�
  int** Edge;
}GraphMtx;

typedef struct Edge{
  int begin;//�ߵ����
  int end;  //�ߵ��յ�
  E   cost; //�ߵ�Ȩֵ
}Edge;

void init_graph(GraphMtx* gm);
//��ӡ��ά����
void show_graph(GraphMtx* gm);
//���붥��
void insert_vertex(GraphMtx* gm, T v);
//��Ӷ�������
void insert_edge(GraphMtx* gm, T v1, T v2, E cost);
//��kruskal�㷨������С������
void minSpanTree_kruskal(GraphMtx* gm);

#endif

void init_graph(GraphMtx* gm){
  gm->MaxVertices = Default_vertex_size;
  gm->NumEdges = gm->NumVertices = 0;

  //���ٶ����ڴ�ռ�
  gm->VerticesList = (T*)malloc(sizeof(T) * (gm->MaxVertices));
  assert(NULL != gm->VerticesList);

  //������ά����
  gm->Edge = (int**)malloc(sizeof(int*) * (gm->MaxVertices));
  assert(NULL != gm->Edge);
  //����gm->MaxVertices�飬�ܴ��gm->MaxVertices��int���ڴ�ռ�
  for(int i = 0; i < gm->MaxVertices; ++i){
    gm->Edge[i] = (int*)malloc(sizeof(int) * gm->MaxVertices);
  }

  //��ʼ����ά����
  for(int i = 0; i < gm->MaxVertices; ++i){
    for(int j = 0; j < gm->MaxVertices; ++j){
      if(i == j)
    gm->Edge[i][j] = 0;
      else
    gm->Edge[i][j] = MAX_COST;
    }
  }
}

//��ӡ��ά����
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
//���붥��
void insert_vertex(GraphMtx* gm, T v){
  //����ռ������������ٲ��붥����
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
//��Ӷ�������
void insert_edge(GraphMtx* gm, T v1, T v2, E cost){
  if(v1 == v2)return;
  
  //����2��������±�
  int j = getVertexIndex(gm, v1);
  int k = getVertexIndex(gm, v2);
  if(j != -1 && k != -1 ){
    //��Ϊ���޷������Ը���2��ֵ
    gm->Edge[j][k] = gm->Edge[k][j] = cost;
    gm->NumEdges++;
  }
}

//�Ƚϱߵ�Ȩ��
int cmp(const void* a, const void* b){
  return ((*(Edge*)a).cost - (*(Edge*)b).cost);
}
//�жϲ�����2������ĸ��ڵ��Ƿ���ͬ
bool is_same(int* father, int begin, int end){
  while(father[begin] != begin){
    begin = father[begin];
  }
  while(father[end] != end){
    end = father[end];
  }
  return begin == end;
}
//�ҵ�end�ڵ�ĸ��ڵ�x�����ҵ�begin�ڵ�ĸ��ڵ�y������x�ڵ�ĸ��ڵ�Ϊy
void mark_same(int* father, int begin, int end){
  while(father[begin] != begin){
    begin = father[begin];
  }
  while(father[end] != end){
    end = father[end];
  }
  father[end] = begin;

}
//��kruskal�㷨������С������
void minSpanTree_kruskal(GraphMtx* g){

  int n = g->NumVertices;
  Edge* edge = (Edge*)malloc(sizeof(Edge) * n*(n-1)/2);
  assert(edge != NULL);

  int k = 0;
  //����һ��ľ��󣬰Ѹ����ߵ���㣬�յ㣬Ȩ�أ��ŵ�edge������
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

  //����Ȩ��������
  qsort(edge, k, sizeof(Edge), cmp);

  //��ʼ��ÿ���ڵ�ĸ��ڵ㣬��ÿ���ڵ�ĸ��ڵ�Ϊ����
  int *father = (int*)malloc(sizeof(int) * n);
  assert(NULL != father);
  for(int i = 0; i < n; ++i){
    father[i] = i;
  }

  for(int i = 0; i < n; ++i){
    //�ж�2���ڵ�ĸ��ڵ��Ƿ���ͬ
    if(!is_same(father, edge[i].begin, edge[i].end)){
      printf("%c->%c:%d\n",g->VerticesList[edge[i].begin],g->VerticesList[edge[i].end], edge[i].cost);
      //���Ӻ��ҵ��ڵ�end�ĸ��ڵ�x�����ҵ��ڵ�begin�ĸ��ڵ�y���ѽڵ�x�ĸ��ڵ����Ϊy
      mark_same(father, edge[i].begin, edge[i].end);
    }
  }
}

int main(){
  GraphMtx gm;
  //��ʼ��ͼ
  init_graph(&gm);

  //���붥��
  insert_vertex(&gm, 'A');
  insert_vertex(&gm, 'B');
  insert_vertex(&gm, 'C');
  insert_vertex(&gm, 'D');
  insert_vertex(&gm, 'E');
  insert_vertex(&gm, 'F');

  //�������
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

  //��ӡͼ
  show_graph(&gm);

  minSpanTree_kruskal(&gm);

}