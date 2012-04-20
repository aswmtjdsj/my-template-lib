#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define maxn 2000005
int n,num[maxn];
int lowbit(int x){return x & (-x);}
int sum(int x)
{
	int ans = 0;
	while(x > 0)
	{
		ans += num[x];
		x -= lowbit(x);
	}
	return ans;
}
int add(int x)
{
	while(x <= n)
	{
		num[x] ++;
		x += lowbit(x);
	}
}
int main()
{
	scanf("%d",&n);
	long long ans = 0;
	for(int i = 1;i <= n;i++)
	{
		int a;
		scanf("%d",&a);
		ans += sum(n) - sum(a - 1);
		add(a);
	}
	printf("%lld\n",ans);
}
