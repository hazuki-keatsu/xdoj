#include <iostream>
#include <new>

struct Person
{
    int id;
    int password;
    Person *next;
};

// 释放循环（或线性）链表
static void freeCircular(Person *head)
{
    if (!head)
        return;
    Person *p = head->next;
    head->next = nullptr; // 断环
    delete head;
    while (p)
    {
        Person *t = p->next;
        delete p;
        p = t;
    }
}

int main()
{
    // 参数输入
    int n, m;
    if (!(std::cin >> n >> m))
        return 0;
    if (n <= 0)
        return 0;
    if (m <= 0)
        m = 1;

    // 构建无头结点循环链表
    Person *head = new Person;
    if (!head)
        return 0;
    head->id = 1;
    // 放入第一个结点
    if (!(std::cin >> head->password))
    {
        delete head;
        return 0;
    }
    head->next = head;
    // 维护一个尾结点
    Person *tail = head;

    // 依次放入其他的结点
    for (int i = 2; i <= n; ++i)
    {
        Person *p = new Person;
        if (!p)
        {
            freeCircular(head);
            return 0;
        }
        p->id = i;
        if (!(std::cin >> p->password))
        {
            delete p;
            freeCircular(head);
            return 0;
        }
        p->next = head;
        tail->next = p;
        tail = p;
    }

    // 约瑟夫环过程（输出编号）
    Person *current = head;
    Person *prev = tail;
    int remaining = n;

    bool firstOut = true;
    while (remaining > 1)
    {
        // 减少循环次数
        int steps = ((m > 0 ? m : 1) - 1) % remaining;
        for (int i = 0; i < steps; ++i)
        {
            prev = current;
            current = current->next;
        }

        if (!firstOut)
            std::cout << ' ';
        std::cout << current->id;
        firstOut = false;

        int nextM = current->password;
        m = (nextM <= 0) ? 1 : nextM;

        if (current == head)
            head = head->next;
        if (current == tail)
            tail = prev;

        prev->next = current->next;
        delete current;
        current = prev->next;
        --remaining;
    }

    if (!firstOut)
        std::cout << ' ';
    std::cout << current->id << '\n';
    delete current;

    return 0;
}
