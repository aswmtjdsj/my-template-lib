//HDU 4009
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define maxn 1005
#define type int
const int inf = ~0u >> 1;
struct node
{
	int u,v;
	type cost;
	node(){}
	node(int _u,int _v,type _c):u(_u),v(_v),cost(_c){}
}e[maxn * maxn];
int pre[maxn],id[maxn],vis[maxn];
type in[maxn];
type dirmst(int root,int nv,int ne)
{
	type ret = 0;
	while(1)
	{
		//find the smallest in-arc
		fill(in,in + nv,inf);
		for(int i = 0;i < ne;i++)
		{
			int u = e[i].u;
			int v = e[i].v;
			if(e[i].cost < in[v] && u != v)
			{
				pre[v] = u;
				in[v] = e[i].cost;
			}
		}
		for(int i = 0;i < nv;i++)
		{
			if(i == root)
				continue;
			if(in[i] == inf)
				return -1;//there are some nodes other than root with no in-arc connected to it
		}
		//find the dir circle
		int cntnode = 0;
		fill(id,id + nv,-1);
		fill(vis,vis + nv,-1);
		in[root] = 0;
		for(int i = 0;i < nv;i++)
		{
			ret += in[i];
			int v = i;
			while(vis[v] != i && id[v] == -1 && v != root)
			{
				vis[v] = i;
				v = pre[v];
			}
			if(v != root && id[v] == -1)
			{
				for(int u = pre[v]; u != v;u = pre[u])
					id[u] = cntnode;
				id[v] = cntnode++;
			}
		}
		if(cntnode == 0)
			break;//no circle
		for(int i = 0;i < nv;i++)
			if(id[i] == -1)
				id[i] = cntnode++;
		//compress the nodes
		for(int i = 0;i < ne;i++)
		{
			int v = e[i].v;
			e[i].u = id[e[i].u];
			e[i].v = id[e[i].v];
			if(e[i].u != e[i].v)
				e[i].cost -= in[v];
		}
		nv = cntnode;
		root = id[root];
	}
	return ret;
}
int n,tot,X,Y,Z;
int ab(int x)
{
	return x >= 0?x:-x;
}
struct point
{
	int x,y,z;
	point(){}
	point(int a,int b,int c):x(a),y(b),z(c){}
	point operator - (const point p)
	{
		return point(x - p.x,y - p.y,z - p.z);
	}
	int dis()
	{
		return ab(x) + ab(y) + ab(z);
	}
}p[maxn];
int main()
{
	while(scanf("%d %d %d %d",&n,&X,&Y,&Z) == 4 && (n || X || Y || Z))
	{
		tot = 0;
		for(int i = 1;i <= n;i++)
		{
			int a,b,c;
			scanf("%d %d %d",&a,&b,&c);
			p[i] = point(a,b,c);
			e[tot++] = node(0,i,ab(p[i].z) * X);
		}
		for(int i = 1;i <= n;i++)
		{
			int opt;
			scanf("%d",&opt);
			for(int j = 0;j < opt;j++)
			{
				int a;
				scanf("%d",&a);
				if(a == i)
					continue;
				int temp = Y * (p[i] - p[a]).dis();
				if(p[i].z < p[a].z)
					temp += Z;
				e[tot++] = node(i,a,temp);
			}
		}
		int ans = dirmst(0,n + 1,tot);
		if(ans == -1)
			puts("poor XiaoA");
		else
			printf("%d\n",ans);
	}
}
