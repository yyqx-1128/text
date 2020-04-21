#include <stdio.h>

void LSCLength(char a[], char b[], int c[11][10], int lsc[11][10], int la, int lb)
{
	for (int i = 0; i <= la; i++)	lsc[0][i] = 0;
	for (int i = 0; i <= lb; i++)	lsc[i][0] = 0;
	for (int i = 1; i <= la; i++)
	{
		for (int j = 1; j <= lb; j++) {
			if (a[i - 1] == b[j - 1])
			{
				lsc[i][j] = lsc[i - 1][j - 1] + 1;
				c[i][j] = 1;
			}
			else if (lsc[i - 1][j] >= lsc[i][j - 1])
			{
				lsc[i][j] = lsc[i - 1][j];
				c[i][j] = 2;
			}
			else {
				lsc[i][j] = lsc[i][j - 1];
				c[i][j] = 3;
			}
		}
	}


}
void LSC(int i, int j, char a[], int c[11][10])
{
	if (i == 0 || j == 0)	return;
	if (c[i][j] == 1)
	{
		LSC(i - 1, j - 1, a, c);
		printf("%3c  ", a[i - 1]);
	}
	else if (c[i][j] == 2)
	{
		LSC(i - 1, j, a, c);
	}
	else
	{
		LSC(i, j - 1, a, c);
	}

}
int main(int argc, char** argv) {
	char a[10] = { 'A','B','C','A','C','D','B','C','A','B' };
	char b[9] = { 'A','D','C','A','B','C','D','A','B' };
	int c[11][10] = { 0 };
	int lsc[11][10] = { 0 };
	LSCLength(a, b, c, lsc, 10, 9);
	for (int i = 0; i <= 10; i++)
	{
		for (int j = 0; j <= 9; j++)
		{
			printf("%d  ", lsc[i][j]);
		}
		printf("\n");
	}
	printf("³¤¶È£º%d\n", lsc[10][9]);
	return 0;
}
