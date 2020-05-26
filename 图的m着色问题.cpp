#include <fstream>  
#include <iostream>  
#include <stdlib.h>  
#include <algorithm>  
using namespace std;

int map[10][10];//�ڽӾ���  

typedef struct Node{ //����ڵ�ṹ��  
   int index; //���  
   int degree; //��  
   int color; //�Ľڵ����ɫ  
} Node;

Node nodes[10];

bool com(Node node1, Node node2) { //���ȴӸߵ�������  
	return node1.degree > node2.degree;
}

bool com2(Node node1, Node node2) { //���ȴӸߵ�������  
	return node1.index < node2.index;
}

int main() {
	ifstream read;
	read.open("map.data");//map.data�Ǵ�����ݵ��ļ���  
	int m, n;
	while (read >> m >> n) {
		for (int i = 0; i < m; i++) {//��������  
			int degree = 0;
			for (int j = 0; j < n; j++) {
				read >> map[i][j];
				if (map[i][j])
					degree++;
			}
			nodes[i].index = i;
			nodes[i].degree = degree;
			nodes[i].color = 0;
		}

		//����  
		sort(nodes, nodes + m, com);
		int k = 0;//K ����ڼ�����ɫ  
		while (true) {
			k++;
			int i;
			for (i = 0; i < m; i++) {//���ҵ���һ��δ��ɫ�Ľڵ�  
				if (nodes[i].color == 0) {
					nodes[i].color = k;
					break;
				}
			}
			if (i == m)//ѭ���˳�������,���нڵ㶼����ɫ  
				break;
			//�ٰ����в��͸ýڵ����ڵĽڵ�����ͬ����ɫ  
			for (int j = 0; j < m; j++) {
				if (nodes[j].color == 0 && map[nodes[i].index][nodes[j].index] == 0
					&& i != j)
					nodes[j].color = k;
			}
		}

		//��������  
		sort(nodes, nodes + m, com2);
		cout << "����Ҫ" << k - 1 << "����ɫ" << endl;
		for (int i = 0; i < m; i++)
			cout << "�ڵ㣺" << nodes[i].index << ":��ɫ" << nodes[i].color << endl;
		return 0;
	}
}