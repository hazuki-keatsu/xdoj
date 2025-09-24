#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	int point;
	int coeffi;
} SINGLE;

void memory(SINGLE *sum, int point, int coeffi);
void sort(SINGLE *sum);

int k = 0;

int main()
{
	int n, m, t;
	scanf("%d %d %d", &n, &m, &t);

	SINGLE *multi1 = (SINGLE *)malloc(n * sizeof(SINGLE));
	SINGLE *multi2 = (SINGLE *)malloc(m * sizeof(SINGLE));
	SINGLE *sum = (SINGLE *)malloc((m + n + 1) * sizeof(SINGLE));
	memset(sum, 0, (m + n + 1) * sizeof(SINGLE));

	for (int i = 0; i < n; i++)
	{
		scanf("%d %d", &multi1[i].coeffi, &multi1[i].point);
	}
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d", &multi2[i].coeffi, &multi2[i].point);
	}

	if (t == 0)
	{
		for (int i = 0; i < n; i++)
		{
			int flag = 0;
			for (int j = 0; j < k; j++)
			{
				if (sum[j].point == multi1[i].point)
				{
					sum[j].coeffi += multi1[i].coeffi;
					flag = 1;
					break;
				}
			}
			if (flag == 0)
			{
				memory(sum, multi1[i].point, multi1[i].coeffi);
			}
		}

		for (int i = 0; i < m; i++)
		{
			int flag = 0;
			for (int j = 0; j < k; j++)
			{
				if (sum[j].point == multi2[i].point)
				{
					sum[j].coeffi += multi2[i].coeffi;
					flag = 1;
					break;
				}
			}
			if (flag == 0)
			{
				memory(sum, multi2[i].point, multi2[i].coeffi);
			}
		}
	}
	else 
	{
		for (int i = 0; i < n; i++)
		{
			int flag = 0;
			for (int j = 0; j < k; j++)
			{
				if (sum[j].point == multi1[i].point)
				{
					sum[j].coeffi += multi1[i].coeffi;
					flag = 1;
					break;
				}
			}
			if (flag == 0)
			{
				memory(sum, multi1[i].point, multi1[i].coeffi);
			}
		}

		for (int i = 0; i < m; i++)
		{
			int flag = 0;
			for (int j = 0; j < k; j++)
			{
				if (sum[j].point == multi2[i].point)
				{
					sum[j].coeffi -= multi2[i].coeffi;
					flag = 1;
					break;
				}
			}
			if (flag == 0)
			{
				memory(sum, multi2[i].point, -multi2[i].coeffi);
			}
		}
	}

	sort(sum);

	for (int i = 0; i < k; i++)
	{
		if (sum[i].coeffi == 0)
			continue;
		else if (sum[i].coeffi == -1)
		{
			if (sum[i].point == 0)
				printf("-1");
			else if (sum[i].point == 1)
				printf("-x");
			// else if (sum[i].point < 0)
			// 	printf("-x^(%d)", sum[i].point);
			else
				printf("-x^%d", sum[i].point);
		}
		else if (sum[i].coeffi == 1)
		{
			if (sum[i].point == 0)
				printf("1");
			else if (sum[i].point == 1)
				printf("x");
			// else if (sum[i].point < 0)
			// 	printf("x^(%d)", sum[i].point);
			else
				printf("x^%d", sum[i].point);
		}
		else
		{
			if (sum[i].point == 0)
				printf("%d", sum[i].coeffi);
			else if (sum[i].point == 1)
				printf("%dx", sum[i].coeffi);
			// else if (sum[i].point < 0)
			// 	printf("%dx^(%d)", sum[i].coeffi, sum[i].point);
			else
				printf("%dx^%d", sum[i].coeffi, sum[i].point);
		}
		if (i < k - 1)
		{
			int q = i;
			while (sum[++q].coeffi == 0)
			{
				q++;
			}
			if (sum[q].coeffi > 0)
				printf("+");
		}
	}

	return 0;
}

void memory(SINGLE *sum, int point, int coeffi)
{
	sum[k].point = point;
	sum[k].coeffi = coeffi;
	k++;
}

void sort(SINGLE *sum)
{
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < k - i - 1; j++)
		{
			if (sum[j].point > sum[j + 1].point)
			{
				SINGLE temp = sum[j];
				sum[j] = sum[j + 1];
				sum[j + 1] = temp;
			}
		}
	}
}
