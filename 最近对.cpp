#include <iostream>  
#include <ctime>
#include <cmath>
#include <algorithm>

using namespace std;

#define NO_DISTANCE 1000000

//�����ά��
typedef struct Point
{
	float x, y;     
}Point;

//��ά���ʼ��
void SetPoints(Point *points, int length)
{
	//�������
	srand(unsigned(time(NULL))); 
	for (int i = 0; i < length; i++)
	{
		//����rand(),ʹ�ú������귶ΧΪ[-100,100]
		points[i].x = (rand() % 20000) / 100.0 - 100;    
		points[i].y = (rand() % 20000) / 100.0 - 100;
	}

}

//����Ծ��빫ʽ
float Distance(Point a, Point b)
{
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

//���սṹ���е�x��Ա������������
bool CmpX(Point a, Point b)
{
	return a.x < b.x;
}

//��������
float ClosestPair(Point points[], int length, Point &a, Point &b)
{
	float distance;        
	float d1, d2;           
	int i = 0, j = 0, k = 0;       
	Point a1, b1, a2, b2;     

	if (length < 2)return NO_DISTANCE;    
	if (length == 2)
	{
		a = points[0];
		b = points[1];
		distance = Distance(points[0], points[1]);
	}
	else
	{
		Point *pts1 = new Point[length];     
		Point *pts2 = new Point[length];

		sort(points, points + length, CmpX);   
		//��λ��
		float mid = points[(length - 1) / 2].x;  

		for (i = 0; i < length / 2; i++)
			pts1[i] = points[i];
		for (int j = 0, i = length / 2; i < length; i++)
			pts2[j++] = points[i]; 
		//���������벿���Ӽ��������
		d1 = ClosestPair(pts1, length / 2, a1, b1); 
		//��������Ұ벿���Ӽ��������             
		d2 = ClosestPair(pts2, length - length / 2, a2, b2);    
		if (d1 < d2) { distance = d1; a = a1; b = b1; }
		else { distance = d2; a = a2; b = b2; }

		//����ָ��ߵ�������
		Point *pts3 = new Point[length];
		for (i = 0, k = 0; i < length; i++)
			if (abs(points[i].x - mid) <= distance)pts3[k++] = points[i];

		for (i = 0; i < k; i++)
			for (j = i + 1; j <= i + 7 && j < k; j++)    
			{
				if (Distance(pts3[i], pts3[j]) < distance)
				{
					distance = Distance(pts3[i], pts3[j]);
					a = pts3[i];
					b = pts3[j];
				}
			}
	}
	return distance;
}

int main()
{
	int N;      
	Point a, b;
	float diatance;

	cout << "���������ά��Ը�����";
	cin >> N;
	if (N < 2)
		cout << "��������ڵ���2�ĵ��������" << endl;
	else
	{
		cout << endl << "������ɵ�" << N << "����ά������£�" << endl;
		Point *points = new Point[N];

		SetPoints(points, N);

		for (int i = 0; i < N; i++)
			cout << "(" << points[i].x << "," << points[i].y << ")" << endl;

		diatance = ClosestPair(points, N, a, b);

		cout << endl << endl << "�������������ĵ��:" << endl;
		for (int i = 0; i < N; i++)
		{
			cout << "(" << points[i].x << "," << points[i].y << ")" << endl;
		}
		cout << endl << "������Ϊ��" << "(" << a.x << "," << a.y << ")��" << "(" << b.x << "," << b.y << ")" << endl << "�����Ծ���Ϊ��" << diatance << endl;
	}
}
