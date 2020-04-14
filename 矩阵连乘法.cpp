#include<iostream>
using namespace std;
const int INTMAX = 2147483647;
int const M = 7;
void RecurMatrixChain(int *p, int Length, int m[][M], int s[][M])
{
	int q, n = Length - 1;
	for (int i = 1; i <= n; i++) m[i][i] = 0;
	for (int l = 2; l <= n; l++) 	
	{
		for (int i = 1; i <= n - l + 1; i++)
		{
			int j = i + l - 1;         
			m[i][j] = INTMAX;
			for (int k = i; k <= j - 1; k++)
			{
				q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
				if (q < m[i][j])
				{
					m[i][j] = q;
					s[i][j] = k;
				}
			}
		}
	}
}
void PRINT_OPTIMAL_PARENS(int s[][M], int i, int j)
{
	if (i == j) cout << "A" << i;
	else
	{
		cout << "(";
		PRINT_OPTIMAL_PARENS(s, i, s[i][j]);
		PRINT_OPTIMAL_PARENS(s, s[i][j] + 1, j);
		cout << ")";
	}
}
int main()
{
	int p[M] = { 30,35,15,5,10,20,25 };
	int m[M][M], s[M][M];
	RecurMatrixChain(p, M, m, s);
	cout << "当n=6时最优解为: \n" << m[1][6];
	cout << "\n括号化方案为：\n";
	PRINT_OPTIMAL_PARENS(s, 1, 6);
	return 0;
}