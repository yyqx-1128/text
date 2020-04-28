#include <iostream>     
#include <algorithm>  
using namespace std;

#define N 3  
#define C 5 

int main()
{
	int value[N + 1] = { 0, 60, 100, 120 }; 
	int weight[N + 1] = { 0, 1, 2, 3 };       
	int f[N + 1][C + 1] = { 0 };       

	int i = 1;
	int j = 1;
	for (i = 1; i <= N; i++)        
	{
		for (j = 1; j <= C; j++)
		{

			if (j < weight[i])
			{
				f[i][j] = f[i - 1][j];
			}
			else
			{
				int x = f[i - 1][j];
				int y = f[i - 1][j - weight[i]] + value[i];
				f[i][j] = max(x, y);
			}
		}
	}

	for (i = 0; i <= N; i++)
	{
		for (j = 0; j <= C; j++)
		{
			printf("%4d ", f[i][j]);
		}

		cout << endl;
	}

	cout << endl << "选取的最大价值是：" << f[N][C] << endl;
	cout << "选取的物品如下：" << endl;
	i = N, j = C;
	while (i)
	{
		if (f[i][j] == (f[i - 1][j - weight[i]] + value[i]))
		{
			cout << i << ":" << "weight=" << weight[i] << ", value=" << value[i] << endl;
			j -= weight[i];
		}
		i--;
	}
	cout << endl;
	return 0;
}