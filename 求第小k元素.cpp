#include <stdio.h>
#define NUM 1001
int a[NUM];

//swap函数 交换x与y的值
void swap(int *x, int *y)
{
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;

}
int select(int left, int right, int k)
{
	if (left >= right) return a[left];
	int i = left;      
	int j = right + 1;   
	int pivot = a[left];//最左边元素为分界数
	while (true)
	{  
		do {
			i = i + 1;
		} while (a[i] < pivot);
		do {
			j = j - 1;
		} while (a[j] > pivot);
		if (i >= j) break;   
		swap(&a[i], &a[j]);
	}
	if (j - left + 1 == k) return pivot;
	a[left] = a[j];                       
	a[j] = pivot;                       
	if (j - left + 1 < k)
		return select(j + 1, right, k - j + left - 1);
	else return select(left, j - 1, k);      
}

int main()
{
	int n, k;
	while (scanf_s("%d%d", &n, &k))
	{
		for (int i = 0; i < n; i++)
			scanf_s("%d", &a[i]);
		printf("%d", select(0, n - 1, k));
	}
	return 0;
}
