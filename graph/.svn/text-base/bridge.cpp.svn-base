/*
to calc the number of bridges in an undircted graph
nodes count from 1 to n
if the graph is not connnected
then break
(actually we can still call it)
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#define maxn 10005
#define maxm 200005
using namespace std;
struct edge
{
	int p,next;
	edge(){}
	edge(int a,int b):p(a),next(b){}
}v[maxn],e[maxm];
int n,m,con,tot,pre[maxn],cnt,bcnt,low[maxn],vis[maxn];
void init()
{
	con = bcnt = cnt = tot = 0;
	memset(vis,0,sizeof(vis));
	memset(pre,-1,sizeof(pre));
	memset(low,-1,sizeof(pre));
	for(int i = 1;i <= n;i++)
		v[i].next = -1;
}
void add(int p,int q)
{
	e[tot] = edge(q,v[p].next);
	v[p].next = tot++;
}
void dfs(int x)
{
	vis[x] = 1;
	con++;
	for(int k = v[x].next;~k;k = e[k].next)
	{
		if(!vis[e[k].p])
			dfs(e[k].p);
	}
}
void bridge(int xu,int xw)
{
	int k,u,w = xw;
	pre[w] = cnt++;
	low[w] = pre[w];
	for(k = v[w].next;~k;k = e[k].next)
	{
		u = e[k].p;
		if(pre[u] == -1)
		{
			bridge(w,u);
			if(low[w] > low[u])
				low[w] = low[u];
			if(low[u] == pre[u])
			{
				bcnt++;
				printf("%d %d\n",w,u);
			}
		}
		else if(u != xu)
		{
			if(low[w] > pre[u])
				low[w] = pre[u];
		}
	}
}
int main()
{
	scanf("%d %d",&n,&m);
	if(m == 0 && n != 0)//single point
	{
		printf("Disconnected!\n");
		return 0;
	}
	init();//initialization
	for(int i = 0;i < m;i++)
	{
		int a,b;
		scanf("%d %d",&a,&b);
		add(a,b);
		add(b,a);
	}
	dfs(1);//judge a graph's connectivity
	if(con != n)
	{
		printf("Disconnected!\n");
		return 0;
	}
	for(int i = 1;i <= n;i++)//judge edge-connection component
		if(pre[i] == -1)
			bridge(i,i);
	printf("%d\n",bcnt);
}
