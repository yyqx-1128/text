#include <iostream>  
#include <ctime>
#include <cmath>
#include <algorithm>

using namespace std;

#define NO_DISTANCE 1000000

//定义二维点
typedef struct Point
{
	float x, y;     
}Point;

//二维点初始化
void SetPoints(Point *points, int length)
{
	//随机设置
	srand(unsigned(time(NULL))); 
	for (int i = 0; i < length; i++)
	{
		//调整rand(),使得横纵坐标范围为[-100,100]
		points[i].x = (rand() % 20000) / 100.0 - 100;    
		points[i].y = (rand() % 20000) / 100.0 - 100;
	}

}

//两点对距离公式
float Distance(Point a, Point b)
{
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

//依照结构体中的x成员变量升序排序
bool CmpX(Point a, Point b)
{
	return a.x < b.x;
}

//求最近点对
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
		//中位数
		float mid = points[(length - 1) / 2].x;  

		for (i = 0; i < length / 2; i++)
			pts1[i] = points[i];
		for (int j = 0, i = length / 2; i < length; i++)
			pts2[j++] = points[i]; 
		//分治求解左半部分子集的最近点
		d1 = ClosestPair(pts1, length / 2, a1, b1); 
		//分治求解右半部分子集的最近点             
		d2 = ClosestPair(pts2, length - length / 2, a2, b2);    
		if (d1 < d2) { distance = d1; a = a1; b = b1; }
		else { distance = d2; a = a2; b = b2; }

		//求解跨分割线的最近点对
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

	cout << "请您输入二维点对个数：";
	cin >> N;
	if (N < 2)
		cout << "请输入大于等于2的点个数！！" << endl;
	else
	{
		cout << endl << "随机生成的" << N << "个二维点对如下：" << endl;
		Point *points = new Point[N];

		SetPoints(points, N);

		for (int i = 0; i < N; i++)
			cout << "(" << points[i].x << "," << points[i].y << ")" << endl;

		diatance = ClosestPair(points, N, a, b);

		cout << endl << endl << "按横坐标排序后的点对:" << endl;
		for (int i = 0; i < N; i++)
		{
			cout << "(" << points[i].x << "," << points[i].y << ")" << endl;
		}
		cout << endl << "最近点对为：" << "(" << a.x << "," << a.y << ")和" << "(" << b.x << "," << b.y << ")" << endl << "最近点对距离为：" << diatance << endl;
	}
}
