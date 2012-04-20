#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define maxn 2000000
#define left l , m , k << 1
#define right m + 1 , r , k << 1|1
int st[maxn * 4];
void rec(int k)
{
	st[k] = st[k << 1] + st[k << 1|1];
}
void build(int l,int r,int k)
{
	st[k] = 0;
	if(l == r)return ;
	int m = (l + r) >> 1;
	build(left);
	build(right);
}
void update(int x,int l,int r,int k)
{
	if(l == r && l == x)
	{
		st[k]++;
		return ;
	}
	int m = (l + r) >> 1;
	if(x <= m)update(x,left);
	else update(x,right);
	rec(k);
}
int query(int ll,int rr,int l,int r,int k)
{
	if(ll <= l && rr >= r)return st[k];
	int m = (l + r) >> 1;
	int ans = 0;
	if(ll <= m) ans += query(ll,rr,left);
	if(rr > m) ans += query(ll,rr,right);
	return ans;
}
int main()
{
	int n;
	scanf("%d",&n);
	build(1,n,1);
	long long ans = 0;
	for(int i = 1;i <= n;i++)
	{
		int m;
		scanf("%d",&m);
		ans += query(m,n,1,n,1);
		update(m,1,n,1);
	}
	printf("%lld\n",ans);
}
