/*
   floyd to calc the Minimum Loop(not self loop) in an undirected graph
   O(N^3)*O(length of Path)
   */
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int inf = 15000005;
#define maxn 102
int dis[maxn][maxn];
int pre[maxn][maxn];
int f[maxn][maxn];
int n,m,ans,cnt;
int sol[maxn];
void dfs(int i,int j)//equals to expand the path
{//i ~ j => i ~ k ~ j => i ~ k1 ~ k ~ k2 ~ j ....
	int k = pre[i][j];
	if(k == 0)
		sol[cnt++] = j;
	else
	{
		dfs(i,k);
		dfs(k,j);
	}
}
int main()
{
	while(scanf("%d%d",&n,&m) == 2)
	{
		for(int i = 1;i <= n;i++)
		{
			for(int j = 1;j <= n;j++)
				f[i][j] = dis[i][j] = inf,pre[i][j] = 0;
			f[i][i] = dis[i][i] = 0;
		}
		for(int i = 0;i < m;i++)
		{
			int a,b,c;
			scanf("%d %d %d",&a,&b,&c);
			f[a][b] = f[b][a] = dis[a][b] = dis[b][a] = min(dis[a][b],c);
		}
		ans = inf;
		for(int k = 1;k <= n;k++)
		{
			for(int i = 1;i < k;i++)
				for(int j = i + 1;j < k;j++)
				{//path + shortest arc + path ( k to i ~ j to k)
					if(ans > dis[i][j] + f[i][k] + f[k][j])
					{
						ans = dis[i][j] + f[i][k] + f[k][j];
						cnt = 0;
						sol[cnt++] = i;
						dfs(i,j);
						sol[cnt++] = k;
					}
				}
			for(int i = 1;i <= n;i++)//just floyd
				for(int j = 1;j <= n;j++)
					if(dis[i][k] + dis[k][j] < dis[i][j])
					{
						dis[i][j] = dis[i][k] + dis[k][j];
						pre[i][j] = k;//k slacks i to j
						//means i => k => j
					}
		}
		if(ans == inf)puts("No solution.");
		else
		{
			for(int i = 0;i < cnt;i++)
				printf("%d%c",sol[i],i == cnt-1?'\n':' ');
		}
	}
}
