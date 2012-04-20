/*
   node counts from 0 to n - 1
   call the function like using dfs
   if(pre[i]==-1)then scc(i)
   */
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define maxn 50005
#define maxm 100005
#define type int
struct edge
{
	int p,next,val;
	edge(){}
	edge(int a,int b,int c):p(a),next(b),val(c){}
}e[maxm];
int st[maxn];
int sc[maxn],pre[maxn],low[maxn],s[maxn];
int cnt0,cnt1;
int n,m,tot,N;
void init()
{
	tot = N = cnt0 = cnt1 = 0;
	fill(st,st + n + 1,-1);
	fill(pre,pre + n + 1,-1);
	fill(low,low + n + 1,-1);
}
void add(int p,int q,int val)
{
	e[tot] = edge(q,st[p],val);
	st[p] = tot++;
}
void scc(int now)
{
	int v,mm;
	mm = low[now] = pre[now] = cnt0++;
	s[N++] = now;
	for(int k = st[now];~k;k = e[k].next)
	{
		if(pre[e[k].p] == -1)
			scc(e[k].p);
		if(low[e[k].p] < mm)
			mm = low[e[k].p];
	}
	if(mm < low[now])
	{
		low[now] = mm;
		return ;
	}
	do
	{
		sc[(v = s[--N])] = cnt1;
		low[v] = n;
	}while(s[N] != now);
	cnt1++;
}
int main()
{
	cin >> n >> m;
	init();
	for(int i = 0;i < m;i++)
	{
		int a,b;
		scanf("%d %d",&a,&b);
		add(a,b,1);
	}
	for(int i = 0;i < n;i++)
		if(pre[i] == -1)
			scc(i);
	/*for(int i = 0;i < n;i++)
		cout << sc[i] << endl;*/
}
