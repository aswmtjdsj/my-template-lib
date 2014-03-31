#include <iostream>
#include <cstdio>
#define SIZE 10000
#define ST -1
#define left(i) ((i) << 1)
#define right(i) (((i) << 1) + 1)
#define pi(i) ((i) >> 1)
using namespace std;
class HEAP
{
    private:
        int item[SIZE + 5];
        int size;
        int now;
    public:
        HEAP(int,int[]);
        HEAP(int);
        bool push(int);
        bool del(int);
        bool inc(int,int);
        bool pop();
        int top();
        void hpy(int);
        void sort(int *);
        void print(int);
        void out(int);
};
int temp  = 0;
void HEAP :: out(int pos)
{
    printf("%d\n",item[pos]);
}
HEAP :: HEAP(int siz,int a[])
{
    size = siz;
    now = size;
    for(int i = 1;i <= size;i++)
        item[i] = a[i];
    for(int i = size / 2;i >= 1;i--)
        hpy(i);
}
HEAP :: HEAP(int siz)
{
    now = 0;
    size = siz;
    for(int i = 1;i <= size;i++)
        item[i] = ST;
}
void HEAP :: hpy(int pos)
{
    int l = left(pos),r = right(pos),large;
    if(l <= now && item[l] > item[pos])
        large = l;
    else
        large = pos;
    if(r <= now && item[r] > item[large])
        large = r;
    if(large != pos)
    {
        swap(item[large],item[pos]);
        hpy(large);
    }
}
bool HEAP :: inc(int pos,int k)
{
    if(pos > now)
        return false;
    else
    {
        item[pos] = k;
        while(pos > 1 && item[pos] > item[pi(pos)])//recurrency
        {
            swap(item[pos],item[pi(pos)]);
            pos = pi(pos);
        }
        return true;
    }
}
int HEAP :: top()
{
    if(now > 0 && size > 0)
        return item[1];
    else
        return -1;
}
bool HEAP :: pop()
{
    if(now < 1 || size < 1)
        return false;
    else
    {
        swap(item[1],item[now]);
        now --;
        hpy(1);
        return true;
    }
}
bool HEAP :: push(int x)
{
    if(now < size)
    {
        now++;
        inc(now,x);
        return true;
    }
    else
        return false;
}
void HEAP :: sort(int * a)
{
    int b[SIZE + 5];
    for(int i = 1;i <= size;i++)
        b[i] = item[i];
    for(int i = size;i >= 2;i--)
    {
        swap(item[i],item[1]);
        now --;
        hpy(1);
    }
    for(int i = 1;i <= size;i++)
    {
        a[i] = item[i];
        item[i] = b[i];
    }
}
bool HEAP :: del(int pos)
{
    if(pos < now)
    {
        swap(item[pos],item[now]);
        now--;
        hpy(pos);
        return true;
    }
    else if(pos == now)
    {
        now --;
        return true;
    }
    else
        return false;
}
void HEAP :: print(int pos)
{
    temp++;
    printf("%8d",item[pos]);
    if(left(pos) <= now && item[left(pos)] != -1)
        print(left(pos));
    else
    {
        for(int i = 0;i < temp;i++)
            printf("\t");
        printf("\n");
    }
    if(right(pos) <= now && item[right(pos)] != -1)
    {
        for(int i = 0;i < temp;i++)
            printf("\t");
        print(right(pos));
    }
    else
        printf("\n");
    temp--;
}
int main()
{
    int n;
    while(scanf("%d",&n) == 1)
    {
        int a[10005];
        for(int i = 1;i <= n;i++)
            scanf("%d",&a[i]);
        HEAP test(n,a);
        test.sort(a);
        printf("%d\n",a[n / 2 + 1]);        
    }
}
