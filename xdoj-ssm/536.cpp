#include<stdio.h>

void paint(int, int (*)[4], int *);

int main()
{
	int n,l[100][4];
	int result[300];
	int i;

	scanf("%d",&n);

	for(i=0;i<n;i++)
	{
		scanf("%d%d%d%d",&l[i][0],&l[i][1],&l[i][2],&l[i][3]);
	}

	paint(n,l,result);
	for(i=0;i<=result[0];i++)
	{
		printf("%d %d\n",result[i*2],result[i*2+1]);
	}

	return 0;
}

void paint(int n, int l[][4], int *result) {  
    int colorCount[10010] = {0}; // 记录每个单元格的染色次数  
    int i, j, x1, y1, x2, y2;  
  
    // 统计每个单元格的染色次数  
    for (i = 0; i < n; i++) {  
        x1 = l[i][0];  
        y1 = l[i][1];  
        x2 = l[i][2];  
        y2 = l[i][3];  
        for (j = x1; j < x2; j++) {  
            for (int k = y1; k < y2; k++) {  
                colorCount[j * 100 + k]++;  
            }  
        }  
    }  
  
    // 统计每个染色次数的单元格数目  
    int count[10010] = {0}; // 记录每个染色次数的单元格数目  
    for (i = 0; i < 10000; i++) {  
        count[colorCount[i]]++;  
    }  
    
    bool flag = 0;
  
    // 将结果存入result数组  注意在得到一次count[i]存在后，后面的count[i]都要记录，即使是0
    int index = 0;  
    for (i = 10000; i >= 0; i--) {  
        if (count[i] > 0 || flag == 1) {  
            result[index++] = i;  
            result[index++] = count[i]; 
			flag = 1; 
        }  
    } 
}