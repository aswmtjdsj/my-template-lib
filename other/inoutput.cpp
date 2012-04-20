#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
void print(int x)
{
	bool mark = false;
	if(x < 0)
	{
		x = -x;
		mark = true;
	}
	char str[20];
	int cnt = 0;
	do
	{
		str[++cnt] = (x % 10) + '0';
		x /= 10;
	}while(x);
	if(mark)
		putchar('-');
	for(int i = cnt;i>=1;i--)
		putchar(str[i]);
}
int main()
{
	char str[200];
	int a[2];
	while(1)
	{
		if(gets(str) == NULL)
			break;
		if(str[0] == 0)
			continue;
		int l = strlen(str);
		a[0] = a[1] = 0;
		int mark = 0;
		for(int i = 0;i < l;i++)
		{
			if(str[i] != ' ')
			{
				a[mark] *= 10;
				a[mark] += str[i] - '0';
			}
			else
				mark++;
		}
		print(a[0] + a[1]);
		puts("");
	}
}
