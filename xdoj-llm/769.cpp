#include <stdio.h>
#include <stdlib.h>
#define ERROR 0
#define OK 1
typedef int ElemType;
typedef struct
{
    ElemType *data; // 队列空间首地址
    int maxSize;
    // 队列空间的大小
    int rear;
    int length;
} Queue;
// 尾指针，队列不空时指示队尾元素之后的位置
// 队列中的元素个数
int createQueue(Queue *q, int n); // 创建容量为 n 的空队列
int isEmpty(Queue q);
// 判断队列是否为空，若为空则返回1，否则返回0
void output(Queue q);
// 输出队列中从队头至队尾的所有元素，不修改队列
int in(Queue *q, ElemType e);
// 元素 e 入队列，成功时返回 OK，失败则返回ERROR
// （队满时入队失败，队列空间不扩充）
int out(Queue *q, ElemType *e);
// 非空时队头元素出队（通过参数e返回队头元素）
// 若出队成功则返回OK，否则返回ERROR
int main()
{ // 评测系统中使用这里定义的main函数进行测试
    Queue Q;
    int n;
    scanf("%d", &n);
    if (createQueue(&Q, n) != OK)
        return 0;
    ElemType elem;
    while (1)
    {
        scanf("%d", &elem);
        if (0 == elem)
            break;
        if (in(&Q, elem) != OK)
        {
            printf("OverFlow\n");
            break;
        }
    }
    output(Q);
    int c = 4;
    while (c--)
    {
        if (out(&Q, &elem))
        {
            printf("%d ", elem);
        }
        else
        {
            printf("UnderFlow\n");
            break;
        }
    }
    return 0;
} // main

int createQueue(Queue *q, int n)
{
    q->data = (ElemType *)malloc(n * sizeof(ElemType)); // 申请队列空间
    if (!q->data)
        return ERROR;
    q->length = 0;
    q->rear = 0;
    q->maxSize = n;
    return OK;
}

int isEmpty(Queue q) { return (0 == q.length); }
void output(Queue q)
{
    if (isEmpty(q))
    {
        return;
    }
    int idx = (q.rear - q.length + q.maxSize) % q.maxSize;
    do
    {
        printf("%d ", q.data[idx]);
        idx = (idx + 1) % q.maxSize;
    } while (idx != q.rear);
}

int in(Queue *q, ElemType e) {
    if (q->length >= q->maxSize) return ERROR; // 队满
    (q->data)[q->rear] = e;
    q->rear = (q->rear + 1) % q->maxSize;  // 循环队列，需要取模
    q->length ++;
    return OK;
}

int out(Queue *q, ElemType *e) {
    if (isEmpty(*q)) return ERROR;
    int front = (q->rear - q->length + q->maxSize) % q->maxSize;  // 计算队首位置
    *e = q->data[front];
    q->data[front] = 0;
    q->length --;
    return OK;
}